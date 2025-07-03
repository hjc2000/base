#pragma once
#include "base/math/InertialElement.h"
#include "base/math/Int64Fraction.h"

namespace base
{
	namespace profidrive
	{
		///
		/// @brief 通过惯性环节模拟的电机。
		///
		///
		class InertialElementMotor
		{
		private:
			base::InertialElement<base::Int64Fraction> _inertial_element{
				base::Int64Fraction{1},
				base::Int64Fraction{1, 100},
				base::Int64Fraction{1, 100000},
			};

			base::Int64Fraction _input_speed{};

		public:
			constexpr InertialElementMotor() = default;

			constexpr base::Int64Fraction InputSpeed() const
			{
				return _input_speed;
			}

			constexpr void SetInputSpeed(base::Int64Fraction const &value)
			{
				_input_speed = value;
			}
		};

	} // namespace profidrive
} // namespace base
