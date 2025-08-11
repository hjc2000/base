#pragma once
#include "base/container/MemoryMapFileList.h"
#include <cstdint>
#include <iostream>

namespace base
{
	namespace test
	{
		inline void TestMemoryMapFileList()
		{
			base::MemoryMapFileList<int> list{"test.map"};
			// for (int64_t i = 0; i < 100; i++)
			// {
			// 	list.Add(i);
			// }

			// for (int64_t i = 0; i < 100; i++)
			// {
			// 	std::cout << list.Get(i) << std::endl;
			// }
		}

	} // namespace test
} // namespace base
