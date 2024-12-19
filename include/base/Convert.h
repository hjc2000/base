#pragma once
#include <stdexcept>
#include <stdint.h>
#include <string>

namespace base
{
	/// @brief 统一定义转换函数的样子。要实现转换逻辑时就特化一个本函数。
	/// @tparam ReturnType
	/// @tparam InputType
	/// @param o
	/// @return
	template <typename ReturnType, typename InputType>
	inline ReturnType Convert(InputType const &o) = delete;
} // namespace base
