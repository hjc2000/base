#include "MulticastMacCollection.h"

namespace
{
    constinit uint8_t _dcp_identify_mac_buffer[] = {0x01, 0x0e, 0xcf, 0x00, 0x00, 0x00};
    constinit uint8_t _dcp_hello_mac_buffer[] = {0x01, 0x0e, 0xcf, 0x00, 0x00, 0x00};
} // namespace

base::Mac base::profinet::MulticastMacCollection::DcpIdentify()
{
    return base::Mac{std::endian::big, base::Array<uint8_t, 6>{_dcp_identify_mac_buffer, 0, 6}};
}

base::Mac base::profinet::MulticastMacCollection::DcpHello()
{
    return base::Mac{std::endian::big, base::Array<uint8_t, 6>{_dcp_hello_mac_buffer, 0, 6}};
}
