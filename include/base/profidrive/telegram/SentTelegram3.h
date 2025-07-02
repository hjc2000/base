#pragma once
#include "base/profidrive/data-type/N4.h"
#include "base/profidrive/data-type/V2.h"
#include <cstdint>

namespace base
{
	namespace profidrive
	{
		enum class EncoderCommand
		{
			///
			/// @brief 不执行任何操作。
			///
			///
			None,

			///
			/// @brief 激活已选择的功能。
			///
			///
			ActivateSelectedFunction,

			///
			/// @brief 读取值。
			///
			///
			ReadValue,

			///
			/// @brief 中断正在执行的功能。
			///
			///
			InterruptFunction,
		};

		enum class EncoderMeasureFunction
		{
			///
			/// @brief 搜索参考点挡块。
			///
			///
			SearchForReferencePointBlock,

			///
			/// @brief 飞速测量。
			///
			///
			RapidMeasurement,
		};

		///
		/// @brief 设置编码器的零点所使用的模式。
		///
		///
		enum class SettingEncoderZeroPointMode
		{
			///
			/// @brief 直接设定零点的位置。
			///
			///
			Set,

			///
			/// @brief 将零点移动一段距离。
			///
			///
			Move,
		};

		///
		/// @brief PLC 发送的报文 3.
		///
		///
		class SentTelegram3
		{
		private:
			base::profidrive::V2 _stw1{};
			base::profidrive::N4 _nsoll_b{};
			base::profidrive::V2 _stw2{};
			base::profidrive::V2 _g1_stw{};

		public:
			///
			/// @brief 控制字 1.
			///
			/// @return
			///
			constexpr base::profidrive::V2 STW1() const
			{
				return _stw1;
			}

			constexpr void Set_STW1(base::profidrive::V2 const &value)
			{
				_stw1 = value;
			}

			/* #region STW1 的各个位代表的属性 */

			///
			/// @brief STW1 指示当前应该上电。
			///
			/// @return
			///
			constexpr bool STW1_PowerOn() const
			{
				return _stw1.ReadBit(0);
			}

			constexpr void Set_STW1_PowerOn(bool value)
			{
				_stw1.WriteBit(0, value);
			}

			///
			/// @brief STW1 的 “不惯性停机” 控制位。为 1 时表示不惯性停机，
			/// 为 0 时表示惯性停机。
			///
			/// @return
			///
			constexpr bool STW1_NoCoastStop() const
			{
				return _stw1.ReadBit(1);
			}

			constexpr void Set_STW1_NoCoastStop(bool value)
			{
				_stw1.WriteBit(1, value);
			}

			///
			/// @brief STW1 指示当前应该惯性停机。
			///
			/// @note 转发 STW1_NoCoastStop, 使得逻辑不那么绕。
			///
			/// @return
			///
			constexpr bool STW1_CoastStop() const
			{
				return !STW1_NoCoastStop();
			}

			constexpr void Set_STW1_CoastStop(bool value)
			{
				Set_STW1_NoCoastStop(!value);
			}

			///
			/// @brief STW1 的 “不快速停机” 控制位。为 1 时表示不快速停机，
			/// 为 0 时表示快速停机。
			///
			/// @return
			///
			constexpr bool STW1_NoQuickStop() const
			{
				return _stw1.ReadBit(2);
			}

			constexpr void Set_STW1_NoQuickStop(bool value)
			{
				_stw1.WriteBit(2, value);
			}

			///
			/// @brief STW1 指示当前应该快速停机。
			///
			/// @note 转发 STW1_NoQuickStop, 使得逻辑不那么绕。
			///
			/// @return
			///
			constexpr bool STW1_QuickStop() const
			{
				return !STW1_NoQuickStop();
			}

			constexpr void Set_STW1_QuickStop(bool value)
			{
				Set_STW1_NoQuickStop(!value);
			}

			///
			/// @brief STW1 的 “允许操作” 控制位。为 1 时表示允许操作，
			/// 为 0 时表示禁止操作。
			///
			/// @return
			///
			constexpr bool STW1_EnableOperation() const
			{
				return _stw1.ReadBit(3);
			}

