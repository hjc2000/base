#pragma once

#include "base/string/define.h"
#include <stdexcept>

namespace base
{
	/**
	 * @brief 闭区间。[Left, Right]
	 *
	 * @tparam T
	 */
	template <typename T>
	class ClosedInterval
	{
	private:
		T _left{};
		T _right{};

	public:
		ClosedInterval() = default;

		ClosedInterval(T const &left, T const &right)
			: _left(left),
			  _right(right)
		{
			if (_right < _left)
			{
				throw std::invalid_argument{CODE_POS_STR + "区间右端点不能小于区间左端点。"};
			}
		}

	public:
		/**
		 * @brief 区间左端点。
		 *
		 * @return T
		 */
		T Left() const
		{
			return _left;
		}

		/**
		 * @brief 区间右端点。
		 *
		 * @return T
		 */
		T Right() const
		{
			return _right;
		}
	};

} // namespace base
