#pragma once

#include "base/embedded/gpio/gpio_parameter.h"
#include "base/embedded/gpio/GpioPin.h"

namespace base
{
	namespace iic
	{
		/* #region ISoftwareIicHostPinDriver */

		class ISoftwareIicHostPinDriver
		{
		public:
			///
			/// @brief 写 SCL 引脚的值。
			///
			/// @param value
			///
			virtual void WriteSCL(bool value) = 0;

			///
			/// @brief 更改 SDA 引脚的 IO 方向。
			///
			/// @warning 改变方向和读写是分开的。不要自作聪明，在 WriteSDA 的实现中将 SDA
			/// 引脚方向切换为输出，在 ReadSDA 的实现中将 SDA 引脚的方向切换为输入。
			///
			/// @param value
			///
			virtual void ChangeSDADirection(base::gpio::Direction value) = 0;

			///
			/// @brief 写 SDA 引脚的值。
			///
			/// @param value
			///
			virtual void WriteSDA(bool value) = 0;

			///
			/// @brief 读 SDA 引脚的值。
			///
			/// @return
			///
			virtual bool ReadSDA() const = 0;
		};

		template <typename GpioType>
		class SoftwareIicHostPinDriver :
			public base::iic::ISoftwareIicHostPinDriver
		{
		public:
			///
			/// @brief 写 SCL 引脚的值。
			///
			/// @param value
			///
			virtual void WriteSCL(bool value) override = 0;

			///
			/// @brief 更改 SDA 引脚的 IO 方向。
			///
			/// @param value
			///
			virtual void ChangeSDADirection(base::gpio::Direction value) override = 0;

			///
			/// @brief 写 SDA 引脚的值。
			///
			/// @param value
			///
			virtual void WriteSDA(bool value) override = 0;

			///
			/// @brief 读 SDA 引脚的值。
			///
			/// @return
			///
			virtual bool ReadSDA() const override = 0;
		};

		/* #endregion */

		/* #region 针对 base::gpio::GpioPin 特化 */

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
				_sda_pin.InitializeAsOutputMode();

				_scl_pin.WritePin(true);
				_sda_pin.WritePin(true);
			}

			///
			/// @brief 写 SCL 引脚的值。
			///
			/// @param value
			///
			virtual void WriteSCL(bool value) final override
			{
				_scl_pin.WritePin(value);
			}

			///
			/// @brief 更改 SDA 引脚的 IO 方向。
			///
			/// @warning 改变方向和读写是分开的。不要自作聪明，在 WriteSDA 的实现中将 SDA
			/// 引脚方向切换为输出，在 ReadSDA 的实现中将 SDA 引脚的方向切换为输入。
			///
			/// @param value
			///
			virtual void ChangeSDADirection(base::gpio::Direction value) final override
			{
				if (value == base::gpio::Direction::Input)
				{
					_sda_pin.InitializeAsInputMode();
				}
				else
				{
					_sda_pin.InitializeAsOutputMode();
				}
			}

			///
			/// @brief 写 SDA 引脚的值。
			///
			/// @param value
			///
			virtual void WriteSDA(bool value) final override
			{
				_sda_pin.WritePin(value);
			}

			///
			/// @brief 读 SDA 引脚的值。
			///
			/// @return
			///
			virtual bool ReadSDA() const final override
			{
				return _sda_pin.ReadPin();
			}
		};

		/* #endregion */

	} // namespace iic
} // namespace base
