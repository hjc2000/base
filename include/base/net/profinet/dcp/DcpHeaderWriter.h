#pragma once
#include "base/bit/AutoBitConverter.h"
#include "base/net/profinet/dcp/DcpServiceIdEnum.h"
#include "base/net/profinet/dcp/DcpServiceTypeEnum.h"
#include "base/stream/Span.h"
#include "base/string/define.h"
#include <stdexcept>

namespace base::profinet
{
	///
	/// @brief DCP 头部作者。
	///
	class DcpHeaderWriter
	{
	private:
		base::Span _span;

	public:
		DcpHeaderWriter(base::Span const &span)
		{
			if (span.Size() < 10)
			{
				throw std::invalid_argument{CODE_POS_STR + "传入的 span 的大小必须 >= 10."};
			}

			_span = span;
		}

		void WriteServiceId(base::profinet::DcpServiceIdEnum value)
		{
			_span[0] = static_cast<uint8_t>(value);
		}

		void WriteServiceType(base::profinet::DcpServiceTypeEnum value)
		{
			_span[1] = static_cast<uint8_t>(value);
		}

		void WriteXid(uint32_t value)
		{
			base::Span span = _span.Slice(base::Range{2, 6});
			base::big_endian_remote_converter.GetBytes(value, span);
		}

		///
		/// @brief 响应延迟。
		///
		/// @param value
		///
		void WriteResponseDelay(uint16_t value)
		{
			base::Span span = _span.Slice(base::Range{6, 8});
			base::big_endian_remote_converter.GetBytes(value, span);
		}

		///
		/// @brief Blocks 的有效数据的长度，包括填充字节。
		///
		/// @note 填充是为了 2 字节对齐，每一个 Block 都必须 2 字节对齐，如果没有对齐，
		/// 尾部需要填充 1 字节。
		///
		/// @param value
		///
		void WriteDataLength(uint16_t value)
		{
			base::Span span = _span.Slice(base::Range{8, 10});
			base::big_endian_remote_converter.GetBytes(value, span);
		}

		///
		/// @brief 头部固定为 10 字节。
		///
		/// @return
		///
		static constexpr int32_t HeaderSize()
		{
			return 10;
		}
	};

} // namespace base::profinet
