#pragma once
#include "base/embedded/gpio/gpio_parameter.h"

namespace base::iic
{
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

} // namespace base::iic
