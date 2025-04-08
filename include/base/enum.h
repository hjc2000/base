#pragma once

namespace base
{
	namespace Enum
	{
		///
		/// @brief 运行状态。
		///
		///
		enum class RunningState
		{
			///
			/// @brief 停止。
			///
			Stop,

			///
			/// @brief 运行。
			///
			Run,
		};

		///
		/// @brief 有效状态。
		///
		///
		enum class ValidState
		{
			Invalid,
			Valid,
		};

		///
		/// @brief 错误状态。
		///
		///
		enum class FaultState
		{
			///
			/// @brief 无错误。
			///
			///
			HasNoFault,

			///
			/// @brief 有错误。
			///
			///
			HasFault,
		};

		///
		/// @brief 警告状态。
		///
		///
		enum class WarningState
		{
			///
			/// @brief 无警告。
			///
			///
			HasNoWarning,

			///
			/// @brief 有警告。
			///
			///
			HasWarning,
		};

		///
		/// @brief 开关状态。
		///
		///
		enum class SwitchState
		{
			Off,
			On,
		};

		///
		/// @brief 电机控制模式。
		///
		///
		enum class MotorControlMode
		{
			///
			/// @brief 位置控制模式。
			///
			///
			Position,

			///
			/// @brief 速度控制模式。
			///
			///
			Speed,

			///
			/// @brief 转矩控制模式。
			///
			///
			Torque,
		};

		///
		/// @brief 电机旋转方向。
		///
		///
		enum class MotorRotationDirection
		{
			///
			/// @brief 正向。
			///
			///
			Forward,

			///
			/// @brief 反向。
			///
			///
			Reverse
		};

	} // namespace Enum
} // namespace base
