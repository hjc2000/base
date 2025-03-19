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

template <typename T>
void ProhibitedInMCU()
{
	static_assert(false, "单片机中禁止使用。");
}

	// 如果没有线程，说明是单片机，此时将下面的 std 功能取消，因为非常耗费 flash 空间。
	#if !HAS_THREAD
		#define cout ProhibitedInMCU<bool>()
		#define endl ProhibitedInMCU<bool>()
		#define format(...) ProhibitedInMCU<bool>()
	#endif // !HAS_THREAD

#endif //__cplusplus
