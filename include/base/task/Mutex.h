#pragma once
#include "base/define.h"
#include "mutex_handle.h"
#include <memory>

namespace base
{
	namespace task
	{
		class Mutex
		{
		private:
			DELETE_COPY_AND_MOVE(Mutex)

			std::shared_ptr<base::task::mutex_handle> _handle;

		public:
			Mutex();

			void Lock() const
			{
				base::task::lock(*_handle);
			}

			void Unlock() const
			{
				base::task::unlock(*_handle);
			}
		};

		class MutexGuard
		{
		private:
			base::task::Mutex const &_mutex;

		public:
			MutexGuard(base::task::Mutex const &m)
				: _mutex(m)
			{
				_mutex.Lock();
			}

			~MutexGuard()
			{
				_mutex.Unlock();
			}
		};

	} // namespace task
} // namespace base
