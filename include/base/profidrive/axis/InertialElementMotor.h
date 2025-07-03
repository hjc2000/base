#pragma once
#include "base/math/InertialElement.h"
#include "base/math/Int64Fraction.h"

namespace base
{
	namespace profidrive
	{
		class InertialElementMotor
		{
		private:
			base::InertialElement<base::Int64Fraction> _inertial_element{
				base::Int64Fraction{1},
				base::Int64Fraction{1, 100},
				base::Int64Fraction{1, 100000},
			};

		public:
			constexpr InertialElementMotor() = default;
		};

	} // namespace profidrive
} // namespace base
