#include "include/base/math/Combination.h"
#include "include/base/stream/StreamWriter.h"
#include <base/bit/BitConverter.h>
#include <base/container/Array.h>
#include <base/container/Dictionary.h>
#include <base/container/List.h>
#include <base/math/Combination.h>
#include <base/math/IRandomGenerator.h>
#include <base/math/Pow.h>
#include <base/net/IPAddress.h>
#include <base/net/Mac.h>
#include <base/net/profinet/dcp/DcpIdentifyRequestReader.h>
#include <base/sfinae/Equal.h>
#include <base/stream/IFileStream.h>
#include <base/stream/MemoryStream.h>
#include <base/stream/StreamWriter.h>
#include <base/string/Parse.h>
#include <base/string/String.h>
#include <base/string/ToHexString.h>
#include <base/test/test_parse.h>
#include <base/test/test_string.h>
#include <base/test/test_zoned_time.h>
#include <base/time/TimePointSinceEpoch.h>
#include <base/unit/Hz.h>
#include <format>
#include <iostream>
#include <string>

int main()
{
	// {
	// 	uint8_t const buffer[] = {0x1, 0xe, 0xcf, 0x0, 0x0, 0x0, 0xb0, 0x25,
	// 							  0xaa, 0x39, 0xe9, 0x1c, 0x88, 0x92, 0xfe,
	// 							  0xfe, 0x5, 0x0, 0x0, 0x0, 0x1, 0x17, 0x0,
	// 							  0x1, 0x0, 0x10, 0x2, 0x2, 0x0, 0xb, 0x72,
	// 							  0x74, 0x2d, 0x6c, 0x61, 0x62, 0x73, 0x2d,
	// 							  0x64, 0x65, 0x76, 0x0, 0x0, 0x0, 0x0, 0x0,
	// 							  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	// 							  0x0, 0x0, 0x0, 0x0, 0x0};

	// 	base::profinet::DcpIdentifyRequestReader reader{base::ReadOnlySpan{buffer, sizeof(buffer)}};
	// 	std::cout << reader << std::endl;
	// }

	// {
	// 	int8_t a = -2;
	// 	int8_t b = -5;
	// 	uint16_t mul = static_cast<uint16_t>(a) * static_cast<uint16_t>(b);
	// 	int32_t result = static_cast<int16_t>(mul);
	// 	std::cout << result << std::endl;
	// }

	// base::test::test_zoned_time();
	// base::test::Test_String_LastIndexOf();
	// base::test::Test_String_Replace();
	// base::test::Test_String_StartWith_EndWith();
	// base::test::test_parse_int32();
	// base::test::test_parse_int64();
	// base::test::test_parse_double();

	{
		// std::shared_ptr<base::IFileStream> fs = base::di::file::CreateNewAnyway("math.txt");
		// base::StreamWriter writer{fs};
		// std::shared_ptr<base::IRandomGenerator> random_generator = base::di::CreateRandomGenerator();
		// int count = 0;
		// while (count <= 100)
		// {
		// 	int left = random_generator->GenerateUInt8Random(2, 20);
		// 	int right = random_generator->GenerateUInt8Random(2, 20);
		// 	int op = random_generator->GenerateUInt8Random(0, 1);
		// 	char op_char = '+';
		// 	if (op)
		// 	{
		// 		op_char = '-';
		// 	}

		// 	int sum = 0;
		// 	if (op == 0)
		// 	{
		// 		sum = left + right;
		// 	}
		// 	else
		// 	{
		// 		sum = left - right;
		// 	}

		// 	if (left == right && op == 1)
		// 	{
		// 		continue;
		// 	}

		// 	if (sum < 0 || sum > 99)
		// 	{
		// 		continue;
		// 	}

		// 	std::string equ = std::format("{} {} {} =",
		// 								  left, op_char, right);

		// 	while (equ.size() < 35)
		// 	{
		// 		equ += ' ';
		// 	}

		// 	equ += std::to_string(sum);
		// 	std::cout << equ << std::endl;
		// 	writer.WriteLine(equ);
		// 	writer.WriteLine();
		// 	count++;
		// }
	}

	{
		int i = 0;

		/* C(10,3)
		 * = 10! / ((10-3)! * 3!)
		 * = 10! / (7! * 3!)
		 * = (10 * 9 * 8) / 3!
		 * = 10 * 9 * 8 / 6
		 * = 10 * 3 * 8 / 2
		 * = 10 * 3 * 4
		 */
		base::Combination c{10, 3};
		while (c.MoveToNext())
		{
			i++;
			std::cout << c << std::endl;
		}

		std::cout << "一共有 " << i << " 种情况。" << std::endl;
	}
}
