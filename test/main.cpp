#include "base/test/TestDateTime.h"
#include "base/time/DateTime.h"
#include "base/time/time.h"
#include "base/time/TimePointSinceEpoch.h"
#include "base/time/TimeSpan.h"
#include "base/time/UtcHourOffset.h"
#include "base/unit/Day.h"
#include <cstdint>  // IWYU pragma: keep
#include <iostream> // IWYU pragma: keep

int main()
{
	base::test::TestDateTime();

	{
		base::TimePointSinceEpoch now_time_point = base::time::Now();

		base::DateTime new_year_date{
			base::UtcHourOffset{8},
			2026,
			2,
			14,
			0,
			0,
			0,
			0,
		};

		base::TimePointSinceEpoch new_year_time_point = new_year_date.TimePointSinceEpoch();
		base::TimeSpan time_span = new_year_time_point - now_time_point;
		base::unit::Day days = static_cast<base::unit::Day>(time_span);
		std::cout << days << std::endl;
		std::cout << static_cast<double>(days) << std::endl;
		std::cout << static_cast<int64_t>(days) << std::endl;
	}

	return 0;
}
