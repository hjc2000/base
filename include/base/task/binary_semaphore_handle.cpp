#include "binary_semaphore_handle.h" // IWYU pragma: keep
#include "base/string/define.h"
#include "base/unit/Nanosecond.h"
#include "base/unit/Second.h"
#include <chrono>
#include <semaphore>

#if HAS_THREAD

class base::task::binary_semaphore_handle
{
private:
	std::binary_semaphore _bs;

public:
	binary_semaphore_handle(bool initial_release)
		: _bs(initial_release)
	{
	}

	///
	/// @brief 释放信号量。
	///
	void Release()
	{
		_bs.release();
	}

	///
	/// @brief 获取信号量。无限等待，永不超时。
	///
	void Acquire()
	{
		_bs.acquire();
	}

	///
	/// @brief 尝试获取信号量。超时后会失败，并返回 false，成功获取信号量后将
	/// 返回 true.
	/// @param timeout 超时时间。
	/// @return
	///
	bool TryAcquire(base::unit::Second const &timeout)
	{
		if (timeout < base::unit::Second{0})
		{
			throw std::invalid_argument{CODE_POS_STR + "超时时间不能 <= 0."};
		}

		return _bs.try_acquire_for(static_cast<std::chrono::nanoseconds>(timeout));
	}
};

/* #region 全局函数 */

std::shared_ptr<base::task::binary_semaphore_handle> base::task::create_binary_semaphore(bool initial_release)
{
	return std::shared_ptr<base::task::binary_semaphore_handle>{new base::task::binary_semaphore_handle{initial_release}};
}

void base::task::release(base::task::binary_semaphore_handle &h)
{
	h.Release();
}

void base::task::acquire(base::task::binary_semaphore_handle &h)
{
	h.Acquire();
}

bool base::task::try_acquire(base::task::binary_semaphore_handle &h, base::unit::Second const &timeout)
{
	return h.TryAcquire(timeout);
}

/* #endregion */

#endif
