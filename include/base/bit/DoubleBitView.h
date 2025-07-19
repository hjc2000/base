#pragma once
#include "base/bit/bit.h"
#include "base/math/FloatNumberValueType.h"
#include <bit>
#include <cstdint>

namespace base
{
	namespace bit
	{
		class DoubleBitView
		{
		private:
			uint64_t _value{};

		public:
			constexpr DoubleBitView() = default;

			constexpr DoubleBitView(double value)
			{
				_value = std::bit_cast<uint64_t>(value);
			}

			constexpr double Value() const
			{
				return std::bit_cast<double>(_value);
			}

			constexpr uint64_t AsUint64() const
			{
				return _value;
			}

			///
			/// @brief 尾数部分的位。
			///
			/// @return
			///
			constexpr uint64_t MantissaBits() const
			{
				return base::bit::ReadBits(_value, 0, 52);
			}

			///
			/// @brief 指数部分的位。
			///
			/// @return
			///
			constexpr uint64_t ExponentBits() const
			{
				return base::bit::ReadBits(_value, 52, 63);
			}

			///
			/// @brief 符号位。
			///
			/// @return
			///
			constexpr bool SignBit() const
			{
				return base::bit::ReadBit(_value, 63);
			}

			///
			/// @brief 浮点值的类型。
			///
			/// @return
			///
			constexpr base::bit::FloatNumberValueType ValueType() const
			{
				if (ExponentBits() == base::bit::ReadBits(UINT64_MAX, 52, 63))
				{
					// 指数位全为 1

					if (MantissaBits() != 0)
					{
						// 尾数位不全为 0,
						return base::bit::FloatNumberValueType::NaN;
					}

					// 尾数位全为 0

					if (!SignBit())
					{
						// 正无穷
						return base::bit::FloatNumberValueType::PositiveInfinite;
					}

					// 负无穷
					return base::bit::FloatNumberValueType::NegativeInfinite;
				}

				// 指数位不全为 1

				if (ExponentBits() == 0)
				{
					// 指数位全为 0
					return base::bit::FloatNumberValueType::Denormalized;
				}

				return base::bit::FloatNumberValueType::Normalized;
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
		};

	} // namespace bit
} // namespace base
