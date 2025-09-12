#pragma once
#include "base/Console.h"
#include "base/embedded/timer/InputCaptureTimer.h"
#include "base/embedded/timer/InputCaptureTimerPll.h"
#include "base/task/delay.h"
#include "base/task/task.h"
#include "base/unit/Hz.h"
#include "base/unit/Nanosecond.h"
#include <chrono>
#include <cstdint>
#include <string>

namespace base
{
	namespace test
	{
		inline void TestInputCaptureTimer(uint32_t timer_id,
										  uint32_t channel_id,
										  int64_t frequency_multiple)
		{
			auto task_func = [timer_id, channel_id, frequency_multiple]()
			{
				base::input_capture_timer::InputCaptureTimer timer{timer_id};
				base::unit::Nanosecond period{60 * 1000};
				base::unit::Hz pwm_frequency{1 * 1000};
				base::unit::Nanosecond pwm_period{pwm_frequency};
				timer.Initialize(std::chrono::microseconds{period});

				base::InputCaptureTimerPll pll{
					timer,
					frequency_multiple,
					666,
				};

				timer.ConfigureChannel(channel_id,
									   base::input_capture_timer::CaptureEdge::RisingEdge,
									   1);

				uint32_t volatile capture_value = 0;

				timer.SetCaptureCompleteCallback(
					[&](base::input_capture_timer::CaptureCompleteEventArgs const &args)
					{
						capture_value = args.CaptureValue();
						pll.UpdateCaptureValue(capture_value);
					});

				timer.SetPeriodElapsedCallback(
					[&]()
					{
						pll.OnPeriodElapsed();
					});

				timer.Start();
				timer.StartChannel(channel_id);

				while (true)
				{
					base::console().Write("timer.CounterPeriod: ");
					base::console().Write(std::to_string(timer.CounterPeriod()));
					base::console().WriteLine();

					base::console().Write("pll.CurrentCaptureRegisterValue: ");
					base::console().Write(std::to_string(pll.CurrentCaptureRegisterValue()));
					base::console().WriteLine();

					base::console().Write("pll.CurrentCaptureValue: ");
					base::console().Write(std::to_string(pll.CurrentCaptureValue()));
					base::console().WriteLine();

					base::console().Write("pll.CapturedSignalPeriod: ");
					base::console().Write(std::to_string(pll.CapturedSignalPeriod()));
					base::console().WriteLine();

					base::console().Write("pll.FrequencyError: ");
					base::console().Write(std::to_string(pll.FrequencyError()));
					base::console().WriteLine();

					base::console().Write("pll.PhaseError: ");
					base::console().Write(std::to_string(pll.PhaseError()));
					base::console().WriteLine();

					base::console().WriteLine();
					base::task::Delay(std::chrono::milliseconds{1000});
				}
			};

			base::task::run(1, 1024 * 4, task_func);
		}

	} // namespace test
} // namespace base
