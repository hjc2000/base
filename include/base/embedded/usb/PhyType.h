#pragma once

namespace base
{
	namespace usb
	{
		enum class PhyType
		{
			///
			/// @brief 低引脚数外置 PHY.
			///
			ULPI,

			///
			/// @brief 高引脚数外置 PHY.
			///
			UTMI,

			///
			/// @brief 内置 PHY.
			///
			Embedded,
		};

	} // namespace usb
} // namespace base
