#pragma once
#include "base/embedded/usb/DescriptorType.h"
#include "base/stream/ReadOnlySpan.h"
#include "base/stream/Span.h"
#include "base/string/define.h"
#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <string>

namespace base
{
	namespace usb
	{
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

			void Initialize(base::usb::DescriptorType type, base::ReadOnlySpan const &span)
			{
				if (span.Size() > sizeof(_data))
				{
					throw std::invalid_argument{CODE_POS_STR + "数据过长。"};
				}

				_length = span.Size();
				_type = type;
				DataSpan().CopyFrom(span);
			}

		public:
			Descriptor() = default;

			Descriptor(base::usb::DescriptorType type, base::ReadOnlySpan const &span)
			{
				Initialize(type, span);
			}

			///
			/// @brief 创建字符串描述符。
			///
			/// @param unicode_string 字符串。这其中的字符编码必须是 UTF16-LE.
			///
			Descriptor(std::string const &unicode_string)
			{
				if (unicode_string.size() % 2 != 0)
				{
					// 字符编码必须是 UTF16-LE。
					// 字符串长度为奇数说明肯定不是 UTF16-LE 编码的。
					throw std::invalid_argument{CODE_POS_STR + "必须是 UTF16-LE 编码的字符串。"};
				}

				base::ReadOnlySpan str_span{
					reinterpret_cast<uint8_t const *>(unicode_string.data()),
					unicode_string.size(),
				};

				Initialize(base::usb::DescriptorType::String, str_span);
			}

			uint8_t Length() const
			{
				return _length;
			}

			base::usb::DescriptorType Type() const
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
