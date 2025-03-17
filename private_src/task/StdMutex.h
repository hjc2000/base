#pragma once
#if HAS_THREAD

	#include <base/task/IMutex.h>

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
