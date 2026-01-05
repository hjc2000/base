#include "DcpServiceIdEnum.h"
#include "base/string/define.h"
#include "base/string/ToHexString.h"
#include <stdexcept>

std::string base::to_string(base::profinet::DcpServiceIdEnum value)
{
	std::string ret;
	switch (value)
	{
	case base::profinet::DcpServiceIdEnum::Get:
		{
			ret = "Get";
			break;
		}
	case base::profinet::DcpServiceIdEnum::Set:
		{
			ret = "Set";
			break;
		}
	case base::profinet::DcpServiceIdEnum::Identify:
		{
			ret = "Identify";
			break;
		}
	case base::profinet::DcpServiceIdEnum::Hello:
		{
			ret = "Hello";
			break;
		}
	default:
		{
			throw std::invalid_argument{CODE_POS_STR + "非法 DcpServiceIdEnum."};
		}
	}

	ret += " (" + base::ToHexString(static_cast<uint16_t>(value)) + ")";
	return ret;
}
