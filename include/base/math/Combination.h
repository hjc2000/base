#pragma once
#include <base/string/ICanToString.h>
#include <string>
#include <vector>

namespace base
{
	/**
	 * @brief 组合。
	 *
	 */
	class Combination :
		public base::ICanToString
	{
	private:
		int _n = 0;
		int _m = 0;
		bool _move_to_next_for_the_first_time = true;
		std::vector<int> _current_combination;

	public:
		Combination(int n, int m);

	public:
		std::vector<int> const &Current() const;

		bool MoveToNext();

		/**
		 * @brief 转化为字符串
		 *
		 * @return std::string
		 */
		virtual std::string ToString() const override;
	};
} // namespace base
