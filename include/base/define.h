#pragma once

///
/// @brief 用来标记某个函数或类已经实现。
///
///
#define IMPLEMENTED

/* #region 强制内联 */

#if defined(_MSC_VER)
	// MSVC 编译器
	#define __base_force_inline __forceinline
#elif defined(__GNUC__) || defined(__clang__)
	// GCC 或 Clang 编译器
	#define __base_force_inline inline __attribute__((always_inline))
#else
	// 其他编译器（无法保证强制内联）
	#define __base_force_inline inline
#endif

/* #endregion */

///
/// @brief 弱符号。
///
#define __base_weak __attribute__((weak))

///
/// @brief 下面的宏仅用于 C++.
///
///
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

#endif // __cplusplus
