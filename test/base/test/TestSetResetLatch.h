#pragma once
#include "base/digital_circuit/SetResetLatch.h"
#include <cstdint>
#include <format>
#include <iostream>
#include <string>

namespace base::test
{
	inline void TestSetResetLatch()
	{
		base::digital_circuit::SetResetLatch set_reset_latch{10};

		{
			std::string log = std::format("set_reset_latch.Output() = {}",
										  set_reset_latch.Output());

			std::cout << log << std::endl;
		}

		for (int32_t i = 0; i < 11; i++)
		{
			set_reset_latch.Input(true);

			std::string log = std::format("i = {}, set_reset_latch.Output() = {}",
										  i,
										  set_reset_latch.Output());

			std::cout << log << std::endl;
		}

		set_reset_latch.Reset();

		{
			std::string log = std::format("set_reset_latch.Output() = {}",
										  set_reset_latch.Output());

			std::cout << log << std::endl;
		}
	}

} // namespace base::test
