#pragma once
#include "base/task/task.h" // IWYU pragma: keep
#include <cstdint>          // IWYU pragma: keep
#include <new>              // IWYU pragma: keep

namespace base
{
	template <typename T>
	class SingletonProvider
	{
	private:
		/* #region get_instance */

#if HAS_THREAD

		T &get_instance()
		{
			static T instance{};
			return instance;
		}

#else

		bool _initialized = false;
		alignas(T) uint8_t _instance_buffer[sizeof(T)];

		T &get_instance()
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

#endif // HAS_THREAD

		/* #endregion */

	public:
		///
		/// @brief 获取单例。
		///
		/// @return
		///
		T &Instance()
		{
			return get_instance();
		}
	};

} // namespace base
