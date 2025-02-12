#include <array>
#include <base/bit/BitConverter.h>
#include <base/container/Array.h>
#include <base/container/Dictionary.h>
#include <base/container/List.h>
#include <base/net/IPAddress.h>
#include <base/net/Mac.h>
#include <base/net/profinet/dcp/DcpIdentifyRequestReader.h>
#include <base/sfinae/Equal.h>
#include <base/stream/MemoryStream.h>
#include <base/string/String.h>
#include <base/string/ToHexString.h>
#include <base/unit/Hz.h>
#include <format>
#include <iostream>

int main()
{
	uint8_t const buffer[] = {0x1, 0xe, 0xcf, 0x0, 0x0, 0x0, 0xb0, 0x25,
							  0xaa, 0x39, 0xe9, 0x1c, 0x88, 0x92, 0xfe,
							  0xfe, 0x5, 0x0, 0x0, 0x0, 0x1, 0x17, 0x0,
							  0x1, 0x0, 0x10, 0x2, 0x2, 0x0, 0xb, 0x72,
							  0x74, 0x2d, 0x6c, 0x61, 0x62, 0x73, 0x2d,
							  0x64, 0x65, 0x76, 0x0, 0x0, 0x0, 0x0, 0x0,
							  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
							  0x0, 0x0, 0x0, 0x0, 0x0};

	base::profinet::DcpIdentifyRequestReader reader{base::ReadOnlySpan{buffer, sizeof(buffer)}};
	std::cout << reader << std::endl;

	int8_t a = -2;
	int8_t b = -5;
	uint16_t mul = static_cast<uint16_t>(a) * static_cast<uint16_t>(b);
	int32_t result = static_cast<int16_t>(mul);
	std::cout << result << std::endl;
	std::cout << base::Hz{100} << std::endl;

	{
		base::Array<uint8_t, 16> arr1{1, 1, 1, 1, 1, 2, 3, 4, 5};
		base::Array<uint8_t, 3> arr2{1, 2, 3};
		base::Span span1{arr1.AsArraySpan()};
		base::Span span2{arr2.AsArraySpan()};
		std::cout << base::ToHexString(arr1.AsReadOnlyArraySpan()) << std::endl;
		std::cout << (span1 == span2) << std::endl;
		std::cout << (span1.IndexOf(span2)) << std::endl;
	}
}
