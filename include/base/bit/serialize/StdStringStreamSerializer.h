#pragma once
#include "base/bit/AutoBitConverter.h"
#include "base/bit/serialize/IStreamSerializable.h"
#include "base/stream/ReadOnlySpan.h"
#include "base/stream/Span.h"
#include "base/string/define.h"
#include <string>

namespace base
{
	class StdStringStreamSerializer :
		public base::IStreamSerializable
	{
	private:
		std::string *_string{};

	public:
		StdStringStreamSerializer() = default;

		StdStringStreamSerializer(std::string &string)
		{
			_string = &string;
		}

		///
		/// @brief 将对象序列化写入流中。
		///
		/// @param stream
		///
		virtual void SerializeIntoStream(base::Stream &stream) const override
		{
			if (_string == nullptr)
			{
				throw std::runtime_error{CODE_POS_STR + "未正确初始化。"};
			}

			int64_t size = _string->size();

			// 先序列化 8 个字节的 int64_t 进去，这样反序列化的时候就知道有多大了。
			base::little_endian_remote_converter.GetBytes(size, stream);

			base::ReadOnlySpan span{
				reinterpret_cast<uint8_t const *>(_string->data()),
				size,
			};

			stream.Write(span);
		}

		///
		/// @brief 从流中反序列化得到对象。
		///
		/// @note 对象要先无参默认构造，然后再调用此方法进行反序列化，重新初始化对象的各个字段。
		///
		/// @param stream
		///
		virtual void DeserializeFromStream(base::Stream &stream) override
		{
			if (_string == nullptr)
			{
				throw std::runtime_error{CODE_POS_STR + "未正确初始化。"};
			}

			int64_t size = base::little_endian_remote_converter.FromBytes<int64_t>(stream);
			_string->clear();
			_string->reserve(size);

			uint8_t temp_buffer[128];
			base::Span temp_buffer_span{temp_buffer, sizeof(temp_buffer)};

			while (true)
			{
				if (static_cast<int64_t>(_string->size()) >= size)
				{
					return;
				}

				int64_t have_read = stream.Read(temp_buffer_span);
				if (have_read <= 0)
				{
					throw base::StreamDeserializeException{CODE_POS_STR + "还没反序列化完成流就结束了。"};
				}

				_string->append(reinterpret_cast<char const *>(temp_buffer), have_read);
			}
		}
	};

} // namespace base
