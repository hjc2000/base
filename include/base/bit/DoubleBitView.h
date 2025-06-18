#pragma once

#include "base/bit/bit.h"
#include <cstdint>

namespace base
{
	namespace bit
	{
		class DoubleBitView
		{
		private:
			union Union
			{
				double _double;
				uint64_t _uint64;
			};

			Union _value_union{};

		public:
			constexpr DoubleBitView() = default;

			constexpr DoubleBitView(double value)
			{
				_value_union._double = value;
			}

			constexpr double Value() const
			{
				return _value_union._double;
			}

			///
			/// @brief 尾数部分的位。
			///
			/// @return
			///
			constexpr uint64_t MantissaBits() const
			{
				return base::bit::ReadBits(_value_union._uint64, 0, 52);
			}

			///
			/// @brief 指数部分的位。
			///
			/// @return
			///
			constexpr uint64_t ExponentBits() const
			{
				return base::bit::ReadBits(_value_union._uint64, 52, 63);
			}

			///
			/// @brief 符号位。
			///
			/// @return
			///
			constexpr bool SignBit() const
			{
				return base::bit::ReadBit(_value_union._uint64, 63);
			}

			///
			/// @brief 是正数。
			///
			/// @return
			///
			constexpr bool Positive() const
			{
				// 符号位位 0 则是正数
				return !SignBit();
			}

			///
			/// @brief 是负数。
			///
			/// @return
			///
			constexpr bool Negative() const
			{
				// 符号位位 1 则是负数
				return SignBit();
			}

			///
			/// @brief 是规格化数。
			///
			/// @return
			///
			constexpr bool Normalized() const
			{
				if (ExponentBits() == 0)
				{
					// 指数位全 0.
					return false;
				}

				if (ExponentBits() == base::bit::ReadBits(UINT64_MAX, 52, 63))
				{
					// 指数位全 1.
					return false;
				}

				return true;
			}
		};

	} // namespace bit
} // namespace base
