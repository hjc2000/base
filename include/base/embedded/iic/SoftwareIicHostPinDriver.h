#pragma once

#include "base/embedded/gpio/gpio_parameter.h"
#include "base/embedded/gpio/GpioPin.h"

namespace base
{
	namespace iic
	{
		class ISoftwareIicHostPinDriver
		{
		public:
			/// @brief 写 SCL 引脚的值。
			/// @param value
			virtual void WriteSCL(bool value) = 0;

			/// @brief 更改 SDA 引脚的 IO 方向。
			/// @param value
			virtual void ChangeSDADirection(base::gpio::Direction value) = 0;

			/// @brief 写 SDA 引脚的值。
			/// @param value
			virtual void WriteSDA(bool value) = 0;

			/// @brief 读 SDA 引脚的值。
			/// @return
			virtual bool ReadSDA() const = 0;
		};

		template <typename GpioType>
		class SoftwareIicHostPinDriver :
			public base::iic::ISoftwareIicHostPinDriver
		{
		public:
			/// @brief 写 SCL 引脚的值。
			/// @param value
			virtual void WriteSCL(bool value) override = 0;

			/// @brief 更改 SDA 引脚的 IO 方向。
			/// @param value
			virtual void ChangeSDADirection(base::gpio::Direction value) override = 0;

			/// @brief 写 SDA 引脚的值。
			/// @param value
			virtual void WriteSDA(bool value) override = 0;

			/// @brief 读 SDA 引脚的值。
			/// @return
			virtual bool ReadSDA() const override = 0;
		};

		template <>
		class SoftwareIicHostPinDriver<base::gpio::GpioPin> :
			public base::iic::ISoftwareIicHostPinDriver
		{
		private:
			base::gpio::GpioPin _scl_pin;
			base::gpio::GpioPin _sda_pin;

		public:
			SoftwareIicHostPinDriver(base::gpio::GpioPin const &scl_pin,
									 base::gpio::GpioPin const &sda_pin)
				: _scl_pin(scl_pin),
				  _sda_pin(sda_pin)
			{
				_scl_pin.InitializeAsOutputMode();
			}

			/// @brief 写 SCL 引脚的值。
			/// @param value
			virtual void WriteSCL(bool value) override;

			/// @brief 更改 SDA 引脚的 IO 方向。
			/// @param value
			virtual void ChangeSDADirection(base::gpio::Direction value) override;

			/// @brief 写 SDA 引脚的值。
			/// @param value
			virtual void WriteSDA(bool value) override;

			/// @brief 读 SDA 引脚的值。
			/// @return
			virtual bool ReadSDA() const override;
		};

	} // namespace iic
} // namespace base
