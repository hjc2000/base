#include "Combination.h"

base::Combination::Combination(int n, int m)
	: _n(n),
	  _m(m)
{
}

std::vector<int> const &base::Combination::Current() const
{
	return _current_combination;
}

base::Combination &base::Combination::operator++(int)
{
	ToNext();
	return *this;
}

base::Combination &base::Combination::operator++()
{
	ToNext();
	return *this;
}
