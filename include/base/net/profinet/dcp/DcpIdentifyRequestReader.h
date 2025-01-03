#pragma once
#include <base/net/profinet/dcp/DcpServiceIdEnum.h>
#include <base/net/profinet/dcp/DcpServiceTypeEnum.h>
#include <base/net/profinet/fid-pdu/FidApduReader.h>

namespace base
{
	namespace profinet
	{
		/// @brief DCP Identify 请求帧阅读器。
		class DcpIdentifyRequestReader
		{
		private:
			base::profinet::FidApduReader _fid_pdu_reader;
			base::ReadOnlySpan _this_span;

		public:
			DcpIdentifyRequestReader(base::ReadOnlySpan const &span);

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

#pragma region Blocks
			/// @brief 是否具有站点名称块。
			/// @return 有则返回 true，没有则返回 false.
			bool HasNameOfStationBlock() const;

			/// @brief 站点名称。
			/// @note 只有 HasNameOfStationBlock 属性为 true 时本属性才有效。
			/// HasNameOfStationBlock 为 false 时访问本属性会抛出异常。
			/// @return
			std::string NameOfStation() const;
#pragma endregion
		};
	} // namespace profinet
} // namespace base
