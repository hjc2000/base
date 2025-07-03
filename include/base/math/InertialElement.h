#pragma once
#include "base/math/Fraction.h"
#include "base/math/Int64Fraction.h"
#include "base/math/math.h"
#include "base/string/define.h"
#include <stdexcept>

namespace base
{
	///
	/// @brief 一阶惯性环节。
	///
	///
	template <typename T>
	class InertialElement final
	{
	private:
		T _inertial_time_constant{};
		T _sample_interval{};
		T _kx{};
		T _ky{};
		T _current_output{};
		T _resolution{};

	public:
		///
		/// @brief 一阶惯性环节。
		///
		/// @param inertial_time_constant 惯性时间常数。
		/// @param sample_interval 采样周期。
		/// @param resolution 计算的分辨率。
		///
		constexpr InertialElement(T inertial_time_constant,
								  T sample_interval,
								  T resolution)
		{
			if (resolution == 0)
			{
				throw std::invalid_argument{CODE_POS_STR + "分辨率不能是 0."};
			}

			_resolution = resolution;
			SetParameter(inertial_time_constant, sample_interval);
		}

		///
		/// @brief 向惯性环节输入一个值，并获取该值产生的输出。
		///
		/// @param x
		///
		/// @return
		///
		constexpr T Input(T x)
		{
			_current_output = _ky * _current_output + _kx * x;

			// 截断，保留整数倍的分辨率的部分，小于分辨率的丢弃。
			//
			// 注意，当 _resolution 很小时，_current_output / _resolution 很可能直接溢出。
			_current_output = base::floor(_current_output / _resolution) * _resolution;
			return _current_output;
		}

		///
		/// @brief 当前的输出。
		///
		/// @return
		///
		constexpr T CurrentOutput() const
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
		constexpr void SetCurrentOutput(T value)
		{
			_current_output = value;
		}

		///
		/// @brief 惯性时间常数。
		///
		/// @return
		///
		constexpr T InertialTimeConstant() const
		{
			return _inertial_time_constant;
		}

		///
		/// @brief 更改惯性时间常数
		///
		/// @param value
		///
		constexpr void SetInertialTimeConstant(T value)
		{
			_inertial_time_constant = value;
			_kx = _sample_interval / (_inertial_time_constant + _sample_interval);
			_ky = _inertial_time_constant / (_inertial_time_constant + _sample_interval);
		}

		///
		/// @brief 采样间隔。
		///
		/// @return
		///
		constexpr T SampleInterval() const
		{
			return _sample_interval;
		}

		///
		/// @brief 更改采样周期
		///
		/// @param value
		///
		constexpr void SetSampleInterval(T value)
		{
			_sample_interval = value;
			_kx = _sample_interval / (_inertial_time_constant + _sample_interval);
			_ky = _inertial_time_constant / (_inertial_time_constant + _sample_interval);
		}

		///
		/// @brief 更改惯性时间常数和采样周期。
		///
		/// @param inertial_time_constant
		/// @param sample_interval
		///
		constexpr void SetParameter(T inertial_time_constant,
									T sample_interval)
		{
			_inertial_time_constant = inertial_time_constant;
			_sample_interval = sample_interval;
			_kx = _sample_interval / (_inertial_time_constant + _sample_interval);
			_ky = _inertial_time_constant / (_inertial_time_constant + _sample_interval);
		}

		T Kx() const
		{
			return _kx;
		}

		T Ky() const
		{
			return _ky;
		}
	};

} // namespace base
