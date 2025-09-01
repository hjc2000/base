#pragma once
#include "base/bit/bit.h"
#include "base/container/ReadOnlyArraySpan.h"
#include "base/string/define.h"
#include "EncoderType.h"
#include <algorithm>
#include <array>
#include <cstdint>
#include <stdexcept>

namespace base
{
	namespace profidrive
	{
		///
		/// @brief 传感器格式。
		///
		///
		class EncoderFormat
		{
		private:
			std::array<uint32_t, 31> _array{};

		public:
			/* #region 构造函数 */

			constexpr EncoderFormat() = default;

			constexpr EncoderFormat(std::array<uint32_t, 31> const &array)
				: _array{array}
			{
			}

			EncoderFormat(base::ReadOnlyArraySpan<uint32_t> const &span)
			{
				if (span.Count() < 31)
				{
					throw std::invalid_argument{CODE_POS_STR + "buffer 的长度不足 31."};
				}

				std::copy(span.Buffer(), span.Buffer() + 31, _array.data());
			}

			/* #endregion */

			constexpr std::array<uint32_t, 31> const &Array() const
			{
				return _array;
			}

			/* #region 首部 */

			///
			/// @brief 次版本号。
			///
			/// @note 次版本号的变更说明做出了兼容性的更改，可能是功能的添加，旧功能的接口
			/// 保持不变。
			///
			/// @return
			///
			constexpr uint32_t MinorVersion() const
			{
				return base::bit::ReadBits(_array[0], 0, 4);
			}

			///
			/// @brief 设置次版本号。
			///
			/// @param value
			///
			constexpr void SetMinorVersion(uint32_t value)
			{
				base::bit::WriteBits(_array[0], 0, 4, value);
			}

			///
			/// @brief 主版本号。
			///
			/// @note 主版本号的变更说明做出了不兼容的更改。
			///
			/// @return
			///
			constexpr uint32_t MajorVersion() const
			{
				return base::bit::ReadBits(_array[0], 4, 8);
			}

			///
			/// @brief 设置主版本号。
			///
			/// @param value
			///
			constexpr void SetMajorVersion(uint32_t value)
			{
				base::bit::WriteBits(_array[0], 4, 8, value);
			}

			///
			/// @brief 本对象所要描述的编码器的个数。
			///
			/// @note 建议将此数量限制在实际拥有的编码器的数量以内，以减小通信负担。
			///
			/// @return
			///
			constexpr uint32_t EncoderCount() const
			{
				return base::bit::ReadBits(_array[0], 8, 12);
			}

			constexpr void SetEncoderCount(uint32_t value)
			{
				base::bit::WriteBits(_array[0], 8, 12, value);
			}

			///
			/// @brief 每个编码器用多少个 uint32_t 去描述它。
			///
			/// @note 标准文档把本参数的每个 uint32_t 对应为一个子索引。例如首部就是子索引 0,
			/// 下一个 uint32_t 就是子索引 1, 以此类推。
			///
			/// @return
			///
			constexpr uint32_t SubindexCount() const
			{
				return base::bit::ReadBits(_array[0], 12, 16);
			}

			///
			/// @brief 设置每个编码器用多少个 uint32_t 去描述它。
			///
			/// @note 目前标准文档里介绍的只有 5 个子索引，所以建议设置为 5, 其他子索引的用途未定义。
			///
			/// @param value
			///
			constexpr void SetSubindexCount(uint32_t value)
			{
				if (value < 5 || value > 10)
				{
					throw std::invalid_argument{CODE_POS_STR + "范围必须在 [5, 10]."};
				}

				base::bit::WriteBits(_array[0], 12, 16, value);
			}

			/* #endregion */

			/* #region 编码器 1 描述信息 */

			///
			/// @brief 传感器类型。
			///
			/// @return
			///
			constexpr base::profidrive::EncoderType G1_EncoderType() const
			{
				bool bit_value = base::bit::ReadBit(_array[1], 0);
				return static_cast<base::profidrive::EncoderType>(bit_value);
			}

			///
			/// @brief 设置传感器类型。
			///
			/// @param value
			///
			constexpr void G1_SetEncoderType(base::profidrive::EncoderType value)
			{
				bool bit_value = static_cast<bool>(value);
				base::bit::WriteBit(_array[1], 0, bit_value);
			}

			///
			/// @brief 光电码盘是绝对式的，能够获取一圈内的绝对位置。
			///
			/// @return
			///
			constexpr bool G1_IsAbsoluteEncoder() const
			{
				return base::bit::ReadBit(_array[1], 1);
			}

			///
			/// @brief 设置光电码盘是否是绝对是的。
			///
			/// @param value
			///
			constexpr void G1_SetIsAbsoluteEncoder(bool value)
			{
				base::bit::WriteBit(_array[1], 1, value);
			}

