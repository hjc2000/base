#pragma once
#include "base/math/FastInt64Fraction.h"
#include "base/math/Fraction.h"
#include "Fraction.h"

namespace base
{
	///
	/// @brief 一阶惯性环节。
	///
	class InertialElement final
	{
	private:
		base::FastInt64Fraction _inertial_time_constant{};
		base::FastInt64Fraction _sample_interval{};
		base::FastInt64Fraction _kx{};
		base::FastInt64Fraction _ky{};
		base::FastInt64Fraction _current_output{};

	public:
		InertialElement() = default;

		///
		/// @brief 一阶惯性环节。
		///
		/// @param inertial_time_constant 惯性时间常数。
		/// @param sample_interval 采样周期。
		///
		InertialElement(base::FastInt64Fraction inertial_time_constant,
						base::FastInt64Fraction sample_interval)
		{
			SetParameter(inertial_time_constant, sample_interval);
		}

		///
		/// @brief 向惯性环节输入一个值，并获取该值产生的输出。
		///
		/// @param x
		///
		/// @return
		///
		base::FastInt64Fraction Input(base::FastInt64Fraction x)
		{
			_current_output *= _ky;
			_current_output += _kx * x;
			return _current_output;
		}

		///
		/// @brief 当前的输出。
		///
		/// @return
		///
		base::FastInt64Fraction CurrentOutput() const
		{
			return _current_output;
		}

		///
		/// @brief 直接更改当前输出值。
		///
		/// @note 可以用来更改惯性环节的初态。
		///
		/// @param value
		///
		void SetCurrentOutput(base::FastInt64Fraction value)
		{
			_current_output = value;
		}

		///
		/// @brief 惯性时间常数。
		///
		/// @return
		///
		base::FastInt64Fraction InertialTimeConstant() const
		{
			return _inertial_time_constant;
		}

		///
		/// @brief 更改惯性时间常数
		///
		/// @param value
		///
		void SetInertialTimeConstant(base::FastInt64Fraction value)
		{
			_inertial_time_constant = value;
			base::Fraction kx = base::Fraction{_sample_interval} / (base::Fraction{_inertial_time_constant} + base::Fraction{_sample_interval});
			base::Fraction ky = base::Fraction{_inertial_time_constant} / (base::Fraction{_inertial_time_constant} + base::Fraction{_sample_interval});
			_kx = static_cast<base::FastInt64Fraction>(kx);
			_ky = static_cast<base::FastInt64Fraction>(ky);
		}

		///
		/// @brief 采样间隔。
		///
		/// @return
		///
		base::FastInt64Fraction SampleInterval() const
		{
			return _sample_interval;
		}

		///
		/// @brief 更改采样周期
		///
		/// @param value
		///
		void SetSampleInterval(base::FastInt64Fraction value)
		{
			_sample_interval = value;
			base::Fraction kx = base::Fraction{_sample_interval} / (base::Fraction{_inertial_time_constant} + base::Fraction{_sample_interval});
			base::Fraction ky = base::Fraction{_inertial_time_constant} / (base::Fraction{_inertial_time_constant} + base::Fraction{_sample_interval});
			_kx = static_cast<base::FastInt64Fraction>(kx);
			_ky = static_cast<base::FastInt64Fraction>(ky);
		}

		///
		/// @brief 更改惯性时间常数和采样周期。
		///
		/// @param inertial_time_constant
		/// @param sample_interval
		///
		void SetParameter(base::FastInt64Fraction inertial_time_constant,
						  base::FastInt64Fraction sample_interval)
		{
			_inertial_time_constant = inertial_time_constant;
			_sample_interval = sample_interval;
			base::Fraction kx = base::Fraction{_sample_interval} / (base::Fraction{_inertial_time_constant} + base::Fraction{_sample_interval});
			base::Fraction ky = base::Fraction{_inertial_time_constant} / (base::Fraction{_inertial_time_constant} + base::Fraction{_sample_interval});
			_kx = static_cast<base::FastInt64Fraction>(kx);
			_ky = static_cast<base::FastInt64Fraction>(ky);
		}

		base::FastInt64Fraction Kx() const
		{
			return _kx;
		}

		base::FastInt64Fraction Ky() const
		{
			return _ky;
		}
	};

} // namespace base
