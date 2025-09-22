#pragma once
#include <cstdint>

namespace base
{
	namespace usb
	{
		///
		/// @brief 接收者类型。
		///
		enum class RecipientType : uint8_t
		{
			///
			/// @brief 设备。
			///
			Device,

			///
			/// @brief 接口。
			///
			Interface,

			///
			/// @brief 端点。
			///
			Endpoint,

			///
			/// @brief 其他。
			///
			Other,
		};

	} // namespace usb
} // namespace base
