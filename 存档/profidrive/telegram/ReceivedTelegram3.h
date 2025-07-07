#pragma once
#include "base/profidrive/data-type/N4.h"
#include "base/profidrive/data-type/V2.h"
#include <cstdint>

namespace base
{
	namespace profidrive
	{
		class ReceivedTelegram3
		{
		private:
			base::profidrive::V2 _zsw1{};
			base::profidrive::N4 _nist_b{};
			base::profidrive::V2 _zsw2{};
			base::profidrive::V2 _g1_zsw{};
			uint32_t _g1_xist1{};
			uint32_t _g1_xist2{};

		public:
			///
			/// @brief 状态字 1.
			///
			/// @return
			///
			constexpr base::profidrive::V2 ZSW1() const
			{
				return _zsw1;
			}

			constexpr void Set_ZSW1(base::profidrive::V2 const &value)
			{
				_zsw1 = value;
			}

			/* #region ZSW1 的各个位代表的属性 */

			///
			/// @brief 为 true 表示接通准备就绪。
			///
			/// @return
			///
			constexpr bool ZSW1_ReadyForSwitchingOn() const
			{
				return _zsw1.ReadBit(0);
			}

			constexpr void Set_ZSW1_ReadyForSwitchingOn(bool value)
			{
				_zsw1.WriteBit(0, value);
			}

			///
			/// @brief 为 true 表示操作准备就绪。
			///
			/// @return
			///
			constexpr bool ZSW1_ReadyForOperation() const
			{
				return _zsw1.ReadBit(1);
			}

			constexpr void Set_ZSW1_ReadyForOperation(bool value)
			{
				_zsw1.WriteBit(1, value);
			}

			///
			/// @brief 为 true 表示操作使能，驱动器开始跟随设定点。
			///
			/// @return
			///
			constexpr bool ZSW1_OperationEnabled() const
			{
				return _zsw1.ReadBit(2);
			}

			constexpr void Set_ZSW1_OperationEnabled(bool value)
			{
				_zsw1.WriteBit(2, value);
			}

			///
			/// @brief 为 true 表示驱动器存在错误。
			///
			/// @return
			///
			constexpr bool ZSW1_Fault() const
			{
				return _zsw1.ReadBit(3);
			}

			constexpr void Set_ZSW1_Fault(bool value)
			{
				_zsw1.WriteBit(3, value);
			}

			///
			/// @brief 为 true 表示惯性停机无效，为 false 表示惯性停机有效。
			///
			/// @return
			///
			constexpr bool ZSW1_CoastStopOff() const
			{
				return _zsw1.ReadBit(4);
			}

			constexpr void Set_ZSW1_CoastStopOff(bool value)
			{
				_zsw1.WriteBit(4, value);
			}

			///
			/// @brief 为 true 表示惯性停机有效。
			///
			/// @return
			///
			constexpr bool ZSW1_CoastStopOn() const
			{
				return !_zsw1.ReadBit(4);
			}

			constexpr void Set_ZSW1_CoastStopOn(bool value)
			{
				_zsw1.WriteBit(4, !value);
			}

			///
			/// @brief 为 true 表示快速停机无效，为 false 表示快速停机有效。
			///
			/// @return
			///
			constexpr bool ZSW1_QuickStopOff() const
			{
				return _zsw1.ReadBit(5);
			}

			constexpr void Set_ZSW1_QuickStopOff(bool value)
			{
				_zsw1.WriteBit(5, value);
			}

			///
			/// @brief 为 true 表示快速停机有效，为 false 表示快速停机无效。
			///
			/// @return
			///
			constexpr bool ZSW1_QuickStopOn() const
			{
				return !_zsw1.ReadBit(5);
			}

			constexpr void Set_ZSW1_QuickStopOn(bool value)
			{
				_zsw1.WriteBit(5, !value);
			}

