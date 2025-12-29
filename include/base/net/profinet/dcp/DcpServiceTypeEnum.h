#pragma once
#include <cstdint>
#include <string>

namespace base
{
	namespace profinet
	{
		///
		/// @brief DCP 服务类型
		///
		enum class DcpServiceTypeEnum : uint8_t
		{
			///
			/// @brief 请求。
			///
			Request = 0x00,

			///
			/// @brief 响应，表示请求成功。
			///
			ResponseSuccess = 0x01,

			///
			/// @brief 响应，表示请求不被支持。
			///
			ResponseNotSupport = 0x05,
		};

	} // namespace profinet

	std::string to_string(base::profinet::DcpServiceTypeEnum value);

} // namespace base
