#pragma once
#include "base/Console.h"
#include "base/embedded/timer/InputCaptureTimer.h"
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

				base::console.Write("timer.CounterPeriod() = ");
				base::console.Write(std::to_string(timer.CounterPeriod()));
				base::console.WriteLine();

				timer.ConfigureChannel(channel_id,
									   base::input_capture_timer::CaptureEdge::RisingEdge,
									   1);

				uint32_t capture_value = 0;

				timer.SetCaptureCompleteCallback(
					[&](base::input_capture_timer::CaptureCompleteEventArgs const &args)
					{
						capture_value = args.CaptureValue();
					});

				timer.Start(channel_id);

				while (true)
				{
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
