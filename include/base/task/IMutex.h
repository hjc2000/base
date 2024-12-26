#pragma once
#include <base/LockGuard.h>

namespace base
{
	class IMutex :
		public base::ILock
	{
	public:
		virtual void Lock() = 0;
		virtual void Unlock() = 0;
	};
} // namespace base
