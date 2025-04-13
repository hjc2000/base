#include "gpio_parameter.h"

std::string base::to_string(base::gpio::PortEnum port)
{
	switch (port)
	{
	case base::gpio::PortEnum::PortA:
		{
			return "PA";
		}
	case base::gpio::PortEnum::PortB:
		{
			return "PB";
		}
	case base::gpio::PortEnum::PortC:
		{
			return "PC";
		}
	case base::gpio::PortEnum::PortD:
		{
			return "PD";
		}
	case base::gpio::PortEnum::PortE:
		{
			return "PE";
		}
	case base::gpio::PortEnum::PortF:
		{
			return "PF";
		}
	case base::gpio::PortEnum::PortG:
		{
			return "PG";
		}
	case base::gpio::PortEnum::PortH:
		{
			return "PH";
		}
	case base::gpio::PortEnum::PortI:
		{
			return "PI";
		}
	case base::gpio::PortEnum::PortJ:
		{
			return "PJ";
		}
	case base::gpio::PortEnum::PortK:
		{
			return "PK";
		}
	case base::gpio::PortEnum::PortL:
		{
			return "PL";
		}
	case base::gpio::PortEnum::PortM:
		{
			return "PM";
		}
	case base::gpio::PortEnum::PortN:
		{
			return "PN";
		}
	case base::gpio::PortEnum::PortO:
		{
			return "PO";
		}
	case base::gpio::PortEnum::PortP:
		{
			return "PP";
		}
	default:
		{
			return "未知端口";
		}
	}
}
