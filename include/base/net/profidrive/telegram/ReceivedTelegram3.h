#pragma once
#include "base/net/profidrive/data-type/N4.h"
#include "base/net/profidrive/data-type/V2.h"

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
			base::profidrive::N4 _g1_xist1{};
			base::profidrive::N4 _g1_xist2{};

		public:
			///
			/// @brief 状态字 1.
			///
			/// @return
			///
			base::profidrive::V2 ZSW1() const
			{
				return _zsw1;
			}

			void Set_ZSW1(base::profidrive::V2 const &value)
			{
				_zsw1 = value;
			}

			/* #region ZSW1 的各个位代表的属性 */

			///
			/// @brief 为 true 表示接通准备就绪。
			///
			/// @return
			///
			bool ZSW1_ReadyForSwitchingOn() const
			{
				return _zsw1[0];
			}

			void Set_ZSW1_ReadyForSwitchingOn(bool value)
			{
				_zsw1[0] = value;
			}

			///
			/// @brief 为 true 表示操作准备就绪。
			///
			/// @return
			///
			bool ZSW1_ReadyForOperation() const
			{
				return _zsw1[1];
			}

			void Set_ZSW1_ReadyForOperation(bool value)
			{
				_zsw1[1] = value;
			}

			///
			/// @brief 为 true 表示操作使能，驱动器开始跟随设定点。
			///
			/// @return
			///
			bool ZSW1_OperationEnabled() const
			{
				return _zsw1[2];
			}

			void Set_ZSW1_OperationEnabled(bool value)
			{
				_zsw1[2] = value;
			}

			///
			/// @brief 为 true 表示驱动器存在错误。
			///
			/// @return
			///
			bool ZSW1_Fault() const
			{
				return _zsw1[3];
			}

			void Set_ZSW1_Fault(bool value)
			{
				_zsw1[3] = value;
			}

			///
			/// @brief 为 true 表示惯性停机无效，为 false 表示惯性停机有效。
			///
			/// @return
			///
			bool ZSW1_CoastStopOff() const
			{
				return _zsw1[4];
			}

			void Set_ZSW1_CoastStopOff(bool value)
			{
				_zsw1[4] = value;
			}

			///
			/// @brief 为 true 表示惯性停机有效。
			///
			/// @return
			///
			bool ZSW1_CoastStopOn() const
			{
				return !_zsw1[4];
			}

			void Set_ZSW1_CoastStopOn(bool value)
			{
				_zsw1[4] = !value;
			}

			///
			/// @brief 为 true 表示快速停机无效，为 false 表示快速停机有效。
			///
			/// @return
			///
			bool ZSW1_QuickStopOff() const
			{
				return _zsw1[5];
			}

			void Set_ZSW1_QuickStopOff(bool value)
			{
				_zsw1[5] = value;
			}

			///
			/// @brief 为 true 表示快速停机有效，为 false 表示快速停机无效。
			///
			/// @return
			///
			bool ZSW1_QuickStopOn() const
			{
				return !_zsw1[5];
			}

			void Set_ZSW1_QuickStopOn(bool value)
			{
				_zsw1[5] = !value;
			}

			///
			/// @brief 为 true 表示接通被禁止，为 false 表示接通没有被禁止。
			///
			/// @return
			///
			bool ZSW1_SwitchingOnInhibited() const
			{
				return _zsw1[6];
			}

			void Set_ZSW1_SwitchingOnInhibited(bool value)
			{
				_zsw1[6] = value;
			}

			///
			/// @brief 为 true 表示存在警告，为 false 表示不存在警告。
			///
			/// @return
			///
			bool ZSW1_Warning() const
			{
				return _zsw1[7];
			}

			void Set_ZSW1_Warning(bool value)
			{
				_zsw1[7] = value;
			}

			///
			/// @brief 为 true 表示速度偏差在容忍范围内，为 false 表示速度偏差超出容忍范围。
			///
			/// @return
			///
			bool ZSW1_SpeedErrorWithinTolerance() const
			{
				return _zsw1[8];
			}

			void Set_ZSW1_SpeedErrorWithinTolerance(bool value)
			{
				_zsw1[8] = value;
			}

			///
			/// @brief 为 true 表示有控制请求，为 false 表示没有控制请求。
			///
			/// @return
			///
			bool ZSW1_HasControlRequest() const
			{
				return _zsw1[9];
			}

			void Set_ZSW1_HasControlRequest(bool value)
			{
				_zsw1[9] = value;
			}

			///
			/// @brief 为 true 表示速度达到或超过比较值，为 false 表示速度未达到比较值。
			///
			/// @return
			///
			bool ZSW1_SpeedReachesComparison() const
			{
				return _zsw1[10];
			}

			void Set_ZSW1_SpeedReachesComparison(bool value)
			{
				_zsw1[10] = value;
			}

			/* #endregion */

			///
			/// @brief 实际转速。
			///
			/// @return
			///
			base::profidrive::N4 NIST_B() const
			{
				return _nist_b;
			}

			void Set_NIST_B(base::profidrive::N4 const &value)
			{
				_nist_b = value;
			}

			///
			/// @brief 状态字 2.
			///
			/// @return
			///
			base::profidrive::V2 ZSW2() const
			{
				return _zsw2;
			}

			void Set_ZSW2(base::profidrive::V2 const &value)
			{
				_zsw2 = value;
			}

			///
			/// @brief 编码器 1 状态字。
			///
			/// @return
			///
			base::profidrive::V2 G1_ZSW() const
			{
				return _g1_zsw;
			}

			void Set_G1_ZSW(base::profidrive::V2 const &value)
			{
				_g1_zsw = value;
			}

			///
			/// @brief 编码器实际位置 1.
			///
			/// @return
			///
			base::profidrive::N4 G1_XIST1() const
			{
				return _g1_xist1;
			}

			void Set_G1_XIST1(base::profidrive::N4 const &value)
			{
				_g1_xist1 = value;
			}

			///
			/// @brief 编码器实际位置 2.
			///
			/// @return
			///
			base::profidrive::N4 G1_XIST2() const
			{
				return _g1_xist2;
			}

			void Set_G1_XIST2(base::profidrive::N4 const &value)
			{
				_g1_xist2 = value;
			}
		};

	} // namespace profidrive
} // namespace base
