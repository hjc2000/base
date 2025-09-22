#include "PCF8574.h" // IWYU pragma: keep
#include "base/SingletonProvider.h"

base::extended_io::PCF8574::PCF8574(base::gpio::GpioPin interrupt_pin,
									std::shared_ptr<base::iic::IicHost> const &iic_host,
									uint8_t address)
	: _interrupt_pin(interrupt_pin)
{
	_iic_host = iic_host;

	if (address > 0b111)
	{
		throw std::out_of_range{"地址超出范围。允许的地址范围为 [0, 7]"};
	}

	_address_register = 0b01000000 | (address << 1);

	// 打开中断引脚
	_interrupt_pin.InitializeAsInputMode(base::gpio::PullMode::PullUp,
										 base::gpio::TriggerEdge::FallingEdge);

	// 初始化后将所有引脚置为高电平。即让芯片内每个引脚的开关管关断。
	PCF8574Operator op{*this};
	op.WriteByte(0, 0xff);
}

namespace
{
	base::SingletonProvider<base::Slot<base::extended_io::PCF8574>> _provider{};
}

base::Slot<base::extended_io::PCF8574> &base::extended_io::pcf8574_slot()
{
	return _provider.Instance();
}
