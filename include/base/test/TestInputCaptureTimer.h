#pragma once
#include "base/Console.h"
#include "base/embedded/timer/InputCaptureTimer.h"
#include "base/embedded/timer/InputCaptureTimerPll.h"
#include "base/math/Int64Fraction.h"
#include "base/task/BinarySemaphore.h"
#include "base/task/delay.h"
#include "base/task/task.h"
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
				timer.Initialize(std::chrono::milliseconds{1000});
				base::task::BinarySemaphore semaphore{false};

				base::InputCaptureTimerPll<uint16_t> pll{
					timer,
					base::Int64Fraction{1, 10},
					10,
					0,
				};

				timer.ConfigureChannel(channel_id,
									   base::input_capture_timer::CaptureEdge::RisingEdge,
									   1);

				uint32_t capture_value = 0;

				timer.SetCaptureCompleteCallback(
					[&](base::input_capture_timer::CaptureCompleteEventArgs const &args)
					{
						capture_value = args.CaptureValue();
					});

				timer.SetPeriodElapsedCallback(
					[&]()
					{
						semaphore.ReleaseFromIsr();
					});

				timer.Start(channel_id);

				while (true)
				{
					semaphore.Acquire();
					pll.Adjust(capture_value);

					base::console.Write("timer.CounterPeriod() = ");
					base::console.Write(std::to_string(timer.CounterPeriod()));
					base::console.WriteLine();

					base::console.Write("捕获值：");
					base::console.Write(std::to_string(capture_value));
					base::console.WriteLine();

					base::task::Delay(std::chrono::milliseconds{1000});
				}
			};

			base::task::run(task_func);
		}

	} // namespace test
} // namespace base
