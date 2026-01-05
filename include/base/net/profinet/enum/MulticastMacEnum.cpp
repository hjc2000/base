#include "MulticastMacEnum.h"

namespace
{
	constinit uint8_t _dcp_identify_mac_buffer[] = {0x01, 0x0e, 0xcf, 0x00, 0x00, 0x00};
	constinit uint8_t _dcp_hello_mac_buffer[] = {0x01, 0x0e, 0xcf, 0x00, 0x00, 0x01};
} // namespace

base::Mac const base::profinet::MulticastMacEnum::DcpIdentify()
{
	return base::Mac{
		std::endian::big,
		base::Array<uint8_t, 6>{
			base::ReadOnlyArraySpan<uint8_t>{
				_dcp_identify_mac_buffer,
				sizeof(_dcp_identify_mac_buffer),
			},
		},
	};
}

base::Mac const base::profinet::MulticastMacEnum::DcpHello()
{
	return base::Mac{
		std::endian::big,
		base::Array<uint8_t, 6>{
			base::ReadOnlyArraySpan<uint8_t>{
				_dcp_hello_mac_buffer,
				sizeof(_dcp_hello_mac_buffer),
			},
		},
	};
}
