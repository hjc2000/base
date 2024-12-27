#include "DisposableSemaphore.h"

#if HAS_THREAD

base::DisposableSemaphore::DisposableSemaphore(base::DisposableSemaphore_MaxCount const &max_count,
											   base::DisposableSemaphore_InitialCount const &initial_count)
	: _semaphore(initial_count.Value())
{
	_max_count = max_count.Value();
	if (_max_count <= 0)
	{
		throw std::invalid_argument{"最大计数必须 >= 0."};
	}

	_release_count = initial_count.Value();
}

void base::DisposableSemaphore::Dispose()
{
	if (_disposed)
	{
		return;
	}

	_disposed = true;

	/**
	 * 只要并发数不超过 INT32_MAX，配合 _disposed，这会让信号量不再具备阻塞能力。
	 *
	 * 这里直接释放，而不像 Release 方法那样还竞争 _lock，这样可以保证快速，并且
	 * 预防有线程在 Acquire 方法的循环中卡死，此时又拿着互斥锁，导致 Dispose 也被
	 * 卡死。
	 */
	_semaphore.release(INT32_MAX);

	{
		std::lock_guard g{_lock};
		_release_count += INT32_MAX;
	}
}

void base::DisposableSemaphore::Release(int32_t count)
{
	std::lock_guard g{_lock};
	_release_count += count;
	_semaphore.release(count);
}

void base::DisposableSemaphore::Acquire()
{
	if (_disposed)
	{
		throw std::runtime_error{"信号量已经释放，无法获取。"};
	}

	{
		std::lock_guard g{_lock};
		while (_release_count > _max_count)
		{
			_semaphore.acquire();
			_release_count--;
		}

		// 这是本次获取的份。
		_release_count--;
	}

	_semaphore.acquire();
	if (_disposed)
	{
		throw std::runtime_error{"信号量已经释放，无法获取。"};
	}
}

bool base::DisposableSemaphore::TryAcquire(base::Seconds const &timeout)
{
	if (_disposed)
	{
		throw std::runtime_error{"信号量已经释放，无法获取。"};
	}

	{
		std::lock_guard g{_lock};
		while (_release_count > _max_count)
		{
			_semaphore.acquire();
			_release_count--;
		}

		/**
		 * 这是本次获取的份。
		 *
		 * 不管等会儿能不能获取成功，都先递减 _release_count，假设会成功。大不了就是释放的信号量
		 * 计数超过 _max_count，反正前面有一个 while (_release_count > _max_count) 循环，
		 * 超标了也没事。
		 *
		 * 先递减 _release_count 可以避免别的线程获取信号量时在 while (_release_count > _max_count)
		 * 循环中循环次数过多，然后被卡死在循环里面。
		 */
		_release_count--;
	}

	bool result = _semaphore.try_acquire_for(static_cast<std::chrono::milliseconds>(timeout));
	if (_disposed)
	{
		throw std::runtime_error{"信号量已经释放，无法获取。"};
	}

	if (!result)
	{
		std::lock_guard g{_lock};

		// 刚才获取信号量失败了，要将递减的 _release_count 恢复。
		_release_count++;
	}

	return result;
}

#endif // HAS_THREAD
