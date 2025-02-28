#pragma once
#include <algorithm>

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
		{
			_left = left;
			_right = std::max<T>(left, right);
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
