#pragma once
#include <base/unit/IUnit.h>

namespace base
{
	class Seconds;
	class Nanoseconds;
	class Hz;

	/// @brief 频率单位：MHz.
	class MHz :
		public base::IUnit<MHz>
	{
	private:
		base::Fraction _value{};

	public:
		/// @brief 0Hz
		MHz() = default;

		/// @brief 从分数构造频率。
		/// @param value
		explicit MHz(base::Fraction const &value);

		explicit MHz(base::Hz const &value);

		/// @brief 构造整数频率。
		/// @param value
		explicit MHz(int64_t value);

		/// @brief 从秒构造频率。Hz 是 s 的倒数。
		/// @param value
		explicit MHz(base::Seconds const &value);

		explicit MHz(base::Nanoseconds const &value);

	public:
		virtual base::Fraction &Value() override
		{
			return _value;
		}

		/// @brief 单位的字符串。
		/// @return
		virtual std::string UnitString() const override;
	};
} // namespace base
