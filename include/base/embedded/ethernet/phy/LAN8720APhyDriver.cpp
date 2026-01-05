#include "LAN8720APhyDriver.h"
#include "base/unit/Mbps.h"

base::ethernet::LAN8720APhyDriver::LAN8720APhyDriver(base::ethernet::EthernetController const &controller)
	: _ethernet_controller(controller)
{
}

base::ethernet::EthernetController &base::ethernet::LAN8720APhyDriver::EthernetController()
{
	return _ethernet_controller;
}

base::ethernet::DuplexMode base::ethernet::LAN8720APhyDriver::DuplexMode()
{
	uint32_t register_value = ReadRegister(0x1F);
	uint32_t const mask = 0b10000;
	if (register_value & mask)
	{
		return base::ethernet::DuplexMode::FullDuplex;
	}

	return base::ethernet::DuplexMode::HalfDuplex;
}

base::unit::Mbps base::ethernet::LAN8720APhyDriver::Speed()
{
	uint32_t register_value = ReadRegister(0x1F);
	uint32_t const mask = 0b01000;
	if (register_value & mask)
	{
		return base::unit::Mbps{100};
	}

	return base::unit::Mbps{10};
}
