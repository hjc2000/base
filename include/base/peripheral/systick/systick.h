#pragma once
#include "base/unit/MHz.h"
#include <cstdint>

namespace base
{
	namespace systick
	{
		///
		/// @brief 获取当前频率。
		///
		/// @return
		///
		base::MHz frequency();

		///
		/// @brief 获取当前的计数值。
		///
		/// @note systick 被认为是减计数的。如果实际上是增计数的，可以将本函数实现为返回计数最大值减去
		/// 当前值，这样就虚拟成减计数的了。
		///
		/// @return
		///
		uint64_t current_value();

		///
		/// @brief 计数器的重装载值。
		///
		/// @note 计数器减计数到 0 后，下一个时钟周期会重新变成 reload_value 的值。
		///
		/// @return
		///
		uint64_t reload_value();

	} // namespace systick
} // namespace base
