#include "TestListBinarySearch.h" // IWYU pragma: keep
#include "base/container/List.h"
#include "base/string/define.h"
#include <cstdint>
#include <functional>
#include <iostream>
#include <stdexcept>

#if HAS_THREAD

void base::test::TestListBinarySearch()
{
	{
		base::List<int> list{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
		int64_t index = 0;

		index = list.AscendingOrderBinarySearch(5);
		if (index != 5)
		{
			throw std::runtime_error{CODE_POS_STR + "测试不通过。"};
		}

		index = list.AscendingOrderBinarySearch(0);
		if (index != 0)
		{
			throw std::runtime_error{CODE_POS_STR + "测试不通过。"};
		}

		index = list.AscendingOrderBinarySearch(9);
		if (index != 9)
		{
			throw std::runtime_error{CODE_POS_STR + "测试不通过。"};
		}
	}

	{
		base::List<int> list{9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
		int64_t index = 0;

		index = list.DescendingOrderBinarySearch(5);
		if (index != 4)
		{
			throw std::runtime_error{CODE_POS_STR + "测试不通过。"};
		}

		index = list.DescendingOrderBinarySearch(0);
		if (index != 9)
		{
			throw std::runtime_error{CODE_POS_STR + "测试不通过。"};
		}

		index = list.DescendingOrderBinarySearch(9);
		if (index != 0)
		{
			throw std::runtime_error{CODE_POS_STR + "测试不通过。"};
		}
	}

	{
		base::List<int> list{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

		std::function<int(int const &left, int const &right)> compare = [](int const &left, int const &right) -> int64_t
		{
			return left - right;
		};

		int64_t index = 0;

		index = list.AscendingOrderBinarySearch(5, compare);
		if (index != 5)
		{
			throw std::runtime_error{CODE_POS_STR + "测试不通过。"};
		}

		index = list.AscendingOrderBinarySearch(0, compare);
		if (index != 0)
		{
			throw std::runtime_error{CODE_POS_STR + "测试不通过。"};
		}

		index = list.AscendingOrderBinarySearch(9, compare);
		if (index != 9)
		{
			throw std::runtime_error{CODE_POS_STR + "测试不通过。"};
		}
	}

	{
		base::List<int> list{0, 1, 2, 3, 6, 7, 8, 9, 10, 11, 12};

		std::function<int(int const &left, int const &right)> compare = [](int const &left, int const &right) -> int64_t
		{
			return left - right;
		};

		int64_t index = 0;

		index = list.AscendingOrderBinarySearchAround(5, compare);
		if (index != 4)
		{
			// 最接近 5 的是索引 4 处的 6.
			throw std::runtime_error{CODE_POS_STR + "测试不通过。"};
		}

		index = list.AscendingOrderBinarySearchAround(12, compare);
		if (index != 10)
		{
			throw std::runtime_error{CODE_POS_STR + "测试不通过。"};
		}
	}

	{
		base::List<int> list{12, 11, 10, 9, 8, 7, 6, 3, 2, 1, 0};

		std::function<int(int const &left, int const &right)> compare = [](int const &left, int const &right) -> int64_t
		{
			return left - right;
		};

		int64_t index = 0;

		index = list.DescendingOrderBinarySearchAround(5, compare);
		if (index != 6)
		{
			// 最接近 5 的是索引 6 处的 6.
			throw std::runtime_error{CODE_POS_STR + "测试不通过。"};
		}

		index = list.DescendingOrderBinarySearchAround(12, compare);
		if (index != 0)
		{
			throw std::runtime_error{CODE_POS_STR + "测试不通过。"};
		}

		index = list.DescendingOrderBinarySearchAround(0, compare);
		if (index != 10)
		{
			throw std::runtime_error{CODE_POS_STR + "测试不通过。"};
		}
	}

	std::cout << CODE_POS_STR << " 所有测试都通过。" << std::endl;
}

#endif // HAS_THREAD