			constexpr void Set_STW1_EnableOperation(bool value)
			{
				_stw1.WriteBit(3, value);
			}

			///
			/// @brief STW1 的 “使能斜坡函数发生器” 控制位。为 1 时表示使能斜坡函数发生器，
			/// 为 0 时表示禁止斜坡函数发生器。
			///
			/// @return
			///
			constexpr bool STW1_EnableRampFunctionGenerator() const
			{
				return _stw1.ReadBit(4);
			}

			constexpr void Set_STW1_EnableRampFunctionGenerator(bool value)
			{
				_stw1.WriteBit(4, value);
			}

			///
			/// @brief STW1 的 “解冻斜坡函数发生器” 控制位。为 1 时表示解冻斜坡函数发生器，
			/// 为 0 时表示冻结斜坡函数发生器。
			///
			/// @return
			///
			constexpr bool STW1_UnfreezeRampFunctionGenerator() const
			{
				return _stw1.ReadBit(5);
			}

			constexpr void Set_STW1_UnfreezeRampFunctionGenerator(bool value)
			{
				_stw1.WriteBit(5, value);
			}

			///
			/// @brief STW1 指示当前应该冻结斜坡函数发生器。
			///
			/// @note 转发 STW1_UnfreezeRampFunctionGenerator, 使得逻辑不那么绕。
			///
			/// @return
			///
			constexpr bool STW1_FreezeRampFunctionGenerator() const
			{
				return !STW1_UnfreezeRampFunctionGenerator();
			}

			constexpr void Set_STW1_FreezeRampFunctionGenerator(bool value)
			{
				Set_STW1_UnfreezeRampFunctionGenerator(!value);
			}

			///
			/// @brief STW1 的 “使能斜坡函数发生器跟随设定点” 控制位。
			/// 为 1 时表示使能斜坡函数发生器跟随设定点，为 0 时表示禁止斜坡函数发生器跟随设定点。
			///
			/// @return
			///
			constexpr bool STW1_EnableRampFunctionGeneratorSetpoint() const
			{
				return _stw1.ReadBit(6);
			}

			constexpr void Set_STW1_EnableRampFunctionGeneratorSetpoint(bool value)
			{
				_stw1.WriteBit(6, value);
			}

			///
			/// @brief STW1 的 “故障确认” 控制位。发生一次上升沿表示进行一次故障确认。
			///
			/// @return
			///
			constexpr bool STW1_FaultAcknowledge() const
			{
				return _stw1.ReadBit(7);
			}

			constexpr void Set_STW1_FaultAcknowledge(bool value)
			{
				_stw1.WriteBit(7, value);
			}

			constexpr bool STW1_SetRampFunctionGeneratorSetpointToJoggingSetpoint1() const
			{
				return _stw1.ReadBit(8);
			}

			constexpr void Set_STW1_SetRampFunctionGeneratorSetpointToJoggingSetpoint1(bool value)
			{
				_stw1.WriteBit(8, value);
			}

			constexpr bool STW1_SetRampFunctionGeneratorSetpointToJoggingSetpoint2() const
			{
				return _stw1.ReadBit(9);
			}

			constexpr void Set_STW1_SetRampFunctionGeneratorSetpointToJoggingSetpoint2(bool value)
			{
				_stw1.WriteBit(9, value);
			}

			///
			/// @brief 当前是被 PLC 控制。
			///
			/// @return
			///
			constexpr bool STW1_IsControlledByPlc() const
			{
				return _stw1.ReadBit(10);
			}

			constexpr void Set_STW1_IsControlledByPlc(bool value)
			{
				_stw1.WriteBit(10, value);
			}

			/* #endregion */

			///
			/// @brief 给定转速。
			///
			/// @note 是个分数，表示是额定转速的多少倍。
			///
			/// @return
			///
			constexpr base::profidrive::N4 NSOLL_B() const
			{
				return _nsoll_b;
			}

