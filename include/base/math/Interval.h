#pragma once

namespace base
{
	/**
	 * @brief 闭区间。[Left, Right]
	 *
	 * @note 仅仅储存左右端点这两个数据，不会检查区间是否合法。
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
