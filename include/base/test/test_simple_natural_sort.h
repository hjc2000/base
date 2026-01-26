#pragma once
#include "base/container/List.h"
#include <iostream>
#include <string>

namespace base::test
{
	inline void test_simple_natural_sort()
	{
		base::List<std::string> list{};

		list.Add("11.mp4");
		list.Add("1.mp4");
		list.Add("12.mp4");
		list.Add("2.mp4");
		list.Add("5.mp4");
		list.Add("3.mp4");
		list.Add("4.mp4");
		list.Add("10.mp4");

		base::simple_natural_sort(list);

		for (std::string const &item : list)
		{
			std::cout << item << std::endl;
		}
	}

} // namespace base::test
