#pragma once

#include "base/bit/bit.h"
#include <cstdint>

namespace base
{
	namespace usb
	{
		/* #region 参数类 */

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
		enum class RequestType : uint8_t
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
		enum class DataDirection : bool
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

		/* #endregion */

		///
		/// @brief 请求类型选项。
		///
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

			constexpr base::usb::RecipientType RecipientType() const
			{
				return _recipient_type;
			}

			constexpr base::usb::RequestType RequestType() const
			{
				return _request_type;
			}

			constexpr base::usb::DataDirection DataDirection() const
			{
				return _data_direction;
			}

			constexpr explicit operator uint8_t() const
			{
				uint8_t ret = 0;
				base::bit::WriteBits(ret, 0, 5, static_cast<uint64_t>(_recipient_type));
				base::bit::WriteBits(ret, 5, 7, static_cast<uint64_t>(_request_type));
				base::bit::WriteBit(ret, 7, static_cast<bool>(_data_direction));
				return ret;
			}
		};

	} // namespace usb
} // namespace base
