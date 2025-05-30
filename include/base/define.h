#pragma once

///
/// @brief 用来标记某个函数或类已经实现。
///
///
#define IMPLEMENTED

/* #region 强制内联 */

#if defined(_MSC_VER)
	// MSVC 编译器
	#define FORCE_INLINE __forceinline
#elif defined(__GNUC__) || defined(__clang__)
	// GCC 或 Clang 编译器
	#define FORCE_INLINE inline __attribute__((always_inline))
#else
	// 其他编译器（无法保证强制内联）
	#define FORCE_INLINE inline
#endif

/* #endregion */

///
/// @brief 静态全局变量。
///
///
#define static_global static

///
/// @brief 静态函数
///
///
#define static_function static

///
/// @brief 静态字段
///
///
#define static_field static

#define CONCAT_IMPL(x, y) x##y
#define CONCAT(x, y) CONCAT_IMPL(x, y)

#ifdef __cplusplus

	#include <cstdint>   // IWYU pragma: keep
	#include <memory>    // IWYU pragma: keep
	#include <stdexcept> // IWYU pragma: keep

	///
	/// @brief 删除类的拷贝构造函数、拷贝赋值运算符、移动构造函数、移动赋值运算符
	///
	///
	#define DELETE_COPY_AND_MOVE(Class)           \
		Class(Class const &) = delete;            \
		Class(Class &&) = delete;                 \
		Class &operator=(Class const &) = delete; \
		Class &operator=(Class &&) = delete;

extern bool volatile _preinit_error;

	#define PREINIT(func)                              \
		namespace                                      \
		{                                              \
			struct                                     \
			{                                          \
				class InitHelper                       \
				{                                      \
				public:                                \
					InitHelper()                       \
					{                                  \
						try                            \
						{                              \
							func();                    \
						}                              \
						catch (...)                    \
						{                              \
							_preinit_error = true;     \
						}                              \
					}                                  \
				};                                     \
                                                       \
				InitHelper _init{};                    \
                                                       \
			} volatile CONCAT(_preinit_, __COUNTER__); \
		}

namespace base
{
	///
	/// @brief 自动指针。
	///
	/// @note 在有线程的平台上是共享指针，在无线程的平台上是裸指针。
	///
	///
	#if HAS_THREAD
	template <typename T>
	using AutoPtr = std::shared_ptr<T>;
	#else
	template <typename T>
	using AutoPtr = T *;
	#endif

} // namespace base

#endif // __cplusplus
