#include "mutex_handle.h" // IWYU pragma: keep
#include <mutex>

#if HAS_THREAD

class base::task::mutex_handle
{
private:
	std::mutex _mutex{};

public:
	void lock()
	{
		_mutex.lock();
	}

	void unlock()
	{
		_mutex.unlock();
	}
};

/* #region 全局函数 */

void base::task::lock(base::task::mutex_handle &h)
{
	h.lock();
}

void base::task::unlock(base::task::mutex_handle &h)
{
	h.unlock();
}

/* #endregion */

#endif
