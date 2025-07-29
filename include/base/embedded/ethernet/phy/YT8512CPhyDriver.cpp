#include "YT8512CPhyDriver.h"
#include "base/embedded/ethernet/parameter.h"
#include "base/string/define.h"
#include "base/unit/Mbps.h"

base::ethernet::YT8512CPhyDriver::YT8512CPhyDriver(base::ethernet::EthernetController const &controller)
	: _ethernet_controller(controller)
{
}

base::ethernet::EthernetController &base::ethernet::YT8512CPhyDriver::EthernetController()
{
	return _ethernet_controller;
}

base::ethernet::DuplexMode base::ethernet::YT8512CPhyDriver::DuplexMode()
{
	uint32_t register_value = ReadRegister(0x11);
	uint32_t const mask = 0b1 << 13;
	uint32_t duplex_register = (register_value & mask) >> 13;

	if (duplex_register)
	{
		return base::ethernet::DuplexMode::FullDuplex;
	}

	return base::ethernet::DuplexMode::HalfDuplex;
}

base::unit::Mbps base::ethernet::YT8512CPhyDriver::Speed()
{
	uint32_t register_value = ReadRegister(0x11);
	uint32_t const mask = 0b11 << 14;
	uint32_t duplex_register = (register_value & mask) >> 14;

	if (duplex_register == 0b00)
	{
		return base::unit::Mbps{10};
	}
	else if (duplex_register == 0b01)
	{
		return base::unit::Mbps{100};
	}
	else if (duplex_register == 0b01)
	{
		return base::unit::Mbps{1000};
	}
	else
	{
		throw std::runtime_error{CODE_POS_STR + "读取连接速率寄存器时读取到保留值。"};
	}
}
