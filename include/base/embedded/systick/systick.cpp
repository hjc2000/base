#include "systick.h" // IWYU pragma: keep
#include "base/unit/MHz.h"
#include "base/unit/Nanosecond.h"
#include <chrono>
#include <cstdint>

/* #region 延时函数 */

void base::systick::delay_for_ticks(uint64_t value)
{
	uint64_t last_tick = base::systick::current_value();
	uint64_t total_tick = 0;
	while (true)
	{
		uint64_t current_tick = base::systick::current_value();
		if (last_tick == current_tick)
		{
			// CPU 太快了，导致再次进入循环后 SysTic 没来得及递增计数，所以 old_tick == now_tick
			continue;
		}

		uint64_t delta_tick = 0;
		if (last_tick > current_tick)
		{
			// 因为是减计数，所以此时没有发生环绕
			delta_tick = last_tick - current_tick;
		}
		else
		{
			// 发生了环绕
			// delta_tick = old_tick - (now_tick - reload)
			// delta_tick = old_tick - now_tick + reload
			delta_tick = last_tick - current_tick + base::systick::reload_value();
		}

		total_tick += delta_tick;
		if (total_tick >= value)
		{
			return;
		}

		last_tick = current_tick;
	}
}

void base::systick::delay(std::chrono::nanoseconds const &value)
{
	base::unit::Nanosecond tick_interval{base::systick::frequency()};
	uint64_t tick_count = static_cast<uint64_t>(base::unit::Nanosecond{value} / tick_interval);
	base::systick::delay_for_ticks(tick_count);
}

void base::systick::delay(std::chrono::microseconds const &value)
{
	base::unit::Nanosecond tick_interval{base::systick::frequency()};
	uint64_t tick_count = static_cast<uint64_t>(base::unit::Nanosecond{value} / tick_interval);
	base::systick::delay_for_ticks(tick_count);
}

void base::systick::delay(std::chrono::milliseconds const &value)
{
	base::unit::Nanosecond tick_interval{base::systick::frequency()};
	uint64_t tick_count = static_cast<uint64_t>(base::unit::Nanosecond{value} / tick_interval);
	base::systick::delay_for_ticks(tick_count);
}

void base::systick::delay(std::chrono::seconds const &value)
{
	base::unit::Nanosecond tick_interval{base::systick::frequency()};
	uint64_t tick_count = static_cast<uint64_t>(base::unit::Nanosecond{value} / tick_interval);
	base::systick::delay_for_ticks(tick_count);
}

void base::systick::delay(base::unit::Nanosecond const &value)
{
	base::systick::delay(static_cast<std::chrono::nanoseconds>(value));
}

void base::systick::delay(base::unit::Second const &value)
{
	base::systick::delay(static_cast<std::chrono::nanoseconds>(value));
}

/* #endregion */
