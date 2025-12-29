#pragma once
#include "base/math/DirectionDetecter.h"
#include <iostream>

namespace base::test
{
	inline void TestDirectionDetecter()
	{
		base::DirectionDetecter detecter{
			base::DirectionDetecter::RisingThreshold{20},
			base::DirectionDetecter::FallenThreshold{-10},
			base::DirectionDetecter::DirectionEnum::Falling,
			base::DirectionDetecter::InitialAnchor{0},
		};

		for (int i = 0; i < 40; i++)
		{
			detecter.Input(i);
			if (detecter.DirectionChange() == base::DirectionDetecter_DirectionChange::FromFallingToRising)
			{
				std::cout << "从下降变成上升。转折点" << detecter.TurningPoint() << std::endl;
			}
			else if (detecter.DirectionChange() == base::DirectionDetecter_DirectionChange::FromRisingToFalling)
			{
				std::cout << "从上升变成下降。转折点" << detecter.TurningPoint() << std::endl;
			}
		}

		for (int i = 40; i > 0; i--)
		{
			detecter.Input(i);
			if (detecter.DirectionChange() == base::DirectionDetecter_DirectionChange::FromFallingToRising)
			{
				std::cout << "从下降变成上升。转折点" << detecter.TurningPoint() << std::endl;
			}
			else if (detecter.DirectionChange() == base::DirectionDetecter_DirectionChange::FromRisingToFalling)
			{
				std::cout << "从上升变成下降。转折点" << detecter.TurningPoint() << std::endl;
			}
		}
	}

} // namespace base::test
