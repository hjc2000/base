#include "DcpServiceTypeEnum.h"
#include "base/string/define.h"
#include "base/string/ToHexString.h"
#include <base/string/define.h>

std::string base::to_string(base::profinet::DcpServiceTypeEnum value)
{
	std::string ret;
	switch (value)
	{
	case base::profinet::DcpServiceTypeEnum::Request:
		{
			ret = "Request";
			break;
		}
	case base::profinet::DcpServiceTypeEnum::ResponseSuccess:
		{
			ret = "ResponseSuccess";
			break;
		}
	case base::profinet::DcpServiceTypeEnum::ResponseNotSupport:
		{
			ret = "ResponseNotSupport";
			break;
		}
	default:
		{
			throw std::invalid_argument{CODE_POS_STR + "非法 DcpServiceTypeEnum."};
		}
	}

	ret += " (" + base::ToHexString(static_cast<uint16_t>(value)) + ")";
	return ret;
}
