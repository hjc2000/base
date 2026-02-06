#pragma once
#include <cstdint>

namespace base::digital_circuit
{
	class SetResetLatch
	{
	private:
		bool _output = false;
		int64_t _count = 0;
		int64_t _setting_output_trigger_count = 0;

	public:
		constexpr SetResetLatch() = default;

		///
		/// @brief
		///
		/// @param setting_output_trigger_count 需要连续输入这么多次为 true 的置位信号才能
		/// 让输出置位。
		/// 	@note 输入 <= 1 的数产生的结果都是输入 1 次为 true 的置位信号后立刻置位输出。
		///
		constexpr SetResetLatch(int64_t setting_output_trigger_count)
		{
			_setting_output_trigger_count = setting_output_trigger_count;

			if (_setting_output_trigger_count < 1)
			{
				_setting_output_trigger_count = 1;
			}
		}

		///
		/// @brief 更新置位信号输入。
		///
		/// @param value
		///
		/// @return 返回当前输入产生影响后的输出。
		///
		constexpr bool Input(bool value)
		{
			if (_output)
			{
				// 输出已经置位了，不需要检查是否达到置位的条件了，直接返回。
				return _output;
			}

			if (value)
			{
				_count++;
			}

			if (_count >= _setting_output_trigger_count)
			{
				_output = true;
			}

			return _output;
		}

		///
		/// @brief 复位输出。
		///
		constexpr void Reset()
		{
			_output = false;
			_count = 0;
		}

		///
		/// @brief 获取输出。
		///
		/// @return
		///
		constexpr bool Output() const
		{
			return _output;
		}
	};

} // namespace base::digital_circuit
