#pragma once
#include <base/LockGuard.h>
#include <memory>

namespace base
{
	class IMutex :
		public base::ILock
	{
	public:
		virtual void Lock() = 0;
		virtual void Unlock() = 0;
	};

	namespace di
	{
		/// @brief 创建一个互斥量。
		/// @return
		std::shared_ptr<base::IMutex> CreateMutex();
	} // namespace di
} // namespace base
