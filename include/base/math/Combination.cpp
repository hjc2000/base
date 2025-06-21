#include "Combination.h"
#include "base/math/BigInteger.h"
#include "base/math/Factorial.h"
#include "base/string/define.h"
#include <cstdint>
#include <stdexcept>

base::Combination::Combination(int n, int m)
	: _n(n),
	  _m(m)
{
	if (_m > _n)
	{
		throw std::invalid_argument{CODE_POS_STR + "m 不能比 n 大。"};
	}

	for (int i = 0; i < _m; i++)
	{
		_current_combination.push_back(i);
	}
}

std::vector<int> const &base::Combination::Current() const
{
	return _current_combination;
}

int base::Combination::operator[](int index) const
{
	if (index < 0 || index >= _m)
	{
		throw std::out_of_range{CODE_POS_STR + "索引溢出。"};
	}

	return _current_combination[index];
}

bool base::Combination::MoveToNext()
{
	if (_m == 0)
	{
		return false;
	}

	if (_move_to_next_for_the_first_time)
	{
		_move_to_next_for_the_first_time = false;
		return true;
	}

	if (_current_combination[0] >= _n - _m)
	{
		return false;
	}

	bool last_loop_has_broken = false;
	for (int i = 0; i < _m; i++)
	{
		int current_index = _m - 1 - i;
		_current_combination[current_index]++;
		if (_current_combination[current_index] > _n - 1 - i)
		{
			last_loop_has_broken = true;
			continue;
		}

		if (last_loop_has_broken)
		{
			last_loop_has_broken = false;
			for (int j = current_index; j + 1 < static_cast<int>(_current_combination.size()); j++)
			{
				_current_combination[j + 1] = _current_combination[j] + 1;
			}
		}

		return true;
	}

	return true;
}

int64_t base::Combination::Count() const
{
	base::BigInteger result = base::Factorial(_n) /
							  base::Factorial(_n - _m) /
							  base::Factorial(_m);

	return static_cast<int64_t>(result);
}

std::string base::Combination::ToString() const
{
	std::string result;
	int count = static_cast<int>(_current_combination.size());
	for (int i = 0; i < count; i++)
	{
		result += std::to_string(_current_combination[i]);
		if (i < count - 1)
		{
			result += ", ";
		}
	}

	return result;
}

#if HAS_THREAD

void base::test::test_combination()
{
	int i = 0;
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
