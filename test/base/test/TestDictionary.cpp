#include "TestDictionary.h" // IWYU pragma: keep
#include "base/container/Dictionary.h"
#include "base/string/define.h"
#include <iostream>
#include <string>

void base::test::TestDictionary()
{
	std::cout << CODE_POS_STR;

	base::Dictionary<int, std::string> dic;
	for (int i = 0; i < 10; i++)
	{
		dic.Add(i, std::to_string(i));
	}

	for (auto &it : dic)
	{
		std::cout << "key = " << it.first
				  << " , "
				  << "value = " << it.second
				  << std::endl;
	}
}
