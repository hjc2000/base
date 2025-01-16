#pragma once
#include <base/unit/IUnit.h>

namespace base
{
	class Seconds;
	class MHz;

	/// @brief 频率单位：Hz.
	class Hz :
		public base::IUnit<Hz>
	{
	private:
		base::Fraction _value{0};

	public:
		/// @brief 0Hz
		Hz() = default;

		/// @brief 拷贝构造函数。
		/// @param o
		Hz(Hz const &o);

		/// @brief 从分数构造频率。
		/// @param value
		explicit Hz(base::Fraction const &value);

		explicit Hz(base::MHz const &value);

		/// @brief 构造整数频率。
		/// @param value
		explicit Hz(int64_t value);

		/// @brief 从秒构造频率。Hz 是 s 的倒数。
		/// @param value
		explicit Hz(base::Seconds const &value);

		/// @brief 赋值运算符。
		/// @param o
		/// @return
		Hz &operator=(Hz const &o);

		virtual base::Fraction &Value() override
		{
			return _value;
		}
	};
} // namespace base
