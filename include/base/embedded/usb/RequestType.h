#pragma once

namespace base
{
	namespace usb
	{
		///
		/// @brief 请求类型。
		///
		enum class RequestType
		{
			///
			/// @brief 标准请求。
			///
			Standard,

			///
			/// @brief 类请求。
			///
			Class,

			///
			/// @brief 厂商请求。
			///
			Vendor,
		};

	} // namespace usb
} // namespace base
