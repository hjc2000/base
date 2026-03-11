#pragma once
#include "base/task/task.h" // IWYU pragma: keep
#include <cstdint>          // IWYU pragma: keep
#include <new>              // IWYU pragma: keep

namespace base
{
	///
	/// @brief 单例提供者。
	///
	/// @note 本类需要被实例化为一个全局对象，然后获取单例时从这个本类
	/// 的全局对象中获取。
	///
	/// @note 直接将需要作为单例的类型定义为全局对象，会有构造顺序的问题，
	/// 本类避免了这个问题，可以放心将本类定义为全局对象，这样就可以获得想要
	/// 的类型的单例了。
	///
	/// @note 可以参考本项目中 StdOutStreamProvider.h 中的 StdOutStreamProvider 类
	/// 的做法。
	///
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
