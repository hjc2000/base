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
			/* #region 析构 */

#if HAS_THREAD

			///
			/// @brief HAS_THREAD 的平台，即通用操作系统才需要析构。
			/// 非 HAS_THREAD 平台是单片机，程序永不终止，单例永不析构。
			///
			~SingletonProvider()
			{
				{
					base::task::TaskSchedulerSuspendGuard g{};
					if (!_initialized)
					{
						return;
					}
				}

				reinterpret_cast<T *>(_instance_buffer)->~T();
				_initialized = false;
			}

#endif // HAS_THREAD

			/* #endregion */

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
