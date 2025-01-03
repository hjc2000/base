#pragma once
#include <base/bit/AutoBitConverter.h>
#include <base/net/profinet/dcp/DcpServiceIdEnum.h>
#include <base/net/profinet/dcp/DcpServiceTypeEnum.h>
#include <base/stream/Span.h>

namespace base
{
	namespace profinet
	{
		class DcpHeaderWriter
		{
		private:
			base::Span _span;
			base::AutoBitConverter _converter{std::endian::big};

		public:
			DcpHeaderWriter(base::Span const &span);

			base::profinet::DcpServiceIdEnum ServiceId() const;
			void SetServiceId(base::profinet::DcpServiceIdEnum value);

			base::profinet::DcpServiceTypeEnum ServiceType() const;
			void SetServiceType(base::profinet::DcpServiceTypeEnum value);

			uint32_t Xid() const;
			void SetXid(uint32_t value);

			/// @brief Blocks 的有效数据的长度，包括填充字节。
			/// @note 填充是为了 2 字节对齐，每一个 Block 都必须 2 字节对齐，如果没有对齐，
			/// 尾部需要填充 1 字节。
			/// @return
			uint16_t DataLength() const;

			void SetDataLength(uint16_t value);

			/// @brief 头部固定为 10 字节。
			/// @return
			static constexpr int32_t Size()
			{
				return 10;
			}
		};
	} // namespace profinet
} // namespace base