			///
			/// @brief 为 true 表示接通被禁止，为 false 表示接通没有被禁止。
			///
			/// @return
			///
			constexpr bool ZSW1_SwitchingOnInhibited() const
			{
				return _zsw1.ReadBit(6);
			}

			constexpr void Set_ZSW1_SwitchingOnInhibited(bool value)
			{
				_zsw1.WriteBit(6, value);
			}

			///
			/// @brief 为 true 表示存在警告，为 false 表示不存在警告。
			///
			/// @return
			///
			constexpr bool ZSW1_Warning() const
			{
				return _zsw1.ReadBit(7);
			}

			constexpr void Set_ZSW1_Warning(bool value)
			{
				_zsw1.WriteBit(7, value);
			}

			///
			/// @brief 为 true 表示速度偏差在容忍范围内，为 false 表示速度偏差超出容忍范围。
			///
			/// @return
			///
			constexpr bool ZSW1_SpeedErrorWithinTolerance() const
			{
				return _zsw1.ReadBit(8);
			}

			constexpr void Set_ZSW1_SpeedErrorWithinTolerance(bool value)
			{
				_zsw1.WriteBit(8, value);
			}

			///
			/// @brief 为 true 表示有控制请求，为 false 表示没有控制请求。
			///
			/// @note 设备准备好接受 PLC 的控制后，就始终置位此标志位。
			/// PLC 不会在设备没有准备好接受控制时发送控制请求。
			///
			/// @note 控制器不应等到 PLC 将 STW1 的 “由 PLC 控制” 标志位置 1 后才将本标志位置 1,
			/// 因为 PLC 会等待设备的本标志位置 1 后才开始控制，如果这么做，会造成死锁。
			///
			/// @return
			///
			constexpr bool ZSW1_HasControlRequest() const
			{
				return _zsw1.ReadBit(9);
			}

			constexpr void Set_ZSW1_HasControlRequest(bool value)
			{
				_zsw1.WriteBit(9, value);
			}

			///
			/// @brief 为 true 表示速度达到或超过比较值，为 false 表示速度未达到比较值。
			///
			/// @return
			///
			constexpr bool ZSW1_SpeedReachesComparison() const
			{
				return _zsw1.ReadBit(10);
			}

			constexpr void Set_ZSW1_SpeedReachesComparison(bool value)
			{
				_zsw1.WriteBit(10, value);
			}

			/* #endregion */

			///
			/// @brief 实际转速。
			///
			/// @return
			///
			constexpr base::profidrive::N4 NIST_B() const
			{
				return _nist_b;
			}

			constexpr void Set_NIST_B(base::profidrive::N4 const &value)
			{
				_nist_b = value;
			}

			///
			/// @brief 状态字 2.
			///
			/// @return
			///
			constexpr base::profidrive::V2 ZSW2() const
			{
				return _zsw2;
			}

			constexpr void Set_ZSW2(base::profidrive::V2 const &value)
			{
				_zsw2 = value;
			}

			/* #region ZSW2 的各个位代表的属性 */

			///
			/// @brief 从站（设备）生命符号。
			///
			/// @return
			///
			constexpr uint16_t ZSW2_DeviceSignOfLife() const
			{
				return _zsw2.ReadBits(12, 16);
			}

			///
			/// @brief 设置从站（设备）生命符号。
			///
			/// @param value
			///
			constexpr void Set_ZSW2_DeviceSignOfLife(uint16_t value)
			{
				_zsw2.WriteBits(12, 16, value);
			}

			///
			/// @brief 递增从站（设备）生命符号。
			///
			///
			constexpr void Increase_ZSW2_DeviceSignOfLife()
			{
				uint16_t value = ZSW2_DeviceSignOfLife();
				value++;
				Set_ZSW2_DeviceSignOfLife(value);
			}

			/* #endregion */

			///
			/// @brief 编码器 1 状态字。
			///
			/// @return
			///
			constexpr base::profidrive::V2 G1_ZSW() const
			{
				return _g1_zsw;
			}

