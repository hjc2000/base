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
	};
} // namespace base
