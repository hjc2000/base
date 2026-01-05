#pragma once
#include "base/container/Queue.h"
#include "base/IDisposable.h"
#include "base/string/define.h"
#include "base/task/Mutex.h"
#include "base/task/Semaphore.h"
#include <atomic>
#include <exception>
#include <stdexcept>

namespace base
{
	///
	/// @brief 数据缓存。
	///
	/// @note 可以往里放入数据和取出数据。本质上是一个队列。当队列的元素数量超过上限时会丢弃最开始的数据。
	///
	/// @tparam T
	///
	template <typename T>
	class DataCache final :
		public IDisposable
	{
	private:
		int64_t _max_count;
		base::Queue<T> _queue;
		std::atomic_bool _disposed = false;
		base::task::Mutex _lock{};
		base::Semaphore _data_avaliable_signal{0};

	public:
		///
		/// @brief 构造函数
		/// @note 因为拷贝构造函数和移动构造函数无法对被拷贝和被移动的对象加锁，
		/// 所以会引发线程安全问题，所以本类不支持拷贝和移动。
		/// @param max_count 能够缓存的最大的数据个数。
		///
		DataCache(int64_t max_count)
		{
			if (max_count < 1)
			{
				throw std::invalid_argument{CODE_POS_STR + "max_count 必须大于等于 1"};
			}

			_max_count = max_count;
		}

		~DataCache()
		{
			Dispose();
		}

		void Dispose() override
		{
			if (_disposed)
			{
				return;
			}

			_disposed = true;
			_data_avaliable_signal.Dispose();
		}

		///
		/// @brief 将数据放到内部队列的末尾。
		/// @param item
		///
		void PushBack(T const &item)
		{
			if (_disposed)
			{
				throw std::runtime_error{CODE_POS_STR + "已经释放了，无法放入数据。"};
			}

			base::task::MutexGuard g{_lock};
			_queue.Enqueue(item);
			if (_queue.Count() > _max_count)
			{
				_queue.Dequeue();
			}

			_data_avaliable_signal.ReleaseAll();
		}

		///
		/// @brief 取出数据。
		/// @note 如果当前无数据可取会阻塞，直到有数据。取出后，数据将从内部队列中删除。
		/// @return
		///
		T TackOut()
		{
			while (true)
			{
				if (_disposed)
				{
					throw std::runtime_error{CODE_POS_STR + "已经释放了，无法取出数据。"};
				}

				// 在持有互斥锁的条件下检查，避免误触，以及操作
				{
					base::task::MutexGuard g{_lock};
					if (_queue.Count() > 0)
					{
						return _queue.Dequeue();
					}
				}

				try
				{
					_data_avaliable_signal.Acquire();
				}
				catch (std::exception const &e)
				{
					throw std::runtime_error{CODE_POS_STR + e.what()};
				}
			}
		}
	};
} // namespace base
