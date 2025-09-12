#pragma once
#include "base/task/task.h"
#include <cstdint>

namespace base
{
	namespace embedded
	{
		template <typename T>
		class SingletonProvider
		{
		private:
			bool _initialized = false;
			alignas(T) uint8_t _instance_buffer[sizeof(T)];

		public:
			T &Instance()
			{
				if (!_initialized)
				{
					base::task::TaskSchedulerSuspendGuard g{};
					if (!_initialized)
					{
						new (_instance_buffer) T{};
						_initialized = true;
					}
				}

				return *reinterpret_cast<T *>(_instance_buffer);
			}
		};

	} // namespace embedded
} // namespace base
