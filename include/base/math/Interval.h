#pragma once
#include <algorithm>

namespace base
{
	///
	/// @brief 闭区间。[Left, Right].
	///
	/// @note 仅仅储存左右端点这两个数据，不会检查区间是否合法。
	///
	template <typename T>
	class ClosedInterval
	{
	private:
		T _left{};
		T _right{};

	public:
		///
		/// @brief 构造函数。
		///
		/// @note 构造出来的区间左右端点是 T 类型的默认值。
		///
		ClosedInterval() = default;

		///
		/// @brief 构造函数。
		///
		/// @note 如果区间右端点小于区间左端点，则会将 left 作为区间右端点。
		///
		/// @param left 区间左端点。
		/// @param right 区间右端点。
		///
		ClosedInterval(T const &left, T const &right)
		{
			_left = left;
			_right = std::max<T>(left, right);
		}

		///
		/// @brief 区间左端点。
		///
		/// @return T
		///
		T Left() const
		{
			return _left;
		}

		///
		/// @brief 区间右端点。
		///
		/// @return T
		///
		T Right() const
		{
			return _right;
		}
	};

} // namespace base
