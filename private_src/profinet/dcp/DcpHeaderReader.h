#pragma once
#include <base/bit/AutoBitConverter.h>
#include <base/net/profinet/dcp/DcpServiceIdEnum.h>
#include <base/net/profinet/dcp/DcpServiceTypeEnum.h>
#include <base/pch.h>
#include <base/stream/ReadOnlySpan.h>

namespace base
{
	namespace profinet
	{
		/// @brief DCP 头部阅读器。
		class DcpHeaderReader
		{
		private:
			base::ReadOnlySpan _span;
			base::AutoBitConverter _converter{std::endian::big};

		public:
			DcpHeaderReader(base::ReadOnlySpan const &span);

			base::profinet::DcpServiceIdEnum ServiceId() const;

			base::profinet::DcpServiceTypeEnum ServiceType() const;

			uint32_t Xid() const;

			/// @brief 响应延迟。
			/// @return
			uint16_t ResponseDelay() const;

			/// @brief Blocks 的有效数据的长度，包括填充字节。
			/// @note 填充是为了 2 字节对齐，每一个 Block 都必须 2 字节对齐，如果没有对齐，
			/// 尾部需要填充 1 字节。
			/// @return
			uint16_t DataLength() const;

			/// @brief 头部固定为 10 字节。
			/// @return
			static_function constexpr int32_t HeaderSize()
			{
				return 10;
			}
		};
	} // namespace profinet
} // namespace base
