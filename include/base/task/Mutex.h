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
			Mutex()
				: _handle(base::task::create_mutex())
			{
				// 将实现放到源文件中预编译，可以防止有些卧龙凤雏的库，定义了一个宏名为
				// create_mutex, 导致我无法正确调用 base::task::create_mutex 函数。
			}

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
