#pragma once
#include "base/task/IMutex.h"

#if HAS_THREAD

namespace base
{
	class StdMutex :
		public base::IMutex
	{
	private:
		std::mutex _lock;

	public:
		void Lock() override;
		void Unlock() override;
	};
} // namespace base

#endif // HAS_THREAD
