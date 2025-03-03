#pragma once
#include <vector>

namespace base
{
	/**
	 * @brief 组合。
	 *
	 */
	class Combination
	{
	private:
		int _n = 0;
		int _m = 0;
		std::vector<int> _current_combination;

	public:
		Combination(int n, int m);

	public:
		std::vector<int> const &Current() const;

		void ToNext()
		{
		}

		Combination &operator++(int);

		Combination &operator++();
	};
} // namespace base
