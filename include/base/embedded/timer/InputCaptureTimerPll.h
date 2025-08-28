#pragma once
#include "base/Console.h"
#include "base/embedded/timer/InputCaptureTimer.h"
#include "base/math/Int64Fraction.h"
#include "base/math/math.h"
#include "base/math/PID.h"
#include "base/string/define.h"
#include <cstdint>
#include <stdexcept>
#include <type_traits>

namespace base
{
	template <typename CounterType>
		requires(std::is_unsigned_v<CounterType>)
	class InputCaptureTimerPll
	{
	private:
		base::input_capture_timer::InputCaptureTimer &_timer;
		base::Int64Fraction _multiple = 1;
		CounterType _origin_period{};
		CounterType _adjust_limit{};
		CounterType _expected_capture_value{};

		bool _current_capture_register_value_changed = false;
		CounterType _current_capture_register_value{};
		int64_t _additional_capture_period = 0;

		int64_t _last_capture_value{};
		int64_t _current_capture_value{};
		int64_t _delta_capture_value{};

		base::PID<base::Int64Fraction> _pid{};
		bool _adjust_started = false;

	public:
		InputCaptureTimerPll(base::input_capture_timer::InputCaptureTimer &timer,
							 base::Int64Fraction const &multiple,
							 CounterType adjust_limit,
							 CounterType expected_capture_value)
			: _timer(timer)
		{
			if (multiple <= 0)
			{
				throw std::invalid_argument{CODE_POS_STR + "非法倍数。"};
			}

			_multiple = multiple;
			_origin_period = timer.CounterPeriod();
			_adjust_limit = adjust_limit;
			_expected_capture_value = expected_capture_value;
			_current_capture_register_value = expected_capture_value;
			_current_capture_value = expected_capture_value;

			_pid = base::PID<base::Int64Fraction>{
				base::Int64Fraction{1, 100},
				base::Int64Fraction{1, 10000},
				0,
				base::Int64Fraction{1, INT16_MAX},
				static_cast<int64_t>(adjust_limit),
				-static_cast<int64_t>(adjust_limit),
			};

			base::console.WriteLine(std::string{"multiple = "} + multiple.ToString());
		}

		void UpdateCaptureValue(CounterType capture_value)
		{
			_current_capture_register_value = capture_value;
			_current_capture_register_value_changed = true;
		}

		void Adjust()
		{
			try
			{
				if (!_current_capture_register_value_changed)
				{
					// 捕获值没有更新，而是定时器溢出，触发一次定时时间到中断，计数器清零了。
					// 下次捕获值要加上 _additional_capture_period 才是真实的距离上次捕获过去的时间。
					_additional_capture_period += _timer.CounterPeriod();
					return;
				}

				_current_capture_register_value_changed = false;
				_last_capture_value = _current_capture_value;
				_current_capture_value = _current_capture_register_value + _additional_capture_period;
				_delta_capture_value = _current_capture_value - _last_capture_value;
				if (_delta_capture_value < 0)
				{
					_delta_capture_value += _timer.CounterPeriod();
				}

				_additional_capture_period = 0;

				if (!_adjust_started)
				{
					// 第一次进来，不进行调整工作
					_adjust_started = true;
					return;
				}
			}
			catch (...)
			{
			}
		}

		int64_t CurrentCaptureValue() const
		{
			return _current_capture_value;
		}

		///
		/// @brief 捕获值的增量，代表了被测量信号的周期。
		///
		/// @return
		///
		int64_t DeltaCaptureValue() const
		{
			return _delta_capture_value;
		}
	};

} // namespace base
