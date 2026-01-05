#pragma once
#include "base/container/Range.h"
#include "base/embedded/usb/descriptor/DescriptorType.h"
#include "base/stream/ReadOnlySpan.h"
#include "base/stream/Span.h"
#include "base/string/define.h"
#include <cstdint>
#include <stdexcept>

namespace base::usb
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
				// 		* 1 字节的长度字段。
				// 		* 1 字节的描述符类型。
				// 内容允许为空。
				throw std::invalid_argument{CODE_POS_STR + "span 过小。"};
			}

			_span = span;
		}

		///
		/// @brief 写入数据长度。
		///
		/// @note 不包括长度字段和描述符类型字段。
		///
		/// @param value
		///
		void WriteDataLength(int64_t value)
		{
			if (value < 0)
			{
				throw std::invalid_argument{CODE_POS_STR + "数据长度不能 < 0."};
			}

			if (value + 2 > 255)
			{
				// 一个描述符整体最多是 255 字节，包括
				// 		* 长度字段
				// 		* 描述符类型字段
				// 		* 数据
				throw std::invalid_argument{CODE_POS_STR + "数据长度过长。"};
			}

			if (value + 2 > _span.Size())
			{
				throw std::invalid_argument{CODE_POS_STR + "本写入器接管的内存段过小，无法容纳这么长的数据。"};
			}

			_span[0] = static_cast<uint8_t>(value) + 2;
		}

		///
		/// @brief 写入描述符类型字段。
		///
		/// @param value
		///
		void WriteDescriptorType(base::usb::DescriptorType value)
		{
			_span[1] = static_cast<uint8_t>(value);
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
				// 算上额外的两个字节，即长度字段和描述符类型字段后，无法写入了。
				throw std::invalid_argument{CODE_POS_STR + "本写入器接管的内存段过小，无法写入。"};
			}

			_span[base::Range{2, span.Size() + 2}].CopyFrom(span);
		}
	};

} // namespace base::usb
