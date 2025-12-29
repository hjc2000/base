#include "Combination.h" // IWYU pragma: keep

#if HAS_THREAD

void base::test::test_combination()
{
	int64_t i = 0;
	base::Combination c{10, 3};
	while (c.MoveToNext())
	{
		i++;
		std::cout << c << std::endl;
	}

	std::cout << "一共有 " << c.Count() << " 种情况。" << std::endl;
	if (i != c.Count())
	{
		throw std::runtime_error{CODE_POS_STR + "列出的组合是错的。"};
	}
}

#endif
