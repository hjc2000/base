#pragma once
#include "base/stream/Span.h"
#include "base/string/define.h"
#include "DescriptorWriter.h"
#include <stdexcept>
#include <string>

namespace base
{
	namespace usb
	{
		class StringDescriptorWriter
		{
		private:
			base::usb::DescriptorWriter _writer;

		public:
			StringDescriptorWriter() = default;

			///
			/// @brief 构造函数
			///
			/// @param span 接受一段内存，后续写入数据将在此段内存中写入。
			///
			StringDescriptorWriter(base::Span const &span)
			{
				_writer = base::usb::DescriptorWriter{span};
			}

			///
			/// @brief 写入字符串数据。
			///
			/// @param unicode_string
			///
			void WriteData(std::string const &unicode_string)
			{
				if (unicode_string.size() % 2 != 0)
				{
					// 字符编码必须是 UTF16-LE。
					// 字符串长度为奇数说明肯定不是 UTF16-LE 编码的。
					throw std::invalid_argument{CODE_POS_STR + "必须是 UTF16-LE 编码的字符串。"};
				}

				_writer.WriteDataLength(unicode_string.size());
				_writer.WriteDescriptorType(base::usb::DescriptorType::String);

				base::ReadOnlySpan str_span{
					reinterpret_cast<uint8_t const *>(unicode_string.data()),
					unicode_string.size(),
				};

				_writer.WriteData(str_span);
			}
		};

	} // namespace usb
} // namespace base
