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
#include <base/time/TimePointSinceEpoch.h>
#include <base/unit/Hz.h>
#include <format>
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
		std::cout << base::Hz{100} << std::endl;
	}

	{
		base::String str1 = "hellohello1111hello";
		base::String str2 = "xiaoming";
		std::cout << str1.IndexOf(str2) << std::endl;

		str1.Replace("hello", "777");
		std::cout << str1 << std::endl;
	}

	{
		base::TimePointSinceEpoch now{std::chrono::system_clock::now()};
		std::cout << now.NanosecondsZonedTimeString() << std::endl;
		std::cout << now.MicrosecondsZonedTimeString() << std::endl;
		std::cout << now.MillisecondsZonedTimeString() << std::endl;
		std::cout << now.SecondsZonedTimeString() << std::endl;
	}
}