			constexpr void Set_G1_ZSW(base::profidrive::V2 const &value)
			{
				_g1_zsw = value;
			}

			/* #region G1_ZSW 的各个位代表的属性 */

			///
			/// @brief 功能 1 已激活。
			///
			/// @return
			///
			constexpr bool G1_ZSW_Function1Activated() const
			{
				return _g1_zsw.ReadBit(0);
			}

			///
			/// @brief 设置功能 1 是否已激活。
			///
			/// @param value
			///
			constexpr void Set_G1_ZSW_Function1Activated(bool value)
			{
				_g1_zsw.WriteBit(0, value);
			}

			///
			/// @brief 功能 2 已激活。
			///
			/// @return
			///
			bool G1_ZSW_Function2Activated() const
			{
				return _g1_zsw.ReadBit(1);
			}

			///
			/// @brief 设置功能 2 是否已激活。
			///
			/// @param value
			///
			constexpr void Set_G1_ZSW_Function2Activated(bool value)
			{
				_g1_zsw.WriteBit(1, value);
			}

			///
			/// @brief 功能 3 已激活。
			///
			/// @return
			///
			constexpr bool G1_ZSW_Function3Activated() const
			{
				return _g1_zsw.ReadBit(2);
			}

			///
			/// @brief 设置功能 3 是否已激活。
			///
			/// @param value
			///
			constexpr void Set_G1_ZSW_Function3Activated(bool value)
			{
				_g1_zsw.WriteBit(2, value);
			}

			///
			/// @brief 功能 4 已激活。
			///
			/// @return
			///
			constexpr bool G1_ZSW_Function4Activated() const
			{
				return _g1_zsw.ReadBit(3);
			}

			///
			/// @brief 设置功能 4 是否已激活。
			///
			/// @param value
			///
			constexpr void Set_G1_ZSW_Function4Activated(bool value)
			{
				_g1_zsw.WriteBit(3, value);
			}

			///
			/// @brief G1_ZSW 的功能激活状态寄存器。
			///
			/// @note 每个位代表一个功能。
			///
			/// @return
			///
			constexpr uint16_t G1_ZSW_FunctionActivationStatus() const
			{
				return _g1_zsw.ReadBits(0, 4);
			}

			///
			/// @brief 设置 G1_ZSW 的功能激活状态寄存器。
			///
			/// @param value
			///
			constexpr void Set_G1_ZSW_FunctionActivationStatus(uint16_t value)
			{
				_g1_zsw.WriteBits(0, 4, value);
			}

			///
			/// @brief 值 1 可用。
			///
			/// @return
			///
			constexpr bool G1_ZSW_Value1Available() const
			{
				return _g1_zsw.ReadBit(4);
			}

			///
			/// @brief 设置值 1 是否可用。
			///
			/// @param value
			///
			constexpr void Set_G1_ZSW_Value1Available(bool value)
			{
				_g1_zsw.WriteBit(4, value);
			}

			///
			/// @brief 值 2 可用。
			///
			/// @return
			///
			constexpr bool G1_ZSW_Value2Available() const
			{
				return _g1_zsw.ReadBit(5);
			}

			///
			/// @brief 设置值 2 是否可用。
			///
			/// @param value
			///
			constexpr void Set_G1_ZSW_Value2Available(bool value)
			{
				_g1_zsw.WriteBit(5, value);
			}

			///
			/// @brief 值 3 可用。
			///
			/// @return
			///
			constexpr bool G1_ZSW_Value3Available() const
			{
				return _g1_zsw.ReadBit(6);
			}

			///
			/// @brief 设置值 3 是否可用。
			///
			/// @param value
			///
			constexpr void Set_G1_ZSW_Value3Available(bool value)
			{
				_g1_zsw.WriteBit(6, value);
			}

			///
			/// @brief 值 4 可用。
			///
			/// @return
			///
			constexpr bool G1_ZSW_Value4Available() const
			{
				return _g1_zsw.ReadBit(7);
			}

