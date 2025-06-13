#pragma once
#include "base/string/define.h"
#include <stdexcept>

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
			if (left > right)
			{
				throw std::invalid_argument{CODE_POS_STR + "区间右端点不能小于左端点。"};
			}

			_left = left;
			_right = right;
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

		///
		/// @brief 检查一个值是否在区间内。
		///
		/// @param value
		/// @return true
		/// @return false
		///
		bool IsInRange(T const &value)
		{
			return value >= _left && value <= _right;
		}

		///
		/// @brief 检查一个值是否在区间外。
		///
		/// @param value
		/// @return true
		/// @return false
		///
		bool IsOutOfRange(T const &value)
		{
			return !IsInRange(value);
		}
	};

} // namespace base