			constexpr void Set_NSOLL_B(base::profidrive::N4 const &value)
			{
				_nsoll_b = value;
			}

			///
			/// @brief 控制字 2.
			///
			/// @return
			///
			constexpr base::profidrive::V2 STW2() const
			{
				return _stw2;
			}

			constexpr void Set_STW2(base::profidrive::V2 const &value)
			{
				_stw2 = value;
			}

			/* #region STW2 的各个位代表的属性 */

			///
			/// @brief 主站（PLC）生命符号。
			///
			/// @return
			///
			constexpr uint16_t STW2_ControllerSignOfLife() const
			{
				return _stw2.ReadBits(12, 16);
			}

			///
			/// @brief 设置主站（PLC）生命符号。
			///
			/// @param value
			///
			constexpr void Set_STW2_ControllerSignOfLife(uint16_t value)
			{
				_stw2.WriteBits(12, 16, value);
			}

			/* #endregion */

			///
			/// @brief 编码器 1 控制字。
			///
			/// @return
			///
			constexpr base::profidrive::V2 G1_STW() const
			{
				return _g1_stw;
			}

			constexpr void Set_G1_STW(base::profidrive::V2 const &value)
			{
				_g1_stw = value;
			}

			/* #region G1_STW 的各个位代表的属性 */

			///
			/// @brief 为 true 表示选中编码器 1 的功能 1.
			///
			/// @return
			///
			constexpr bool G1_STW_Function1Selected() const
			{
				return _g1_stw.ReadBit(0);
			}

			///
			/// @brief 设置是否选中编码器 1 的功能 1.
			///
			/// @param value
			///
			constexpr void Set_G1_STW_Function1Selected(bool value)
			{
				_g1_stw.WriteBit(0, value);
			}

			///
			/// @brief 为 true 表示选中编码器 1 的功能 2.
			///
			/// @return
			///
			constexpr bool G1_STW_Function2Selected() const
			{
				return _g1_stw.ReadBit(1);
			}

			///
			/// @brief 设置是否选中编码器 1 的功能 2.
			///
			/// @param value
			///
			constexpr void Set_G1_STW_Function2Selected(bool value)
			{
				_g1_stw.WriteBit(1, value);
			}

			///
			/// @brief 为 true 表示选中编码器 1 的功能 3.
			///
			/// @return
			///
			constexpr bool G1_STW_Function3Selected() const
			{
				return _g1_stw.ReadBit(2);
			}

			///
			/// @brief 设置是否选中编码器 1 的功能 3.
			///
			/// @param value
			///
			constexpr void Set_G1_STW_Function3Selected(bool value)
			{
				_g1_stw.WriteBit(2, value);
			}

			///
			/// @brief 为 true 表示选中编码器 1 的功能 4.
			///
			/// @return
			///
			constexpr bool G1_STW_Function4Selected() const
			{
				return _g1_stw.ReadBit(3);
			}

			///
			/// @brief 设置是否选中编码器 1 的功能 4.
			///
			/// @param value
			///
			constexpr void Set_G1_STW_Function4Selected(bool value)
			{
				_g1_stw.WriteBit(3, value);
			}

			///
			/// @brief 功能的激活状态。
			///
			/// @note 用来激活功能。每个位对应一个功能。
			///
			/// @return
			///
			constexpr uint16_t G1_STW_FunctionActivationStatus() const
			{
				return _g1_stw.ReadBits(0, 4);
			}

			///
			/// @brief 设置功能的激活状态。
			///
			/// @param value
			///
			constexpr void Set_G1_STW_FunctionActivationStatus(uint16_t value)
			{
				_g1_stw.WriteBits(0, 4, value);
			}

			///
			/// @brief 功能 1 到 4 只要有一个功能被激活，本方法就返回 true.
			///
			/// @return
			///
			constexpr bool G1_STW_AnyFunctionActivated() const
			{
				return G1_STW_FunctionActivationStatus() != 0;
			}

