#pragma once

namespace base
{
	namespace usb
	{
		///
		/// @brief 数据传输方向。
		///
		enum class DataDirection
		{
			///
			/// @brief 主机到设备。
			///
			HostToDevice,

			///
			/// @brief 设备到主机。
			///
			DeviceToHost,
		};

	} // namespace usb
} // namespace base
