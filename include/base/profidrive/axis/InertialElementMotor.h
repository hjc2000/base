#pragma once
#include "base/math/InertialElement.h"
#include "base/math/Int64Fraction.h"
#include <cstdint>

namespace base::profidrive
{
	///
	/// @brief 通过惯性环节模拟的电机。
	///
	///
	class InertialElementMotor
	{
	private:
		///
		/// @brief 使用一阶惯性环节模拟转矩环节。
		///
		///
		base::InertialElement<base::Int64Fraction> _torque_link{
			base::Int64Fraction{1},
			base::Int64Fraction{1, static_cast<int64_t>(1e9)},
			base::Int64Fraction{1, static_cast<int64_t>(1e32)},
		};

		base::Int64Fraction _given_speed{};

	public:
		constexpr InertialElementMotor() = default;

		///
		/// @brief 当前的给定速度。
		///
		/// @return
		///
		constexpr base::Int64Fraction GivenSpeed() const
		{
			return _given_speed;
		}

		///
		/// @brief 设置给定速度。
		///
		/// @param value
		///
		constexpr void SetGivenSpeed(base::Int64Fraction const &value)
		{
			_given_speed = value;
		}

		constexpr base::Int64Fraction FeedbackSpeed() const
		{
			return _torque_link.CurrentOutput();
		}
	};

} // namespace base::profidrive
