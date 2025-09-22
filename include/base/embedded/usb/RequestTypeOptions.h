#pragma once

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

		class RequestTypeOptions
		{
		private:
			base::usb::RecipientType _recipient_type{};
			base::usb::RequestType _request_type{};
			base::usb::DataDirection _data_direction{};

		public:
			constexpr RequestTypeOptions() = default;

			constexpr RequestTypeOptions(base::usb::RecipientType recipient_type,
										 base::usb::RequestType request_type,
										 base::usb::DataDirection data_direction)
			{
				_recipient_type = recipient_type;
				_request_type = request_type;
				_data_direction = data_direction;
			}
		};

	} // namespace usb
} // namespace base
