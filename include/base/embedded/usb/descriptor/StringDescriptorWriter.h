#pragma once
#include "base/stream/ReadOnlySpan.h"
#include "base/stream/Span.h"
#include "base/string/define.h"
#include "DescriptorWriter.h"
#include <cstddef>
#include <cstdint>
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
			/// @param span 容纳着 UTF16-LE 编码的字符串的内存段。
			///
			void WriteData(base::ReadOnlySpan const &span)
			{
				if (span.Size() % 2 != 0)
				{
					// 字符编码必须是 UTF16-LE。
					// 字符串长度为奇数说明肯定不是 UTF16-LE 编码的。
					throw std::invalid_argument{CODE_POS_STR + "必须是 UTF16-LE 编码的字符串。"};
				}

				if (reinterpret_cast<size_t>(span.Buffer()) % 2 != 0)
				{
					throw std::invalid_argument{CODE_POS_STR + "内存段必须 2 字节对齐。"};
				}

				_writer.WriteDataLength(span.Size());
				_writer.WriteDescriptorType(base::usb::DescriptorType::String);
				_writer.WriteData(span);
			}

			///
			/// @brief 写入数据。
			///
			/// @param str
			///
			void WriteData(std::u16string const &str)
			{
				base::ReadOnlySpan span{
					reinterpret_cast<uint8_t const *>(str.data()),
					static_cast<int64_t>(str.size() * sizeof(char16_t)),
				};

				_writer.WriteDataLength(span.Size());
				_writer.WriteDescriptorType(base::usb::DescriptorType::String);
				_writer.WriteData(span);
			}
		};

	} // namespace usb
} // namespace base
