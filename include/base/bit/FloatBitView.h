#pragma once
#include "base/bit/bit.h"
#include "base/bit/FloatValueType.h"
#include <bit>
#include <cstdint>

namespace base
{
	namespace bit
	{
		///
		/// @brief float 的位视图。
		///
		///
		class FloatBitView
		{
		private:
			uint32_t _value{};

		public:
			constexpr FloatBitView() = default;

			constexpr FloatBitView(float value)
			{
				_value = std::bit_cast<uint32_t>(value);
			}

			///
			/// @brief 此视图中的浮点的值。
			///
			/// @return
			///
			constexpr float Value() const
			{
				return std::bit_cast<float>(_value);
			}

			///
			/// @brief 将浮点的位视图视为 uint32_t 的位视图后得到的
			/// uint32_t 类型的值。
			///
			/// @return
			///
			constexpr uint32_t AsUint32() const
			{
				return _value;
			}

			///
			/// @brief 尾数部分的位。
			///
			/// @return
			///
			constexpr uint32_t MantissaBits() const
			{
				return base::bit::ReadBits(_value, 0, 23);
			}

			///
			/// @brief 指数部分的位。
			///
			/// @return
			///
			constexpr uint32_t ExponentBits() const
			{
				return base::bit::ReadBits(_value, 23, 31);
			}

			///
			/// @brief 符号位。
			///
			/// @return
			///
			constexpr bool SignBit() const
			{
				return base::bit::ReadBit(_value, 31);
			}

			///
			/// @brief 浮点值的类型。
			///
			/// @return
			///
			constexpr base::bit::FloatValueType ValueType() const
			{
				if (ExponentBits() == base::bit::ReadBits(UINT32_MAX, 23, 31))
				{
					// 指数位全为 1

					if (MantissaBits() != 0)
					{
						// 尾数位不全为 0,
						return base::bit::FloatValueType::NaN;
					}

					// 尾数位全为 0

					if (!SignBit())
					{
						// 正无穷
						return base::bit::FloatValueType::PositiveInfinite;
					}

					// 负无穷
					return base::bit::FloatValueType::NegativeInfinite;
				}

				// 指数位不全为 1

				if (ExponentBits() == 0)
				{
					// 指数位全为 0
					return base::bit::FloatValueType::Denormalized;
				}

				return base::bit::FloatValueType::Normalized;
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
