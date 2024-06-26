#pragma once
#ifndef HAS_THREAD
#define HAS_THREAD 0
#endif

#if HAS_THREAD
#include <functional>
#include <mutex>

namespace base
{
	/// @brief 带有互斥锁的句柄包装器。
	/// @note 获取和设置句柄都要竞争互斥锁。
	///
	/// @tparam T
	template <typename T>
	class MutexHandleWrapper
	{
	private:
		std::mutex _lock;
		T _handle;

	public:
		T &Handle()
		{
			std::lock_guard l{_lock};
			return _handle;
		}

		void SetHandle(T handle)
		{
			std::lock_guard l{_lock};
			_handle = handle;
		}
	};
}
#endif // HAS_THREAD
