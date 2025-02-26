#include <base/bit/BitConverter.h>
#include <base/container/Array.h>
#include <base/container/Dictionary.h>
#include <base/container/List.h>
#include <base/math/Pow.h>
#include <base/net/IPAddress.h>
#include <base/net/Mac.h>
#include <base/net/profinet/dcp/DcpIdentifyRequestReader.h>
#include <base/sfinae/Equal.h>
#include <base/stream/MemoryStream.h>
#include <base/string/Parse.h>
#include <base/string/String.h>
#include <base/string/ToHexString.h>
#include <base/test/test_parse.h>
#include <base/test/test_string.h>
#include <base/test/test_zoned_time.h>
#include <base/time/TimePointSinceEpoch.h>
#include <base/unit/Hz.h>
#include <cstdint>
#include <iostream>

int main()
{
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
	}

	{
		int8_t a = -2;
		int8_t b = -5;
		uint16_t mul = static_cast<uint16_t>(a) * static_cast<uint16_t>(b);
		int32_t result = static_cast<int16_t>(mul);
		std::cout << result << std::endl;
	}

	// base::test::test_zoned_time();
	// base::test::Test_String_LastIndexOf();
	// base::test::Test_String_Replace();
	// base::test::Test_String_StartWith_EndWith();
	// base::test::test_parse_int32();
	// base::test::test_parse_int64();
	base::test::test_parse_double();
}
