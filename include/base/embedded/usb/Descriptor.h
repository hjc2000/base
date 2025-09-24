#pragma once
#include "base/stream/ReadOnlySpan.h"
#include "base/stream/Span.h"
#include "base/string/define.h"
#include <cstddef>
#include <cstdint>
#include <stdexcept>

namespace base
{
	namespace usb
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

		///
		/// @brief USB 描述符。
		///
		class Descriptor
		{
		private:
			///
			/// @brief 描述符长度。
			///
			/// @note 包括长度字段自身以及描述符类型。
			/// 即
			/// 	_length = 1 + 1 + sizeof(_data)
			///
			uint8_t _length{};

			///
			/// @brief 描述符类型。
			///
			base::usb::DescriptorType _type{};

			///
			/// @brief 描述符数据。
			///
			/// @note 整个描述符最大长度为 255, 因此留给数据的只剩下 255 - 1 - 1 = 251 个字节。
			/// 即 255 减去 1 字节的长度字段，再减去 1 字节的描述符类型字段。
			///
			alignas(size_t) uint8_t _data[255 - 1 - 1];

		public:
			constexpr Descriptor() = default;

			Descriptor(base::usb::DescriptorType type, base::ReadOnlySpan const &span)
			{
				if (span.Size() > sizeof(_data))
				{
					throw std::invalid_argument{CODE_POS_STR + "数据过长。"};
				}

				_length = span.Size();
				_type = type;
				DataSpan().CopyFrom(span);
			}

			constexpr uint8_t Length() const
			{
				return _length;
			}

			constexpr base::usb::DescriptorType Type() const
			{
				return _type;
			}

			base::Span DataSpan()
			{
				return base::Span{_data, sizeof(_data)};
			}
		};

	} // namespace usb
} // namespace base
