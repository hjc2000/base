#include "base_semaphore_handle.h"
#include "base/string/define.h"
#include "base/unit/Second.h"
#include <cstdint>
#include <memory>
#include <semaphore>

#if HAS_THREAD

class base::task::base_semaphore_handle
{
private:
	std::counting_semaphore<INT32_MAX> _semaphore{0};

public:
	base_semaphore_handle(int32_t initial_count)
		: _semaphore(initial_count)
	{
	}

	///
	/// @brief 释放信号量。
	///
	/// @param count 要释放的数量。
	///
	void Release(int32_t count)
	{
		if (count <= 0)
		{
			throw std::invalid_argument{CODE_POS_STR + "count 不能 <= 0."};
		}

		_semaphore.release(count);
	}

	///
	/// @brief 获取信号量。无限等待，永不超时。
	///
	///
	void Acquire()
	{
		_semaphore.acquire();
	}

	///
	/// @brief 尝试获取信号量。超时后会失败，并返回 false，成功获取信号量后将
	/// 返回 true.
	///
	/// @param timeout 超时时间。
	///
	/// @return 成功获取信号量则返回 true, 否则返回 false.
	///
	bool TryAcquire(base::unit::Second const &timeout)
	{
		if (timeout < base::unit::Second{0})
		{
			throw std::invalid_argument{CODE_POS_STR + "超时时间不能 <= 0."};
		}

		bool result = _semaphore.try_acquire_for(static_cast<std::chrono::milliseconds>(timeout));
		return result;
	}
};

std::shared_ptr<base::task::base_semaphore_handle> base::task::create_base_semaphore(int32_t initial_count)
{
	return std::shared_ptr<base::task::base_semaphore_handle>{new base::task::base_semaphore_handle{initial_count}};
}

void base::task::release(base::task::base_semaphore_handle &h, int32_t count)
{
	h.Release(count);
}

void base::task::acquire(base::task::base_semaphore_handle &h)
{
	h.Acquire();
}

bool base::task::try_acquire(base::task::base_semaphore_handle &h, base::unit::Second const &timeout)
{
	return h.TryAcquire(timeout);
}

#endif
