#pragma once
#include "base/container/MemoryMapFileList.h"
#include "base/string/String.h"
#include <cstdint>
#include <iostream>
#include <string>

namespace base
{
	namespace test
	{
		inline void TestMemoryMapFileList()
		{
			base::MemoryMapFileList<int> list{"test.map"};
			for (int64_t i = 0; i < 100; i++)
			{
				list.Add(i);
			}

			for (int64_t i = 0; i < 100; i++)
			{
				base::String str = std::to_string(list.Get(i));
				str.PadLeft('0', base::StringLength{2});
				std::cout << str << ", ";
				if ((i + 1) % 20 == 0)
				{
					std::cout << std::endl;
				}
			}

			std::cout << std::endl;
		}

	} // namespace test
} // namespace base
