#pragma once
#include "base/embedded/usb/DescriptorType.h"
#include "base/stream/ReadOnlySpan.h"
#include "base/stream/Span.h"
#include "base/string/define.h"
#include <cstdint>
#include <stdexcept>

namespace base
{
	namespace usb
	{
		class DescriptorWriter
		{
		private:
			base::Span _span{};

		public:
			DescriptorWriter() = default;

			///
			/// @brief 构造函数
			///
			/// @param span 接受一段内存，后续写入数据将在此段内存中写入。
			///
			DescriptorWriter(base::Span const &span)
			{
				if (span.Size() < 2)
				{
					// 至少需要能够容纳：
					// 		1 字节的长度字段。
					// 		1 字节的描述符类型。
					// 内容允许为空。
					throw std::invalid_argument{CODE_POS_STR + "span 过小。"};
				}

				_span = span;
			}

			void WriteLength(uint8_t length)
			{
				_span[0] = length;
			}

			void WriteDescriptorType(base::usb::DescriptorType type)
			{
				_span[1] = static_cast<uint8_t>(type);
			}

			///
			/// @brief 写入数据。
			///
			/// @param span 储存着数据的内存段。
			/// 	@note 数据中不包括长度字段和描述符类型字段。
			///
			void WriteData(base::ReadOnlySpan const &span)
			{
				if (_span.Size() < span.Size() + 2)
				{
					throw std::invalid_argument{CODE_POS_STR + "本写入器接管的内存段过小，无法写入。"};
				}
			}
		};

	} // namespace usb
} // namespace base
