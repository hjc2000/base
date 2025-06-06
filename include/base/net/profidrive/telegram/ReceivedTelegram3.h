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
