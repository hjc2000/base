#include "base/envirenment.h"
#include "base/file/filesystem.h"
#include "base/math/BigInteger.h"
#include "base/net/IPAddress.h"
#include "base/net/profinet/dcp/DcpIdentifyRequestReader.h"
#include "base/string/Parse.h"
#include "base/time/DateTime.h"
#include "base/usage/CountTriangle.h"
#include "base/usage/GenerateCalculationQuestions.h"
#include <cstdlib>
#include <iostream>
#include <stdlib.h>

extern char **environ;

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

	base::test::TestDateTime();
	// base::test::TestDirectoryEntryEnumerable();
	// base::test::TestRecursiveDirectoryEntryEnumerable();

	{
		// base::Path src_path{"C:/Users/huang/dev/.temp/src"};
		// base::Path dst_path{"C:/Users/huang/dev/.temp/dst"};

		// base::filesystem::Copy(src_path,
		// 					   dst_path,
		// 					   base::filesystem::OverwriteOption::Overwrite);
	}

	auto dic = base::GetEnvirenmentVariableDictionary();
	std::cout << dic.Get("Path") << std::endl;
}
