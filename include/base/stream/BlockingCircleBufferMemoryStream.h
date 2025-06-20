#pragma once
#include "base/container/Range.h"
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
		BlockingCircleBufferMemoryStream(int32_t max_size)
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

		virtual int32_t Read(base::Span const &span) override
		{
			while (true)
			{
				if (_stream_closed)
				{
					throw std::runtime_error{CODE_POS_STR + "流已关闭，无法读取"};
				}

				// 在持有互斥锁的条件下检查，避免误触，以及操作
				{
					base::task::MutexGuard g{_lock};
					if (_mstream.Length() > 0)
					{
						int64_t have_read = _mstream.Read(span);
						_buffer_consumed_signal.ReleaseAll();
						return have_read;
					}
				}

				try
				{
					_buffer_avaliable_signal.Acquire();
				}
				catch (std::exception const &e)
				{
					throw std::runtime_error{CODE_POS_STR + e.what()};
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
					throw std::runtime_error{CODE_POS_STR + "流已关闭，无法写入。"};
				}

				{
					base::task::MutexGuard g{_lock};
					if (_mstream.AvailableToWrite() > 0)
					{
						int32_t should_write = std::min(_mstream.AvailableToWrite(), remain_span.Size());
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
				catch (std::exception const &e)
				{
					throw std::runtime_error{CODE_POS_STR + e.what()};
				}
			}
		}

		virtual void Flush() override
		{
			base::task::MutexGuard g{_lock};
			_mstream.Flush();
		}

		///
		/// @brief 结束流。
		///
		/// @note 结束后，写入的数据会被丢弃。Read 方法在读取完缓冲区的数据后，将永远返回 0.
		///
		/// @note 结束后，会取消所有阻塞，且不会再阻塞。
		///
		virtual void Close() override
		{
			base::task::MutexGuard g{_lock};
			_stream_closed = true;
			_buffer_avaliable_signal.Dispose();
			_buffer_consumed_signal.Dispose();
		}

		/* #endregion */
	};
} // namespace base
