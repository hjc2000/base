#pragma once
#include "base/embedded/gpio/GpioPin.h"
#include "base/embedded/iic/IicHost.h"
#include "base/embedded/Slot.h"
#include "base/stream/Span.h"
#include "base/task/delay.h"
#include "base/task/Mutex.h"
#include <bit>
#include <cstdint>
#include <functional>
#include <memory>

namespace base::extended_io
{
	class PCF8574Operator;

	///
	/// @brief 这是一个使用 IIC 接口控制的扩展 IO 芯片。
	///
	/// @note 每个引脚内部是一个开关管，所谓的写 1 就是将开关管关断，写 0 就是将开关管打开。
	/// 所以引脚外部需要使用上拉的方式进行接线。例如接 LED 时，需要将阴极连接到本芯片的引脚，
	/// 阳极连接着电源。
	///
	/// @note 引脚电平发生变化后，会导致 PCF8574 的 INT 引脚变成低电平。这可以用来触发单片机
	/// 的外部中断。INT 引脚变成低电平后，必须对 PCF8574 进行一次写入或读取操作才能将 INT 恢复
	/// 成高电平。
	///
	/// @note 因为写入操作也有恢复 PCF8574 的 INT 为高电平的功能，所以可以推测写入操作不会导致
	/// PCF8574 做出反应，进而触发 INT. 这点与单片机的 GPIO 不同。很多单片机的 GPIO 如果在输出
	/// 模式下又开启中断功能，自己写自己的引脚也会触发中断。
	///
	class PCF8574
	{
	private:
		friend class PCF8574Operator;
		base::task::Mutex _lock;
		base::gpio::GpioPin _interrupt_pin;
		std::shared_ptr<base::iic::IicHost> _iic_host;

		///
		/// @brief 地址寄存器。高 4 位固定为 0b0100，低 4 位中的高 3 位是地址，最低位用来表示
		/// 读操作还是写操作。最低位为 1 表示读操作，最低位为 0 表示写操作。
		///
		uint8_t _address_register = 0b01000000;

	public:
		///
		/// @brief 构造函数。
		///
		/// @param interrupt_pin PCF8574 具有中断功能，需要一个中断输入引脚。
		///
		/// @param iic_host 本对象需要一个 IIC 主机接口来控制 PCF8574 芯片。
		///
		/// @param address PCF8574 芯片有一个地址，操作时需要用地址来指定芯片，一个 IIC 总线上可以挂
		/// 多个 PCF8574 芯片。允许的地址范围为 [0, 7]，因为芯片上总共有 3 个引脚，用来接低电平或高电平
		/// 表示地址。
		///
		PCF8574(base::gpio::GpioPin interrupt_pin,
				std::shared_ptr<base::iic::IicHost> const &iic_host,
				uint8_t address);

		~PCF8574()
		{
			// UnregisterInterruptCallback();
		}
	};

	class PCF8574Operator
	{
	private:
		PCF8574 &_pcf8574;
		base::task::MutexGuard _guard;

	public:
		PCF8574Operator(PCF8574 &pcf8574)
			: _pcf8574(pcf8574),
			  _guard(pcf8574._lock)
		{
		}

		///
		/// @brief 注册中断回调函数。
		///
		/// @param func
		///
		void RegisterInterruptCallback(std::function<void()> const &func)
		{
			_pcf8574._interrupt_pin.RegisterInterruptCallback(func);
		}

		///
		/// @brief 取消注册中断回调函数。
		///
		void UnregisterInterruptCallback()
		{
			_pcf8574._interrupt_pin.UnregisterInterruptCallback();
		}

		/* #region 读写位 */

		///
		/// @brief 读取一个位。即读取指定索引的 IO 端子的电平。
		///
		/// @param index IO 端子的索引。
		///
		/// @return
		///
		bool ReadBit(int index)
		{
			uint8_t data = ReadByte(index / 8);
			uint8_t mask = 0x1 << (index % 8);
			return data & mask;
		}

		///
		/// @brief 写 1 个位。即写指定索引的 IO 端子的电平。
		///
		/// @param index IO 端子的索引。
		///
		/// @param value IO 端子的电平。
		///
		void WriteBit(int index, bool value)
		{
			uint8_t byte = ReadByte(index / 8);
			uint8_t mask = 0x1 << (index % 8);
			if (value)
			{
				byte |= mask;
			}
			else
			{
				byte &= ~mask;
			}

			WriteByte(index / 8, byte);
		}

