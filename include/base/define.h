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

#define CONCAT_IMPL(x, y) x##y
#define CONCAT(x, y) CONCAT_IMPL(x, y)

#ifdef __cplusplus
	#include <cstdint>   // IWYU pragma: keep
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

#endif
