#pragma once
#include "base/Console.h"
#include "base/embedded/timer/BaseTimer.h"
#include "base/task/BinarySemaphore.h"
#include "base/task/task.h"
#include <chrono>
#include <cstdint>
#include <string>

namespace base
{
	namespace test
	{
		inline void TestBaseTimer(uint32_t base_timer_id)
		{
			base::task::run(
				[base_timer_id]()
				{
					base::base_timer::BaseTimer timer{base_timer_id};
					timer.Initialize(std::chrono::milliseconds{1000});
					base::task::BinarySemaphore semaphore{false};

					timer.SetPeriodElapsedCallback(
						[&]()
						{
							semaphore.ReleaseFromIsr();
						});

					timer.Start();

					while (true)
					{
						semaphore.Acquire();
						base::console().WriteLine("被定时器释放了。");
						base::console().WriteLine(std::to_string(timer.Period().count()));
					}
				});
		}

	} // namespace test
} // namespace base
