#pragma once
#ifndef HAS_THREAD
#define HAS_THREAD 0
#endif

#include <functional>

#if HAS_THREAD
#include <mutex>
#endif

namespace base
{
	/// @brief 带有互斥锁的句柄包装器。
	/// @note 获取和设置句柄都要竞争互斥锁。
	/// @note 仅当宏 HAS_THREAD 定义为真时有效。
	///
	/// @tparam T
	template <typename T>
	class MutexHandleWrapper
	{
	private:
#if HAS_THREAD
		std::mutex _lock;
#endif

		T _handle;

	public:
		T &Handle()
		{
#if HAS_THREAD
			std::lock_guard l{_lock};
#endif

			return _handle;
		}

		void SetHandle(T handle)
		{
#if HAS_THREAD
			std::lock_guard l{_lock};
#endif

			_handle = handle;
		}
	};
}
