#pragma once
#include <base/unit/IUnit.h>
#include <chrono>

namespace base
{
	class Hz;
	class MHz;
	class Hours;
	class Minutes;
	class Seconds;
	class Nanoseconds;

	/// @brief 纳秒
	class Nanoseconds :
		public base::IUnit<Nanoseconds>
	{
	private:
		base::Fraction _value{};

	public:
		Nanoseconds() = default;
		explicit Nanoseconds(base::Fraction const &value);
		explicit Nanoseconds(int64_t value);
		explicit Nanoseconds(base::Hours const &value);
		explicit Nanoseconds(base::Minutes const &value);
		explicit Nanoseconds(base::Seconds const &value);
		explicit Nanoseconds(base::Hz const &value);
		explicit Nanoseconds(base::MHz const &value);
		explicit Nanoseconds(std::chrono::seconds const &value);
		explicit Nanoseconds(std::chrono::milliseconds const &value);
		explicit Nanoseconds(std::chrono::microseconds const &value);

		virtual base::Fraction &Value() override
		{
			return _value;
		}

		/// @brief 单位的字符串。
		/// @return
		virtual std::string UnitString() const override;

#pragma region 强制转换运算符
		explicit operator std::chrono::seconds() const;
		explicit operator std::chrono::milliseconds() const;
		explicit operator std::chrono::microseconds() const;
#pragma endregion
	};
} // namespace base
