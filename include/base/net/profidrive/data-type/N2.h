#pragma once
#include <base/math/Fraction.h>

namespace base
{
	/// @brief profidrive 行规特定类型: N2.
	class N2
	{
	private:
		int16_t _value{};

	public:
		N2() = default;
		N2(base::Fraction const &value);

		int16_t Value() const
		{
			return _value;
		}

		/// @brief 强制转换为分数类型。
		explicit operator base::Fraction() const;

		/// @brief 等同 Value 属性。
		explicit operator int16_t() const
		{
			return _value;
		}
	};
} // namespace base
