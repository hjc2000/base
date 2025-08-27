#pragma once
#include "base/embedded/timer/InputCaptureTimer.h"
#include "base/math/Int64Fraction.h"
#include "base/math/math.h"
#include <cstdint>
#include <type_traits>

namespace base
{
	template <typename CounterType>
		requires(std::is_unsigned_v<CounterType>)
	class InputCaptureTimerPll
	{
	private:
		base::input_capture_timer::InputCaptureTimer &_timer;
		base::Int64Fraction _kp{1, 10};
		CounterType _origin_period{};
		CounterType _adjust_limit{};
		CounterType _expected_capture_value{};
		bool _current_capture_value_changed = false;
		CounterType _current_capture_value{};
		CounterType _current_capture_value_interpolation{};

	public:
		InputCaptureTimerPll(base::input_capture_timer::InputCaptureTimer &timer,
							 base::Int64Fraction const &kp,
							 CounterType adjust_limit,
							 CounterType expected_capture_value)
			: _timer(timer)
		{
			_kp = kp;
			_origin_period = timer.CounterPeriod();
			_adjust_limit = adjust_limit;
			_expected_capture_value = expected_capture_value;
			_current_capture_value = expected_capture_value;
			_current_capture_value_interpolation = expected_capture_value;
		}

		void UpdateCaptureValue(CounterType capture_value)
		{
			_current_capture_value = capture_value;
			_current_capture_value_changed = true;
		}

		void Adjust()
		{
			try
			{
				if (_current_capture_value_changed)
				{
					_current_capture_value_changed = false;
					_current_capture_value_interpolation = _current_capture_value;
				}

				int64_t error = static_cast<int64_t>(_current_capture_value_interpolation) - static_cast<int64_t>(_expected_capture_value);
				error %= _origin_period;
				if (error > _origin_period / 2)
				{
					error -= _origin_period;
				}

				base::Int64Fraction kp_factor = base::Int64Fraction{base::abs(error)} * 20 / _origin_period;
				if (kp_factor < 1)
				{
					// 非线性优化。
					//
					// 误差很大，大于 1/20 的 _origin_period 时，kp_factor 大于 1, 并且误差越大，
					// kp_factor 越大。
					//
					// 让 kp 乘上 kp_factor, 就可以实现大误差时增大比例系数。
					//
					// 当 kp_factor 小于 1 时，说明误差小于 1/20 的 _origin_period, 此时让 kp_factor
					// 等于 1, 即使用原始的 kp 值进行调整。
					kp_factor = 1;
				}

				int64_t delta = static_cast<int64_t>(_kp * kp_factor * error);

				if (error != 0 && delta == 0)
				{
					// 误差过小，乘上 kp 后截断了，但是误差确实存在，需要调整。
					if (base::abs(error) > 1)
					{
						delta = error / 2;
					}
					else
					{
						delta = error / error;
					}
				}

				if (delta > static_cast<int64_t>(_adjust_limit))
				{
					delta = static_cast<int64_t>(_adjust_limit);
				}
				else if (delta < -static_cast<int64_t>(_adjust_limit))
				{
					delta = -static_cast<int64_t>(_adjust_limit);
				}

				int64_t period = static_cast<int64_t>(_origin_period) + delta;
				if (period < 1)
				{
					period = 1;
				}

				_timer.SetCounterPeriodPreloadValue(period);

				// 因为定时时间到中断触发的频率比捕获中断触发的频率高，所以在下次捕获前需要对
				// 捕获值进行插值。
				_current_capture_value_interpolation -= delta;
			}
			catch (...)
			{
			}
		}
	};

} // namespace base
