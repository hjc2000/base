#include "serial_handle.h"

void base::serial::start(base::serial::serial_handle &h)
{
	start(h,
		  base::serial::Direction::RX_TX,
		  base::serial::BaudRate{115200},
		  base::serial::DataBits{8},
		  base::serial::Parity::None,
		  base::serial::StopBits::One,
		  base::serial::HardwareFlowControl::None);
}

void base::serial::start(base::serial::serial_handle &h,
						 base::serial::BaudRate const &baud_rate)
{
	start(h,
		  base::serial::Direction::RX_TX,
		  baud_rate,
		  base::serial::DataBits{8},
		  base::serial::Parity::None,
		  base::serial::StopBits::One,
		  base::serial::HardwareFlowControl::None);
}
