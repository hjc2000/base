#include "test_zoned_time.h"
#include "base/time/TimePointSinceEpoch.h"
#include <iostream>

#if HAS_THREAD

void base::test::test_zoned_time()
{
	base::TimePointSinceEpoch now{std::chrono::system_clock::now()};
	std::cout << now.NanosecondsZonedTimeString() << std::endl;
	std::cout << now.MicrosecondsZonedTimeString() << std::endl;
	std::cout << now.MillisecondsZonedTimeString() << std::endl;
	std::cout << now.SecondsZonedTimeString() << std::endl;
}

#endif
