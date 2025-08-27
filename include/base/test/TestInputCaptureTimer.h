#pragma once
#include "base/Console.h"
#include "base/embedded/timer/InputCaptureTimer.h"
#include "base/embedded/timer/InputCaptureTimerPll.h"
#include "base/math/Int64Fraction.h"
#include "base/task/BinarySemaphore.h"
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
		inline void TestInputCaptureTimer(uint32_t timer_id, uint32_t channel_id)
		{
			auto task_func = [timer_id, channel_id]()
			{
				base::input_capture_timer::InputCaptureTimer timer{timer_id};
				base::unit::Nanosecond period{50 * 1000};
				base::unit::Hz pwm_frequency{1 * 1000};
				base::unit::Nanosecond pwm_period{pwm_frequency};
				timer.Initialize(std::chrono::microseconds{period});
				base::task::BinarySemaphore semaphore{false};

				base::InputCaptureTimerPll<uint16_t> pll{
					timer,
					static_cast<base::Int64Fraction>(period / pwm_period),
					static_cast<uint16_t>(timer.CounterPeriod() / 10),
					233,
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
						pll.Adjust();
						semaphore.ReleaseFromIsr();
					});

				timer.Start(channel_id);

				uint32_t loop_times = 0;
				while (true)
				{
					semaphore.Acquire();

					if (loop_times % 1000 == 0)
					{
						base::console.Write("timer.CounterPeriod() = ");
						base::console.Write(std::to_string(timer.CounterPeriod()));
						base::console.WriteLine();

						base::console.Write("捕获值：");
						base::console.Write(std::to_string(capture_value));
						base::console.WriteLine();

						base::task::Delay(std::chrono::milliseconds{1000});
					}

					loop_times++;
					loop_times %= 1000;
				}
			};

			base::task::run(2, 1024 * 2, task_func);
		}

	} // namespace test
} // namespace base