			///
			/// @brief 有 64 位的绝对位置信息。
			///
			/// @return
			///
			constexpr bool G1_Has64BitAbsolutePosition() const
			{
				return base::bit::ReadBit(_array[1], 2);
			}

			///
			/// @brief 设置是否有 64 位的绝对位置信息。
			///
			/// @note 不要设置为 true, 当前版本不支持 64 位绝对位置。设置为 true 是个保留的选项。
			///
			/// @param value
			///
			constexpr void G1_SetHas64BitAbsolutePosition(bool value)
			{
				base::bit::WriteBit(_array[1], 2, value);
			}

			///
			/// @brief 传感器格式描述信息可能改变，不是静态的。
			///
			/// @note 每次发生传感器错误，或者传感器停车后，传感器格式的描述信息都有可能发生改变
			/// 需要重新读取。这是给 PLC 看的，让 PLC 能够重新读取传感器格式，调整控制策略。
			///
			/// @return
			///
			constexpr bool G1_EncoderFormatMayBeChanged() const
			{
				return base::bit::ReadBit(_array[1], 29);
			}

			///
			/// @brief 设置传感器格式描述信息是否可能改变。
			///
			/// @param value
			///
			constexpr void G1_SetEncoderFormatMayBeChanged(bool value)
			{
				base::bit::WriteBit(_array[1], 29, value);
			}

			///
			/// @brief 传感器格式描述信息的有效性有可能改变。
			///
			/// @note 有效性的改变仅在传感器停车时可能发生。
			///
			/// @return
			///
			constexpr bool G1_EncoderFormatvalidityMayBeChanged() const
			{
				return !base::bit::ReadBit(_array[1], 30);
			}

			///
			/// @brief 设置传感器格式描述信息的有效性是否可能改变。
			///
			/// @param value
			///
			constexpr void G1_SetEncoderFormatvalidityMayBeChanged(bool value)
			{
				base::bit::WriteBit(_array[1], 30, !value);
			}

			///
			/// @brief 传感器格式描述信息的有效性。
			///
			/// @return
			///
			constexpr bool G1_EncoderFormatValidity() const
			{
				return base::bit::ReadBit(_array[1], 31);
			}

			///
			/// @brief 设置传感器格式描述信息的有效性。
			///
			/// @param value
			///
			constexpr void G1_SetEncoderFormatValidity(bool value)
			{
				base::bit::WriteBit(_array[1], 31, value);
			}

			///
			/// @brief 传感器的分辨率。
			///
			/// @note 对于旋转编码器，就是旋转一圈产生的脉冲数。不包括脉冲细分的部分。
			/// 细分相当于倍频，这里要的是原始的脉冲数。
			///
			/// @return
			///
			constexpr uint32_t G1_Resolution() const
			{
				return _array[2];
			}

			///
			/// @brief 设置传感器的分辨率。
			///
			/// @param value
			///
			constexpr void G1_SetResolution(uint32_t value)
			{
				_array[2] = value;
			}

			///
			/// @brief G1_XIST1 高分辨率移位因子移位的比特数。
			///
			/// @return
			///
			constexpr uint32_t G1_Xist1ShiftBitCount() const
			{
				return _array[3];
			}

			///
			/// @brief 设置 G1_XIST1 高分辨率移位因子移位的比特数。
			///
			/// @param value
			///
			constexpr void G1_SetXist1ShiftBitCount(uint32_t value)
			{
				_array[3] = value;
			}

			///
			/// @brief G1_XIST2 高分辨率移位因子移位的比特数。
			///
			/// @return
			///
			constexpr uint32_t G1_Xist2ShiftBitCount() const
			{
				return _array[4];
			}

			///
			/// @brief 设置 G1_XIST2 高分辨率移位因子移位的比特数。
			///
			/// @param value
			///
			constexpr void G1_SetXist2ShiftBitCount(uint32_t value)
			{
				_array[4] = value;
			}

			///
			/// @brief 多圈分辨率。
			///
			/// @note 能够记录转过的最大圈数，计数到此值后，再转一圈就溢出了。
			///
			/// @note 此值大于 1 时必须支持在 Gx_XIST2 中传输绝对位置。
			///
			/// @return
			///
			constexpr uint32_t G1_MultiTurnResolution() const
			{
				return _array[5];
			}

			///
			/// @brief 设置多圈分辨率。
			///
			/// @param value
			///
			constexpr void G1_SetMultiTurnResolution(uint32_t value)
			{
				_array[5] = value;
			}

			/* #endregion */
		};

	} // namespace profidrive
} // namespace base
