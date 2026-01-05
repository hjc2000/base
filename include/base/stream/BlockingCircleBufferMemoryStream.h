#pragma once
#include "base/container/Range.h"
#include "base/IDisposable.h"
#include "base/stream/CircleBufferMemoryStream.h"
#include "base/task/Mutex.h"
#include "base/task/Semaphore.h"

namespace base
{
	///
	/// @brief 带阻塞功能的环形缓冲区的内存流。
	///
	class BlockingCircleBufferMemoryStream final :
		public base::Stream
	{
	private:
		base::CircleBufferMemoryStream _mstream;
		std::atomic_bool _stream_closed = false;
		base::task::Mutex _lock{};

		///
		/// @brief 流中的数据被消费了，现在处于不是满的状态
		///
		base::Semaphore _buffer_consumed_signal{1};

		///
		/// @brief 流中有数据可用。
		///
		base::Semaphore _buffer_avaliable_signal{0};

	public:
		BlockingCircleBufferMemoryStream(int64_t max_size)
			: _mstream(max_size)
		{
		}

		~BlockingCircleBufferMemoryStream()
		{
			Close();
		}

		/* #region 流属性 */

		virtual bool CanRead() const override
		{
			return true;
		}

		virtual bool CanWrite() const override
		{
			return true;
		}

		virtual bool CanSeek() const override
		{
			return false;
		}

		virtual int64_t Length() const override
		{
			base::task::MutexGuard g{_lock};
			return _mstream.Length();
		}

		virtual void SetLength(int64_t value) override
		{
			base::task::MutexGuard g{_lock};
			_mstream.SetLength(value);
		}

		virtual int64_t Position() const override
		{
			base::task::MutexGuard g{_lock};
			return _mstream.Position();
		}

		virtual void SetPosition(int64_t value) override
		{
			base::task::MutexGuard g{_lock};
			_mstream.SetPosition(value);
		}

		/* #endregion */

		/* #region 读写冲关 */

		virtual int64_t Read(base::Span const &span) override
		{
			while (true)
			{
				// 在持有互斥锁的条件下检查，避免误触，以及操作
				{
					base::task::MutexGuard g{_lock};
					if (_stream_closed || _mstream.Length() > 0)
					{
						// 流关闭后无条件允许读取，即使 _mstream 长度为 0, 此时本对象的 Read 方法
						// 才允许返回 0, 并且由于写入已经禁止，_mstream 的长度将永远为 0, 于是
						// 本方法将永远返回 0.
						int64_t have_read = _mstream.Read(span);
						_buffer_consumed_signal.ReleaseAll();
						return have_read;
					}
				}

				try
				{
					_buffer_avaliable_signal.Acquire();
				}
				catch (base::ObjectDisposedException const &e)
				{
					// 不处理，继续下一轮循环。
				}
				catch (std::exception const &e)
				{
					throw std::runtime_error{CODE_POS_STR + e.what()};
				}
				catch (...)
				{
					throw std::runtime_error{CODE_POS_STR + "未知的异常。"};
				}
			}
		}

		virtual void Write(base::ReadOnlySpan const &span) override
		{
			if (span.Size() <= 0)
			{
				return;
			}

			base::ReadOnlySpan remain_span = span;
			while (true)
			{
				if (_stream_closed)
				{
					throw base::ObjectDisposedException{CODE_POS_STR + "流已关闭，无法写入。"};
				}

				{
					base::task::MutexGuard g{_lock};
					if (_mstream.AvailableToWrite() > 0)
					{
						int64_t should_write = std::min(_mstream.AvailableToWrite(), remain_span.Size());
						_mstream.Write(remain_span[base::Range{0, should_write}]);
						remain_span = remain_span[base::Range{should_write, remain_span.Size()}];
						_buffer_avaliable_signal.ReleaseAll();
						if (remain_span.Size() <= 0)
						{
							// 将所有数据写完了，返回
							return;
						}
					}
				}

				// 如果刚才将所有数据写完了，已经返回了，到这里说明没写完，但是流已经满了，需要等待。
				try
				{
					_buffer_consumed_signal.Acquire();
				}
				catch (base::ObjectDisposedException const &e)
				{
					// 不处理，继续下一轮循环。
				}
				catch (std::exception const &e)
				{
					throw std::runtime_error{CODE_POS_STR + e.what()};
				}
				catch (...)
				{
					throw std::runtime_error{CODE_POS_STR + "未知的异常。"};
				}
			}
		}

		virtual void Flush() override
		{
			base::task::MutexGuard g{_lock};
			_mstream.Flush();
		}

		///
		/// @brief 关闭流。
		///
		/// @note 关闭后，写入会引发异常。Read 方法在读取完缓冲区的数据后，将永远返回 0.
		///
		/// @note 关闭后，会取消所有阻塞，且不会再阻塞。
		///
		virtual void Close() override
		{
			base::task::MutexGuard g{_lock};
			_stream_closed = true;
			_buffer_avaliable_signal.Dispose();
			_buffer_consumed_signal.Dispose();
		}

		/* #endregion */

		///
		/// @brief 返回内部循环缓冲区的大小，也是此流所能达到的最大长度。
		///
		/// @return
		///
		int64_t BufferSize() const
		{
			base::task::MutexGuard g{_lock};
			return _mstream.BufferSize();
		}

		///
		/// @brief 本流内部的缓冲区剩余空间。单位：字节。
		///
		/// @return
		///
		int64_t AvailableToWrite() const
		{
			base::task::MutexGuard g{_lock};
			return _mstream.AvailableToWrite();
		}
	};

} // namespace base
