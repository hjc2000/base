#pragma once
#include "base/bit/AutoBitConverter.h"
#include "base/net/profinet/dcp/DcpServiceIdEnum.h"
#include "base/net/profinet/dcp/DcpServiceTypeEnum.h"
#include "base/stream/ReadOnlySpan.h"
#include "base/string/define.h"
#include <stdexcept>

namespace base::profinet
{
	///
	/// @brief DCP 头部读者。
	///
	class DcpHeaderReader
	{
	private:
		base::ReadOnlySpan _span;

	public:
		DcpHeaderReader(base::ReadOnlySpan const &span)
		{
			if (span.Size() < 10)
			{
				throw std::invalid_argument{CODE_POS_STR + "传入的 span 的大小必须 >= 10."};
			}

			_span = span;
		}

		base::profinet::DcpServiceIdEnum ServiceId() const
		{
			return static_cast<base::profinet::DcpServiceIdEnum>(_span[0]);
		}

		base::profinet::DcpServiceTypeEnum ServiceType() const
		{
			return static_cast<base::profinet::DcpServiceTypeEnum>(_span[1]);
		}

		uint32_t Xid() const
		{
			base::ReadOnlySpan span = _span.Slice(base::Range{2, 6});
			return base::big_endian_remote_converter.FromBytes<uint32_t>(span);
		}

		///
		/// @brief 响应延迟。
		/// @return
		///
		uint16_t ResponseDelay() const
		{
			base::ReadOnlySpan span = _span.Slice(base::Range{6, 8});
			return base::big_endian_remote_converter.FromBytes<uint16_t>(span);
		}

		///
		/// @brief Blocks 的有效数据的长度，包括填充字节。
		///
		/// @note 填充是为了 2 字节对齐，每一个 Block 都必须 2 字节对齐，如果没有对齐，
		/// 尾部需要填充 1 字节。
		///
		/// @return
		///
		uint16_t DataLength() const
		{
			base::ReadOnlySpan span = _span.Slice(base::Range{8, 10});
			return base::big_endian_remote_converter.FromBytes<uint16_t>(span);
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
