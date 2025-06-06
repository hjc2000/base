#pragma once
#include "base/net/profidrive/data-type/N4.h"
#include "base/net/profidrive/data-type/V2.h"

namespace base
{
	namespace profidrive
	{
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
		};

	} // namespace profidrive
} // namespace base
