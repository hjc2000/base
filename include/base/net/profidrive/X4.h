#pragma once
#include <base/math/Fraction.h>

namespace base
{
	/// @brief profidrive 行规特定类型: X4.
	class X4
	{
	private:
		int32_t _value{};

	public:
		X4() = default;
		X4(base::Fraction const &value);

		int32_t Value() const
		{
			return _value;
		}

		/// @brief 强制转换为分数类型。
		explicit operator base::Fraction() const;

		/// @brief 等同 Value 属性。
		explicit operator int32_t() const
		{
			return _value;
		}
	};
} // namespace base
