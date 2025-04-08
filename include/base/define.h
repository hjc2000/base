#pragma once

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

#ifdef __cplusplus
	#include <cstdint> // IWYU pragma: keep

	///
	/// @brief 删除类的拷贝构造函数、拷贝赋值运算符、移动构造函数、移动赋值运算符
	///
	///
	#define DELETE_COPY_AND_MOVE(Class)           \
		Class(Class const &) = delete;            \
		Class(Class &&) = delete;                 \
		Class &operator=(Class const &) = delete; \
		Class &operator=(Class &&) = delete;

	#define CONCAT_IMPL(x, y) x##y
	#define CONCAT(x, y) CONCAT_IMPL(x, y)

	#define PREINIT(func)                                                    \
		namespace                                                            \
		{                                                                    \
			template <uint64_t UniqueID>                                     \
			class InitHelper                                                 \
			{                                                                \
			public:                                                          \
				InitHelper()                                                 \
				{                                                            \
					func();                                                  \
				}                                                            \
			};                                                               \
                                                                             \
			InitHelper<__COUNTER__> volatile CONCAT(_preinit_, __COUNTER__); \
		}

#endif
