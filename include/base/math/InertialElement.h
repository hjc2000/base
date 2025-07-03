#pragma once

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

	public:
		/* #region 参数类 */

		///
		/// @brief 惯性时间常数
		///
		///
		class TimeConstant
		{
		private:
			T _value = 0;

		public:
			constexpr explicit TimeConstant(T value)
			{
				_value = value;
			}

			constexpr T Value() const
			{
				return _value;
			}
		};

		///
		/// @brief 采样周期
		///
		///
		class SampleInterval
		{
		private:
			T _value = 0;

		public:
			constexpr explicit SampleInterval(T value)
			{
				_value = value;
			}

			constexpr T Value() const
			{
				return _value;
			}
		};

		/* #endregion */

		///
		/// @brief 一阶惯性环节。
		///
		/// @param inertial_time_constant 惯性时间常数。
		/// @param sample_interval 采样周期。
		///
		constexpr InertialElement(T inertial_time_constant,
								  T sample_interval)
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
		constexpr T Input(T x)
		{
			_current_output = _ky * _current_output + _kx * x;
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
	};

} // namespace base
