#pragma once
#include <chrono>
#include <ctime>

namespace base
{
	class TimeSpan
	{
	private:
		std::chrono::nanoseconds _span;

	public:
		TimeSpan();

		explicit TimeSpan(std::chrono::nanoseconds const &value);
		explicit TimeSpan(std::chrono::microseconds const &value);
		explicit TimeSpan(std::chrono::seconds const &value);

		explicit operator std::chrono::nanoseconds() const;
		explicit operator std::chrono::microseconds() const;
		explicit operator std::chrono::seconds() const;
		explicit operator timespec() const;

#pragma region 加减运算符
		/// @brief 两个时间段相加，变成一个新的时间段。
		/// @param rhs
		/// @return
		base::TimeSpan operator+(base::TimeSpan const &rhs) const;

		/// @brief 两个时间段相减，得到一个新的时间段。
		/// @param rhs
		/// @return
		base::TimeSpan operator-(base::TimeSpan const &rhs) const;
#pragma endregion
	};
} // namespace base
