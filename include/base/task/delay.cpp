#include "delay.h"
#include <chrono>
#include <thread>

#if HAS_THREAD

void base::task::Delay(std::chrono::seconds const &time)
{
	std::this_thread::sleep_for(time);
}

void base::task::Delay(std::chrono::milliseconds const &time)
{
	std::this_thread::sleep_for(time);
}

void base::task::Delay(std::chrono::microseconds const &time)
{
	std::this_thread::sleep_for(time);
}

void base::task::Delay(std::chrono::nanoseconds const &time)
{
	std::this_thread::sleep_for(time);
}

#endif
