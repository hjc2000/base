#include "delay.h"
#include <chrono>
#include <thread>

#if HAS_THREAD

void base::Delay(std::chrono::seconds const &time)
{
	std::this_thread::sleep_for(time);
}

void base::Delay(std::chrono::milliseconds const &time)
{
	std::this_thread::sleep_for(time);
}

void base::Delay(std::chrono::microseconds const &time)
{
	std::this_thread::sleep_for(time);
}

void base::Delay(std::chrono::nanoseconds const &time)
{
	std::this_thread::sleep_for(time);
}

void base::Delay(base::Seconds const &time)
{
	std::chrono::nanoseconds ns = static_cast<std::chrono::nanoseconds>(time);
	Delay(ns);
}

#endif
