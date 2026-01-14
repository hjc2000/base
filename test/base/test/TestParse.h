#pragma once
#include "base/string/define.h"
#include "base/string/Parse.h"
#include <cstdint>
#include <iostream>

namespace base::test
{
	inline void TestParseInt32()
	{
		std::cout << "测试：" << CODE_POS_STR;

		std::string str{"10"};
		std::cout << "解析 10:\t" << base::Parse<int32_t>(str) << std::endl;

		str = "0x10";
		std::cout << "解析 0x10:\t" << base::Parse<int32_t>(str) << std::endl;

		str = "010";
		std::cout << "解析 010:\t" << base::Parse<int32_t>(str) << std::endl;
	}

	inline void TestParseInt64()
	{
		std::cout << "测试：" << CODE_POS_STR;

		std::string str{"-10"};
		std::cout << "解析 -10:\t" << base::Parse<int64_t>(str) << std::endl;

		str = "-0x10";
		std::cout << "解析 -0x10:\t" << base::Parse<int64_t>(str) << std::endl;

		str = "-010";
		std::cout << "解析 -010:\t" << base::Parse<int64_t>(str) << std::endl;
	}

	inline void TestParseDouble()
	{
		std::cout << "测试：" << CODE_POS_STR;

		std::string str{"10"};
		std::cout << "解析 10:\t" << base::Parse<double>(str) << std::endl;

		str = "0x10";
		std::cout << "解析 0x10:\t" << base::Parse<double>(str) << std::endl;

		str = "010";
		std::cout << "解析 010:\t" << base::Parse<double>(str) << std::endl;

		str = "-0x10.5";
		std::cout << "解析 -0x10.5:\t" << base::Parse<double>(str) << std::endl;

		str = "10.5";
		std::cout << "解析 16 进制 10.5:\t" << base::Parse<double>(str, 16) << std::endl;
		std::cout << "解析 8 进制 10.5:\t" << base::Parse<double>(str, 8) << std::endl;
	}

} // namespace base::test
