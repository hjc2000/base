#pragma once
#include <cstdint>

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
			/// @note 博图中的 MC_Power 程序块的输入信号 Enable 输入 TRUE 时开始执行使能
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

			///
			/// @brief 状态机错误。
			///
			StateMachineError
		};

	} // namespace profidrive
} // namespace base

inline bool operator<(base::profidrive::AxisState lhs, base::profidrive::AxisState rhs)
{
	return static_cast<uint32_t>(lhs) < static_cast<uint32_t>(rhs);
}

inline bool operator>(base::profidrive::AxisState lhs, base::profidrive::AxisState rhs)
{
	return static_cast<uint32_t>(lhs) > static_cast<uint32_t>(rhs);
}

inline bool operator<=(base::profidrive::AxisState lhs, base::profidrive::AxisState rhs)
{
	return static_cast<uint32_t>(lhs) <= static_cast<uint32_t>(rhs);
}

inline bool operator>=(base::profidrive::AxisState lhs, base::profidrive::AxisState rhs)
{
	return static_cast<uint32_t>(lhs) >= static_cast<uint32_t>(rhs);
}
