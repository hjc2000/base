#pragma once
#include <base/math/Fraction.h>

namespace base
{
	/// @brief profidrive 行规特定类型：N4.
	class N4
	{
	private:
		int32_t _value{};

	public:
		N4() = default;
		N4(base::Fraction const &value);

		/// @brief 强制转换为分数类型。
		explicit operator base::Fraction() const;
	};
} // namespace base
