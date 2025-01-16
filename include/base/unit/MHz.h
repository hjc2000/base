#pragma once
#include <base/unit/IUnit.h>

namespace base
{
	class Seconds;
	class Hz;

	/// @brief 频率单位：MHz.
	class MHz :
		public base::IUnit<MHz>
	{
	private:
		base::Fraction _value{0};

	public:
		/// @brief 0Hz
		MHz() = default;

		/// @brief 拷贝构造函数。
		/// @param o
		MHz(MHz const &o);

		/// @brief 从分数构造频率。
		/// @param value
		MHz(base::Fraction const &value);

		MHz(base::Hz const &value);

		/// @brief 构造整数频率。
		/// @param value
		MHz(int64_t value);

		/// @brief 从秒构造频率。Hz 是 s 的倒数。
		/// @param value
		MHz(base::Seconds const &value);

		/// @brief 赋值运算符。
		/// @param o
		/// @return
		MHz &operator=(MHz const &o);

		virtual base::Fraction &Value() override
		{
			return _value;
		}
	};
} // namespace base
