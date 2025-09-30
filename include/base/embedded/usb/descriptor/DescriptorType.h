#pragma once

namespace base::usb
{
	enum class DescriptorType
	{
		///
		/// @brief 设备描述符。
		///
		Device = 0x01,

		///
		/// @brief 配置描述符。
		///
		Configuration = 0x02,

		///
		/// @brief 字符串描述符。
		///
		String = 0x03,

		///
		/// @brief 接口描述符。
		///
		Interface = 0x04,

		///
		/// @brief 端点描述符。
		///
		Endpoint = 0x05,

		///
		/// @brief 设备限定描述符。
		///
		DeviceQualifier = 0x06,

		///
		/// @brief 其他速率配置描述符。
		///
		OtherSpeedConfiguration = 0x07,

		///
		/// @brief 接口功率描述符。
		///
		InterfacePower = 0x08,

		///
		/// @brief OTG 描述符。
		///
		OTG = 0x09,

		///
		/// @brief 调试描述符。
		///
		Debug = 0x0A,

		///
		/// @brief 接口关联描述符。
		///
		InterfaceAssociation = 0x0B,

		///
		/// @brief BOS 描述符。
		///
		BOS = 0x0F,

		///
		/// @brief 设备能力描述符。
		///
		DeviceCapability = 0x10,

		///
		/// @brief HID描述符。
		///
		HID = 0x21,

		///
		/// @brief HID 报告描述符。
		///
		HIDReport = 0x22,

		///
		/// @brief Hub 描述符。
		///
		Hub = 0x29,

		///
		/// @brief 超级速度 USB 端点伴随描述符。
		///
		SuperSpeedEndpointCompanion = 0x30,

		///
		/// @brief 超级速度 Plus 等时端点伴随描述符。
		///
		SuperSpeedPlusIsochronousEndpointCompanion = 0x31
	};

} // namespace base::usb
