#include "test_string.h"

#if HAS_THREAD
	#include <base/string/define.h>
	#include <base/string/String.h>
	#include <iostream>

void base::test::Test_String_LastIndexOf()
{
	std::cout << "测试：" + CODE_POS_STR;
	base::String str{"666777"};
	int32_t index = str.LastIndexOf(5, "777");
	std::cout << index << std::endl;
}

void base::test::Test_String_Replace()
{
	std::cout << "测试：" + CODE_POS_STR;
	base::String str = "hellohello1111hello";
	str.Replace("hello", "777");
	std::cout << str << std::endl;
}

void base::test::Test_String_StartWith_EndWith()
{
	std::cout << "测试：" + CODE_POS_STR;
	base::String str = "123456789";

	std::string matches[] = {
		"123",
		"456",
		"789",
		"123456789",
		"0123456789",
		"1234567890",
	};

	for (auto match : matches)
	{
		std::cout << "StartWith " + match + ":" << str.StartWith(match) << std::endl;
	}

	for (auto match : matches)
	{
		std::cout << "EndWith " + match + ":" << str.EndWith(match) << std::endl;
	}
}

#endif
