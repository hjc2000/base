#pragma once
#include "base/unit/IUnit.h"

namespace base
{
	class Seconds;
	class Nanoseconds;
	class MHz;

	/// @brief 频率单位：Hz.
	class Hz :
		public base::IUnit<Hz>
	{
	private:
		base::Fraction _value{};

	public:
		///
		/// @brief 0 Hz
		///
		///
		Hz() = default;

		///
		/// @brief 从分数构造频率。
		///
		/// @param value
		///
		explicit Hz(base::Fraction const &value);

		explicit Hz(base::MHz const &value);

		///
		/// @brief 构造整数频率。
		///
		/// @param value
		///
		explicit Hz(int64_t value);

		///
		/// @brief 从秒构造频率。Hz 是 s 的倒数。
		///
		/// @param value
		///
		explicit Hz(base::Seconds const &value);

		explicit Hz(base::Nanoseconds const &value);

		///
		/// @brief 单位的值。
		///
		/// @return base::Fraction&
		///
		virtual base::Fraction &Value() override
		{
			return _value;
		}

		///
		/// @brief 单位的字符串。
		///
		/// @return std::string
		///
		virtual std::string UnitString() const override;
	};
} // namespace base
