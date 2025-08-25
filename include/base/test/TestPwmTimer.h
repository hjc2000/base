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
			timer.InitializeAsUpMode(base::unit::Hz{20 * 1000});

			timer.ConfigureOutput(channel_id,
								  base::pwm_timer::Polarity::Positive,
								  base::pwm_timer::Polarity::Negative,
								  timer.Cycle() / 10,
								  0);

			base::console.Write("timer.Cycle(): ");
			base::console.Write(std::to_string(timer.Cycle()));
			base::console.WriteLine();

			timer.Start(channel_id);
		}

	} // namespace test
} // namespace base
