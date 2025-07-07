#pragma once

namespace base
{
	namespace profidrive
	{
		///
		/// @brief 轴状态机的状态。
		///
		///
		enum class AxisState
		{
			///
			/// @brief 禁止接通状态。
			///
			SwitchingOnInhibited,

			///
			/// @brief 接通准备就绪。
			///
			ReadyForSwitchingOn,

			///
			/// @brief 轴已接通。
			///
			SwitchedOn,

			///
			/// @brief 轴已使能，正在操作。
			///
			/// @note 博图中的 MC_Power 程序块的 Enable 引脚输入 true 时开始执行使能
			/// 轴的过程。
			///
			Operation,

			///
			/// @brief 斜坡停机。
			///
			RampStop,

			///
			/// @brief 快速停机。
			///
			QuickStop,
		};

	} // namespace profidrive
} // namespace base

namespace base
{
	///
	/// @brief 将轴状态枚举转换为字符串。
	///
	/// @param state
	/// @return
	///
	constexpr char const *to_string(base::profidrive::AxisState state) noexcept
	{
		switch (state)
		{
		case base::profidrive::AxisState::SwitchingOnInhibited:
			{
				return "SwitchingOnInhibited";
			}
		case base::profidrive::AxisState::ReadyForSwitchingOn:
			{
				return "ReadyForSwitchingOn";
			}
		case base::profidrive::AxisState::SwitchedOn:
			{
				return "SwitchedOn";
			}
		case base::profidrive::AxisState::Operation:
			{
				return "Operation";
			}
		case base::profidrive::AxisState::RampStop:
			{
				return "RampStop";
			}
		case base::profidrive::AxisState::QuickStop:
			{
				return "QuickStop";
			}
		default:
			{
				return "未定义状态";
			}
		}
	}

} // namespace base
