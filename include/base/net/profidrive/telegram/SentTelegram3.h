#pragma once
#include "base/bit/bit.h"
#include "base/net/profidrive/data-type/N4.h"
#include "base/net/profidrive/data-type/V2.h"
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
			base::profidrive::V2 STW1() const
			{
				return _stw1;
			}

			void Set_STW1(base::profidrive::V2 const &stw1)
			{
				_stw1 = stw1;
			}

			/* #region STW1 的各个位代表的属性 */

			///
			/// @brief STW1 的 “不下电” 控制位。为 1 时表示不下电，
			/// 为 0 时表示下电。
			///
			/// @return
			///
			bool STW1_NoPowerDown() const
			{
				return _stw1[0];
			}

			void Set_STW1_NoPowerDown(bool value)
			{
				_stw1[0] = value;
			}

			///
			/// @brief STW1 指示当前应该上电。
			///
			/// @note 转发 STW1_NoPowerDown, 使得逻辑不那么绕。
			///
			/// @return
			///
			bool STW1_PowerOn() const
			{
				return STW1_NoPowerDown();
			}

			void Set_STW1_PowerOn(bool value)
			{
				Set_STW1_NoPowerDown(value);
			}

			///
			/// @brief STW1 的 “不惯性停机” 控制位。为 1 时表示不惯性停机，
			/// 为 0 时表示惯性停机。
			///
			/// @return
			///
			bool STW1_NoCoastStop() const
			{
				return _stw1[1];
			}

			void Set_STW1_NoCoastStop(bool value)
			{
				_stw1[1] = value;
			}

			///
			/// @brief STW1 指示当前应该惯性停机。
			///
			/// @note 转发 STW1_NoCoastStop, 使得逻辑不那么绕。
			///
			/// @return
			///
			bool STW1_CoastStop() const
			{
				return !STW1_NoCoastStop();
			}

			void Set_STW1_CoastStop(bool value)
			{
				Set_STW1_NoCoastStop(!value);
			}

			///
			/// @brief STW1 的 “不快速停机” 控制位。为 1 时表示不快速停机，
			/// 为 0 时表示快速停机。
			///
			/// @return
			///
			bool STW1_NoQuickStop() const
			{
				return _stw1[2];
			}

			void Set_STW1_NoQuickStop(bool value)
			{
				_stw1[2] = value;
			}

			///
			/// @brief STW1 指示当前应该快速停机。
			///
			/// @note 转发 STW1_NoQuickStop, 使得逻辑不那么绕。
			///
			/// @return
			///
			bool STW1_QuickStop() const
			{
				return !STW1_NoQuickStop();
			}

			void Set_STW1_QuickStop(bool value)
			{
				Set_STW1_NoQuickStop(!value);
			}

			///
			/// @brief STW1 的 “允许操作” 控制位。为 1 时表示允许操作，
			/// 为 0 时表示禁止操作。
			///
			/// @return
			///
			bool STW1_EnableOperation() const
			{
				return _stw1[3];
			}

			void Set_STW1_EnableOperation(bool value)
			{
				_stw1[3] = value;
			}

			///
			/// @brief STW1 的 “使能斜坡函数发生器” 控制位。为 1 时表示使能斜坡函数发生器，
			/// 为 0 时表示禁止斜坡函数发生器。
			///
			/// @return
			///
			bool STW1_EnableRampFunctionGenerator() const
			{
				return _stw1[4];
			}

			void Set_STW1_EnableRampFunctionGenerator(bool value)
			{
				_stw1[4] = value;
			}

			///
			/// @brief STW1 的 “解冻斜坡函数发生器” 控制位。为 1 时表示解冻斜坡函数发生器，
			/// 为 0 时表示冻结斜坡函数发生器。
			///
			/// @return
			///
			bool STW1_UnfreezeRampFunctionGenerator() const
			{
				return _stw1[5];
			}

			void Set_STW1_UnfreezeRampFunctionGenerator(bool value)
			{
				_stw1[5] = value;
			}

			///
			/// @brief STW1 指示当前应该冻结斜坡函数发生器。
			///
			/// @note 转发 STW1_UnfreezeRampFunctionGenerator, 使得逻辑不那么绕。
			///
			/// @return
			///
			bool STW1_FreezeRampFunctionGenerator() const
			{
				return !STW1_UnfreezeRampFunctionGenerator();
			}

			void Set_STW1_FreezeRampFunctionGenerator(bool value)
			{
				Set_STW1_UnfreezeRampFunctionGenerator(!value);
			}

			///
			/// @brief STW1 的 “使能斜坡函数发生器跟随设定点” 控制位。
			/// 为 1 时表示使能斜坡函数发生器跟随设定点，为 0 时表示禁止斜坡函数发生器跟随设定点。
			///
			/// @return
			///
			bool STW1_EnableRampFunctionGeneratorSetpoint() const
			{
				return _stw1[6];
			}

			void Set_STW1_EnableRampFunctionGeneratorSetpoint(bool value)
			{
				_stw1[6] = value;
			}

			///
			/// @brief STW1 的 “故障确认” 控制位。发生一次上升沿表示进行一次故障确认。
			///
			/// @return
			///
			bool STW1_FaultAcknowledge() const
			{
				return _stw1[7];
			}

			void Set_STW1_FaultAcknowledge(bool value)
			{
				_stw1[7] = value;
			}

			bool STW1_SetRampFunctionGeneratorSetpointToJoggingSetpoint1() const
			{
				return _stw1[8];
			}

			void Set_STW1_SetRampFunctionGeneratorSetpointToJoggingSetpoint1(bool value)
			{
				_stw1[8] = value;
			}

			bool STW1_SetRampFunctionGeneratorSetpointToJoggingSetpoint2() const
			{
				return _stw1[9];
			}

			void Set_STW1_SetRampFunctionGeneratorSetpointToJoggingSetpoint2(bool value)
			{
				_stw1[9] = value;
			}

			///
			/// @brief 当前是被 PLC 控制。
			///
			/// @return
			///
			bool STW1_IsControlledByPlc() const
			{
				return _stw1[10];
			}

			void Set_STW1_IsControlledByPlc(bool value)
			{
				_stw1[10] = value;
			}

			/* #endregion */

			///
			/// @brief 给定转速。
			///
			/// @note 是个分数，表示是额定转速的多少倍。
			///
			/// @return
			///
			base::profidrive::N4 NSOLL_B() const
			{
				return _nsoll_b;
			}

			void Set_NSOLL_B(base::profidrive::N4 const &nsoll_b)
			{
				_nsoll_b = nsoll_b;
			}

			///
			/// @brief 控制字 2.
			///
			/// @return
			///
			base::profidrive::V2 STW2() const
			{
				return _stw2;
			}

			void Set_STW2(base::profidrive::V2 const &stw2)
			{
				_stw2 = stw2;
			}

			///
			/// @brief 编码器 1 控制字。
			///
			/// @return
			///
			base::profidrive::V2 G1_STW() const
			{
				return _g1_stw;
			}

			void Set_G1_STW(base::profidrive::V2 const &g1_stw)
			{
				_g1_stw = g1_stw;
			}

			///
			/// @brief 为 true 表示激活编码器 1 的功能 1.
			///
			/// @return
			///
			bool G1_STW_Function1() const
			{
				return _g1_stw[0];
			}

			void Set_G1_STW_Function1(bool value)
			{
				_g1_stw[0] = value;
			}

			///
			/// @brief 为 true 表示激活编码器 1 的功能 2.
			///
			/// @return
			///
			bool G1_STW_Function2() const
			{
				return _g1_stw[1];
			}

			void Set_G1_STW_Function2(bool value)
			{
				_g1_stw[1] = value;
			}

			///
			/// @brief 为 true 表示激活编码器 1 的功能 3.
			///
			/// @return
			///
			bool G1_STW_Function3() const
			{
				return _g1_stw[2];
			}

			void Set_G1_STW_Function3(bool value)
			{
				_g1_stw[2] = value;
			}

			///
			/// @brief 为 true 表示激活编码器 1 的功能 4.
			///
			/// @return
			///
			bool G1_STW_Function4() const
			{
				return _g1_stw[3];
			}

			void Set_G1_STW_Function4(bool value)
			{
				_g1_stw[3] = value;
			}

			///
			/// @brief 编码器控制命令。
			///
			/// @return
			///
			base::profidrive::EncoderCommand G1_STW_Command() const
			{
				uint16_t value = static_cast<uint16_t>(_g1_stw);
				value = base::bit::ReadBits(value, 4, 7);
				return static_cast<base::profidrive::EncoderCommand>(value);
			}

			void Set_G1_STW_Command(base::profidrive::EncoderCommand command)
			{
				uint16_t value = static_cast<uint16_t>(_g1_stw);
				base::bit::WriteBits(value, 4, 7, static_cast<uint16_t>(command));
				_g1_stw = base::profidrive::V2{value};
			}
		};

	} // namespace profidrive
} // namespace base
