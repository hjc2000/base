#include "test_parse.h"

#if HAS_THREAD
	#include "base/string/define.h"
	#include <base/string/Parse.h>
	#include <iostream>
	#include <string>

void base::test::test_parse_int32()
{
	std::cout << "测试：" << CODE_POS_STR;

	std::string str{"10"};
	std::cout << "解析 10:\t" << base::ParseInt32(str) << std::endl;

	str = "0x10";
	std::cout << "解析 0x10:\t" << base::ParseInt32(str) << std::endl;

	str = "010";
	std::cout << "解析 010:\t" << base::ParseInt32(str) << std::endl;
}

void base::test::test_parse_int64()
{
	std::cout << "测试：" << CODE_POS_STR;

	std::string str{"10"};
	std::cout << "解析 10:\t" << base::ParseInt64(str) << std::endl;

	str = "0x10";
	std::cout << "解析 0x10:\t" << base::ParseInt64(str) << std::endl;

	str = "010";
	std::cout << "解析 010:\t" << base::ParseInt64(str) << std::endl;
}

void base::test::test_parse_double()
{
	std::cout << "测试：" << CODE_POS_STR;

	std::string str{"10"};
	std::cout << "解析 10:\t" << base::ParseDouble(str) << std::endl;

	str = "0x10";
	std::cout << "解析 0x10:\t" << base::ParseDouble(str) << std::endl;

	str = "010";
	std::cout << "解析 010:\t" << base::ParseDouble(str) << std::endl;

	str = "10.5";
	std::cout << "解析 16 进制 10.5:\t" << base::ParseDouble(str, 16) << std::endl;
	std::cout << "解析 8 进制 10.5:\t" << base::ParseDouble(str, 8) << std::endl;
}

#endif
