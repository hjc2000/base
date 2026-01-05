#pragma once

namespace base
{
	///
	/// @brief 左边负无穷，右边闭的区间。 (-inf, Right].
	///
	template <typename T>
	class LeftInfiniteRightClosedInterval
	{
	private:
		T _right{};

	public:
		///
		/// @brief 构造函数。
		///
		/// @note 构造出来的区间左右端点是 T 类型的默认值。
		///
		constexpr LeftInfiniteRightClosedInterval() = default;

		///
		/// @brief 构造函数。
		///
		/// @param right 区间右端点。
		///
		constexpr LeftInfiniteRightClosedInterval(T const &right)
		{
			_right = right;
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
			return value <= _right;
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
