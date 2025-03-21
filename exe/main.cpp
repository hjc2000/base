#include "base/file/filesystem.h"
#include "base/file/Path.h"
#include "base/math/BigInteger.h"
#include "base/net/IPAddress.h"
#include "base/net/profinet/dcp/DcpIdentifyRequestReader.h"
#include "base/string/Parse.h"
#include "base/time/DateTime.h"
#include "base/time/time.h"
#include "base/time/TimePointSinceEpoch.h"
#include "base/usage/CountTriangle.h"
#include "base/usage/GenerateCalculationQuestions.h"
#include <chrono>
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

	base::usage::CountTriangle();
	base::TestIpAddress();
	base::test::TestBigInteger();
	base::test::test_parse_int32();
	base::test::test_parse_int64();
	base::test::test_parse_double();
	base::usage::GenerateCalculationQuestions();

	{
		// base::filesystem::create_directory("./test_dir");
		// base::filesystem::copy("./test_dir", "./test_dir1");

		// base::Path src_path{"C:/Users/huang/dev/.temp/src"};
		// base::Path dst_path{"C:/Users/huang/dev/.temp/dst"};

		// base::filesystem::Copy(src_path,
		// 					   dst_path,
		// 					   base::filesystem::OverwriteOption::Overwrite);
	}

	{
		auto now = base::time::Now();
		std::cout << static_cast<std::chrono::year_month_day>(now) << std::endl;
	}

	{
		base::TimePointSinceEpoch now_time_point = base::time::Now();

		base::DateTime now{
			base::UtcHourOffset{8},
			now_time_point,
		};

		std::cout << now << std::endl;
		std::cout << now_time_point << std::endl;
		std::cout << static_cast<std::chrono::nanoseconds>(now_time_point) << std::endl;
		std::cout << static_cast<std::chrono::nanoseconds>(static_cast<base::TimePointSinceEpoch>(now)) << std::endl;
	}
}
