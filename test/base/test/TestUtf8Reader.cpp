#include "TestUtf8Reader.h" // IWYU pragma: keep
#include "base/container/ArraySpan.h"
#include "base/stream/MemoryStream.h"
#include "base/stream/Span.h"
#include "base/string/define.h"
#include "base/string/encoding/Utf8Reader.h"
#include <cstdint>
#include <iostream>
#include <string>

void base::test::TestUtf8Reader()
{
	std::cout << CODE_POS_STR;

	constexpr char32_t utf32_str[6] = {U'你', U'好', U'，', U'世', U'界', U'！'};
	std::string utf8_str = "你好，世界！";

	base::Span span{
		reinterpret_cast<uint8_t *>(utf8_str.data()),
		static_cast<int64_t>(utf8_str.size()),
	};

	base::MemoryStream stream{span};
	stream.SetLength(span.Size());
	base::string::encoding::Utf8Reader reader{stream};

	char32_t buffer[6]{};
	base::ArraySpan<char32_t> out_span{buffer, sizeof(buffer) / sizeof(char32_t)};

	int64_t have_read = reader.Read(out_span);
	std::cout << "have read: " << have_read << std::endl;

	for (int i = 0; i < out_span.Count(); i++)
	{
		std::cout << static_cast<uint32_t>(out_span[i]) << std::endl;
		if (out_span[i] != utf32_str[i])
		{
			std::cout << "在 i = " << i << " 位置出错" << std::endl;
		}
	}
}
