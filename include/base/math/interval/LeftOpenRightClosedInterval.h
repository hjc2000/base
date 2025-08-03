#pragma once
#include "base/string/define.h"
#include <stdexcept>

namespace base
{
	///
	/// @brief 左开右区间。(Left, Right].
	///
	template <typename T>
	class LeftOpenRightClosedInterval
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
		constexpr LeftOpenRightClosedInterval() = default;

		///
		/// @brief 构造函数。
		///
		/// @param left 区间左端点。
		/// @param right 区间右端点。
		///
		constexpr LeftOpenRightClosedInterval(T const &left, T const &right)
		{
			if (right < left)
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
		constexpr T const &Left() const
		{
			return _left;
		}

		///
		/// @brief 区间右端点。
		///
		/// @return T
		///
		constexpr T const &Right() const
		{
			return _right;
		}

		///
		/// @brief 检查一个值是否在区间内。
		///
		/// @param value
		/// @return
		///
		constexpr bool IsInRange(T const &value) const
		{
			return value > _left && value <= _right;
		}

		///
		/// @brief 检查一个值是否在区间外。
		///
		/// @param value
		/// @return
		///
		constexpr bool IsOutOfRange(T const &value) const
		{
			return !IsInRange(value);
		}
	};

} // namespace base
