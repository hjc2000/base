#pragma once
#include <stdint.h>
#include <string>

namespace base
{
	namespace profinet
	{
		///
		/// @brief DCP 请求帧中的服务 ID.
		///
		enum class DcpServiceIdEnum : uint8_t
		{
			Get = 0x03,
			Set = 0x04,
			Identify = 0x05,
			Hello = 0x06,
		};

	} // namespace profinet

	///
	/// @brief 将 DcpServiceIdEnum 转为字符串。
	///
	/// @param value
	///
	/// @return
	///
	std::string to_string(base::profinet::DcpServiceIdEnum value);

} // namespace base
