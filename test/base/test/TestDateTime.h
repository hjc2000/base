#pragma once
#include "base/time/convert.h"
#include "base/time/time.h"
#include "base/time/TimePointSinceEpoch.h"
#include <chrono>
#include <iostream>

namespace base::test
{
	inline void TestDateTime()
	{
		base::TimePointSinceEpoch now_time_point = base::time::Now();

		base::DateTime now{
			base::UtcHourOffset{8},
			now_time_point,
		};

		base::DateTimeStringBuilder dsb = now.LocalDateTimeStringBuilder();
		dsb.SetYearMonthDaySeparator('/');

		std::cout << dsb << std::endl;
		std::cout << base::to_string(now_time_point) << std::endl;
		std::cout << static_cast<std::chrono::nanoseconds>(now_time_point) << std::endl;
		std::cout << static_cast<std::chrono::nanoseconds>(now.TimePointSinceEpoch()) << std::endl;
	}

} // namespace base::test
