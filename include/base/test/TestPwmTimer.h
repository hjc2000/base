#pragma once
#include "base/Console.h"
#include "base/embedded/timer/PwmTimer.h"
#include "base/unit/Hz.h"
#include <cstdint>
#include <string>

namespace base
{
	namespace test
	{
		inline void TestPwmTimer(uint32_t pwm_timer_id, uint32_t channel_id)
		{
			base::pwm_timer::PwmTimer timer{pwm_timer_id};
			timer.InitializeAsUpMode(base::unit::Hz{1 * 1000});

			timer.ConfigureOutput(channel_id,
								  base::pwm_timer::Polarity::Positive,
								  timer.CounterPeriod() * 9 / 10,
								  0);

			base::console().Write("timer.CounterPeriod() = ");
			base::console().Write(std::to_string(timer.CounterPeriod()));
			base::console().WriteLine();

			timer.Start();
			timer.StartChannel(channel_id);
		}

	} // namespace test
} // namespace base
