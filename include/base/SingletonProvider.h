#pragma once
#include "base/task/task.h" // IWYU pragma: keep
#include <cstdint>

namespace base
{
	template <typename T>
	class SingletonProvider
	{
	private:
		bool _initialized = false;
		alignas(T) uint8_t _instance_buffer[sizeof(T)];

		/* #region get_instance */

#if HAS_THREAD

		T &get_instance()
		{
			static T instance{};
			return instance;
		}

#else

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
		/* #region 析构 */

#if HAS_THREAD

		///
		/// @brief HAS_THREAD 的平台，即通用操作系统才需要析构。
		/// 非 HAS_THREAD 平台是单片机，程序永不终止，单例永不析构。
		///
		/// @note 单例的析构是程序结束时运行时调用的，是单线程的，不需要加锁。
		///
		~SingletonProvider()
		{
			if (!_initialized)
			{
				return;
			}

			reinterpret_cast<T *>(_instance_buffer)->~T();
			_initialized = false;
		}

#endif // HAS_THREAD

		/* #endregion */

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