			///
			/// @brief 设置值 4 是否可用。
			///
			/// @param value
			///
			constexpr void Set_G1_ZSW_Value4Available(bool value)
			{
				_g1_zsw.WriteBit(7, value);
			}

			///
			/// @brief 值的可用状态。
			///
			/// @note 每个位代表一个值。
			///
			/// @return
			///
			constexpr uint16_t G1_ZSW_ValueAvailabilityStatus() const
			{
				return _g1_zsw.ReadBits(4, 8);
			}

			///
			/// @brief 设置值的可用状态。
			///
			/// @param value
			///
			constexpr void Set_G1_ZSW_ValueAvailabilityStatus(uint16_t value)
			{
				_g1_zsw.WriteBits(4, 8, value);
			}

			///
			/// @brief 探头 1 翻转。
			///
			/// @return
			///
			constexpr bool G1_ZSW_Probe1Deflected() const
			{
				return _g1_zsw.ReadBit(8);
			}

			///
			/// @brief 设置探头 1 是否被翻转。
			///
			/// @param value
			///
			constexpr void Set_G1_ZSW_Probe1Deflected(bool value)
			{
				_g1_zsw.WriteBit(8, value);
			}

			///
			/// @brief 探头 2 翻转。
			///
			/// @return
			///
			constexpr bool G1_ZSW_Probe2Deflected() const
			{
				return _g1_zsw.ReadBit(9);
			}

			///
			/// @brief 设置探头 2 是否被翻转。
			///
			/// @param value
			///
			constexpr void Set_G1_ZSW_Probe2Deflected(bool value)
			{
				_g1_zsw.WriteBit(9, value);
			}

			///
			/// @brief 错误确认进行中。
			///
			/// @return
			///
			constexpr bool G1_ZSW_ErrorAcknowledgementInProcess() const
			{
				return _g1_zsw.ReadBit(11);
			}

			///
			/// @brief 设置错误确认是否进行中。
			///
			/// @param value
			///
			constexpr void Set_G1_ZSW_ErrorAcknowledgementInProcess(bool value)
			{
				_g1_zsw.WriteBit(11, value);
			}

			constexpr bool G1_ZSW_ZeroPointHasChanged() const
			{
				return _g1_zsw.ReadBit(12);
			}

			constexpr void Set_G1_ZSW_ZeroPointHasChanged(bool value)
			{
				_g1_zsw.WriteBit(12, value);
			}

			constexpr bool G1_ZSW_TransmitAbsolutePosition() const
			{
				return _g1_zsw.ReadBit(13);
			}

			constexpr void Set_G1_ZSW_TransmitAbsolutePosition(bool value)
			{
				_g1_zsw.WriteBit(13, value);
			}

			constexpr bool G1_ZSW_SensorHasBeenParked() const
			{
				return _g1_zsw.ReadBit(14);
			}

			constexpr void Set_G1_ZSW_SensorHasBeenParked(bool value)
			{
				_g1_zsw.WriteBit(14, value);
			}

			constexpr bool G1_ZSW_SensorError() const
			{
				return _g1_zsw.ReadBit(15);
			}

			constexpr void Set_G1_ZSW_SensorError(bool value)
			{
				_g1_zsw.WriteBit(15, value);
			}

			/* #endregion */

			///
			/// @brief 编码器实际位置 1.
			///
			/// @return
			///
			constexpr uint32_t G1_XIST1() const
			{
				return _g1_xist1;
			}

			constexpr void Set_G1_XIST1(uint32_t value)
			{
				_g1_xist1 = value;
			}

			///
			/// @brief 编码器实际位置 2.
			///
			/// @return
			///
			constexpr uint32_t G1_XIST2() const
			{
				return _g1_xist2;
			}

			constexpr void Set_G1_XIST2(uint32_t value)
			{
				_g1_xist2 = value;
			}
		};

	} // namespace profidrive
} // namespace base
