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

		base::DateTime now_date_time{
			base::UtcHourOffset{8},
			now_time_point,
		};

		base::DateTimeStringBuilder date_time_string_builder = now_date_time.LocalDateTimeStringBuilder();
		date_time_string_builder.SetYearMonthDaySeparator('/');

		std::cout << static_cast<std::chrono::nanoseconds>(now_time_point) << std::endl;
		std::cout << static_cast<std::chrono::nanoseconds>(now_date_time.TimePointSinceEpoch()) << std::endl;
		std::cout << date_time_string_builder << std::endl;
		std::cout << base::to_string(base::Convert<base::ns_zoned_time>(base::UtcHourOffset{8}, now_time_point)) << std::endl;
	}

} // namespace base::test