		///
		/// @brief 翻转一个位。
		///
		/// @param index
		///
		void ToggleBit(int index)
		{
			bool bit = ReadBit(index);
			WriteBit(index, !bit);
		}

		/* #endregion */

		/* #region 读写字节 */

		///
		/// @brief 读取一个字节。这是一个 8 位的 IO 扩展芯片，读取 1 个字节意味着读取
		/// 所有 IO 端子的电平。
		///
		/// @param index 索引。要读取第几个字节。
		///
		/// @return
		///
		uint8_t ReadByte(int index)
		{
			base::iic::IicHostOperator op{*_pcf8574._iic_host};

			op.Initialize(base::unit::Nanosecond{std::chrono::microseconds{4}},
						  base::unit::Nanosecond{std::chrono::microseconds{4} * 20});

			op.SendStartingSignal();
			op.SendByte(_pcf8574._address_register | 0x01);
			uint8_t data = op.ReceiveByte(true);
			op.SendStoppingSignal();
			return data;
		}

		///
		/// @brief 写 1 个字节。这是 1 个 8 位的 IO 扩展芯片，写 1 个字节意味着设置所有
		/// IO 端子的电平。
		///
		/// @param index 索引。要写入第几个字节。
		///
		/// @param value
		///
		void WriteByte(int index, uint8_t value)
		{
			base::iic::IicHostOperator op{*_pcf8574._iic_host};

			op.Initialize(base::unit::Nanosecond{std::chrono::microseconds{4}},
						  base::unit::Nanosecond{std::chrono::microseconds{4} * 20});

			op.SendStartingSignal();
			op.SendByte(_pcf8574._address_register | 0x00);
			op.SendByte(value);
			op.SendStoppingSignal();
			base::task::Delay(std::chrono::milliseconds{10});
		}

		///
		/// @brief 读取多个字节到 span 中。
		///
		/// @param addr IO 端口中的字节的起始地址。
		///
		/// @param span 读取到的字节被写入此 span.
		///
		void Read(int addr, base::Span const &span)
		{
			for (int i = 0; i < span.Size(); i++)
			{
				span[i] = ReadByte(addr + i);
			}
		}

		/* #endregion */

		/* #region 读写整型 */

		///
		/// @brief 读取 IO 端口中指定索引处的一个 uint16_t 数据。
		///
		/// @param index
		///
		/// @return
		///
		uint16_t ReadUInt16(int index)
		{
			uint16_t data = 0;

			base::Span span{
				reinterpret_cast<uint8_t *>(&data),
				sizeof(data),
			};

			Read(index * 2, span);

			/* 刚才的操作方式是低字节放到数组的低索引处，这是小端序，
			 * 如果本机字节序是大端序，需要翻转。
			 */
			if (std::endian::native == std::endian::big)
			{
				span.Reverse();
			}

			return data;
		}

		///
		/// @brief 读取 IO 端口中指定索引处的一个 uint32_t 数据。
		///
		/// @param index
		///
		/// @return
		///
		uint32_t ReadUInt32(int index)
		{
			uint32_t data = 0;

			base::Span span{
				reinterpret_cast<uint8_t *>(&data),
				sizeof(data),
			};

			Read(index * 2, span);

			/* 刚才的操作方式是低字节放到数组的低索引处，这是小端序，
			 * 如果本机字节序是大端序，需要翻转。
			 */
			if (std::endian::native == std::endian::big)
			{
				span.Reverse();
			}

			return data;
		}

		///
		/// @brief 读取 IO 端口中指定索引处的一个 uint64_t 数据。
		///
		/// @param index
		///
		/// @return
		///
		uint64_t ReadUInt64(int index)
		{
			uint64_t data = 0;

			base::Span span{
				reinterpret_cast<uint8_t *>(&data),
				sizeof(data),
			};

			Read(index * 2, span);

			/* 刚才的操作方式是低字节放到数组的低索引处，这是小端序，
			 * 如果本机字节序是大端序，需要翻转。
			 */
			if (std::endian::native == std::endian::big)
			{
				span.Reverse();
			}

			return data;
		}

		/* #endregion */
	};

	base::Slot<base::extended_io::PCF8574> &pcf8574_slot();

} // namespace base::extended_io

inline base::extended_io::PCF8574::PCF8574(base::gpio::GpioPin interrupt_pin,
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
