#pragma once
#include <stdint.h>

namespace base
{
	namespace profinet
	{
		/// @brief DCP 请求帧中的服务 ID.
		enum class DcpServiceIdEnum : uint8_t
		{
			Get = 0x03,
			Set = 0x04,
			Identify = 0x05,
			Hello = 0x06,
		};
	} // namespace profinet
} // namespace base
