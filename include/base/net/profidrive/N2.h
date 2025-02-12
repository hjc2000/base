#pragma once
#include <base/math/Fraction.h>

namespace base
{
	/// @brief profidrive 行规特定类型: N2.
	class N2
	{
	private:
		int32_t _value{};

	public:
		N2() = default;
		N2(base::Fraction const &value);

		/// @brief 强制转换为分数类型。
		explicit operator base::Fraction() const;
	};
} // namespace base
