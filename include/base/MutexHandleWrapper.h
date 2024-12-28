#pragma once
#include <base/task/IMutex.h>
#include <functional>

namespace base
{
	/// @brief 带有互斥锁的句柄包装器。
	/// @note 获取和设置句柄都要竞争互斥锁。
	/// @tparam T
	template <typename T>
	class MutexHandleWrapper final
	{
	private:
		std::shared_ptr<base::IMutex> _lock = base::di::CreateMutex();
		T _handle{};

	public:
		T &Handle()
		{
			base::LockGuard g{*_lock};
			return _handle;
		}

		void SetHandle(T const &handle)
		{
			base::LockGuard g{*_lock};
			_handle = handle;
		}
	};
} // namespace base