			///
			/// @brief 对编码器 1 的命令。
			///
			/// @note 优先级 3.
			///
			/// @return
			///
			constexpr base::profidrive::EncoderCommand G1_STW_Command() const
			{
				uint16_t value = _g1_stw.ReadBits(4, 7);
				return static_cast<base::profidrive::EncoderCommand>(value);
			}

			///
			/// @brief 设置对编码器 1 的命令。
			///
			/// @param value
			///
			constexpr void Set_G1_STW_Command(base::profidrive::EncoderCommand value)
			{
				_g1_stw.WriteBits(4, 7, static_cast<uint16_t>(value));
			}

			constexpr bool G1_STW_CommandIsValid() const
			{
				if (static_cast<int32_t>(G1_STW_Command()) < 0)
				{
					return false;
				}

				if (static_cast<int32_t>(G1_STW_Command()) > static_cast<int32_t>(base::profidrive::EncoderCommand::InterruptFunction))
				{
					// InterruptFunction 是最后一个枚举值，大于它是非法的。
					return false;
				}

				return true;
			}

			///
			/// @brief 选择编码器测量功能。
			///
			/// @return
			///
			constexpr base::profidrive::EncoderMeasureFunction G1_STW_MeasureFunction() const
			{
				bool value = _g1_stw.ReadBit(7);
				return static_cast<base::profidrive::EncoderMeasureFunction>(value);
			}

			///
			/// @brief 设置要选择的编码器测量功能。
			///
			/// @param value
			///
			constexpr void Set_G1_STW_MeasureFunction(base::profidrive::EncoderMeasureFunction value)
			{
				_g1_stw.WriteBit(7, static_cast<bool>(value));
			}

			///
			/// @brief 设置编码器零点位置时所使用的模式。
			///
			/// @return
			///
			constexpr base::profidrive::SettingEncoderZeroPointMode G1_STW_SettingZeroPointMode() const
			{
				bool value = _g1_stw.ReadBit(11);
				return static_cast<base::profidrive::SettingEncoderZeroPointMode>(value);
			}

			constexpr void Set_G1_STW_SettingZeroPointMode(base::profidrive::SettingEncoderZeroPointMode value)
			{
				_g1_stw.WriteBit(11, static_cast<bool>(value));
			}

			///
			/// @brief 为 true 表示请求改变零点位置。
			///
			/// @note 改变零点位置有 “直接设置” 和 “移动” 这两种方式。
			/// 详见 G1_STW_SettingZeroPointMode 属性。
			///
			/// @note 优先级 4.
			///
			/// @return
			///
			constexpr bool G1_STW_ChangeZeroPoint() const
			{
				return _g1_stw.ReadBit(12);
			}

			constexpr void Set_G1_STW_ChangeZeroPoint(bool value)
			{
				_g1_stw.WriteBit(12, value);
			}

			///
			/// @brief 为 true 表示请求使用 G1_XIST2 来传输绝对位置。
			///
			/// @note 优先级 5.
			///
			/// @return
			///
			constexpr bool G1_STW_RequestAbsolutePosition() const
			{
				return _g1_stw.ReadBit(13);
			}

			constexpr void Set_G1_STW_RequestAbsolutePosition(bool value)
			{
				_g1_stw.WriteBit(13, value);
			}

			///
			/// @brief 为 true 表示请求让编码器停车。
			///
			/// @note 停车后，编码器可以物理上与驱动器断开连接。
			///
			/// @note 优先级 1. 具有最高优先级。
			///
			/// @return
			///
			constexpr bool G1_STW_Park() const
			{
				return _g1_stw.ReadBit(14);
			}

			constexpr void Set_G1_STW_Park(bool value)
			{
				_g1_stw.WriteBit(14, value);
			}

			///
			/// @brief 请求进行编码器的错误确认。
			///
			/// @note 优先级 2.
			///
			/// @return
			///
			constexpr bool G1_STW_AcknowledgeError() const
			{
				return _g1_stw.ReadBit(15);
			}

			constexpr void Set_G1_STW_AcknowledgeError(bool value)
			{
				_g1_stw.WriteBit(15, value);
			}

			/* #endregion */
		};

	} // namespace profidrive
} // namespace base
