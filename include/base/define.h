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

	///
	/// @brief 删除类的拷贝构造函数、拷贝赋值运算符、移动构造函数、移动赋值运算符
	///
	///
	#define DELETE_COPY_AND_MOVE(Class)           \
		Class(Class const &) = delete;            \
		Class(Class &&) = delete;                 \
		Class &operator=(Class const &) = delete; \
		Class &operator=(Class &&) = delete;

	#define REGISTER_PREINIT(func) \
		namespace                  \
		{                          \
			class Init             \
			{                      \
			public:                \
				Init()             \
				{                  \
					func();        \
				}                  \
			};                     \
                                   \
			Init volatile _init{}; \
		}

#endif
