#include "test_zoned_time.h"
#include "base/time/time.h"
#include "base/time/TimePointSinceEpoch.h"
#include <iostream>

#if HAS_THREAD

void base::test::test_zoned_time()
{
	base::TimePointSinceEpoch now = base::time::Now();
	std::cout << now.NanosecondsZonedTimeString() << std::endl;
	std::cout << now.MicrosecondsZonedTimeString() << std::endl;
	std::cout << now.MillisecondsZonedTimeString() << std::endl;
	std::cout << now.SecondsZonedTimeString() << std::endl;
}

#endif
