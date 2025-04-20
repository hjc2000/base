#pragma once
#include "mutex_handle.h"
#include <memory>

namespace base
{
	namespace task
	{
		class Mutex
		{
		private:
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

		class LockGuard
		{
		private:
			base::task::Mutex const &_mutex;

		public:
			LockGuard(base::task::Mutex const &m)
				: _mutex(m)
			{
				_mutex.Lock();
			}

			~LockGuard()
			{
				_mutex.Unlock();
			}
		};

	} // namespace task
} // namespace base
