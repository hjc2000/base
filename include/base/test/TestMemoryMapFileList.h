#pragma once
#include "base/container/MemoryMapFileList.h"
#include "base/string/String.h"
#include <cstdint>
#include <iostream>
#include <string>

#if HAS_THREAD

namespace base
{
	namespace test
	{
		inline void TestMemoryMapFileList()
		{
			{
				std::cout << std::endl
						  << "测试 Add: "
						  << std::endl;

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

			{
				std::cout << std::endl
						  << "测试 Insert: "
						  << std::endl;

				base::MemoryMapFileList<int> list{"test.map"};
				for (int64_t i = 0; i < 100; i++)
				{
					list.Insert(0, i);
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
		}

	} // namespace test
} // namespace base

#endif // HAS_THREAD
