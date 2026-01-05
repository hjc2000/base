#pragma once

namespace base
{
	///
	/// @brief 左边开，右边正无穷的区间。 (Left, +inf).
	///
	template <typename T>
	class LeftOpenRightInfiniteInterval
	{
	private:
		T _left{};

	public:
		///
		/// @brief 构造函数。
		///
		/// @note 构造出来的区间左右端点是 T 类型的默认值。
		///
		constexpr LeftOpenRightInfiniteInterval() = default;

		///
		/// @brief 构造函数。
		///
		/// @param left 区间右端点。
		///
		constexpr LeftOpenRightInfiniteInterval(T const &left)
		{
			_left = left;
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
		/// @brief 检查一个值是否在区间内。
		///
		/// @param value
		/// @return
		///
		constexpr bool IsInRange(T const &value) const
		{
			return value > _left;
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
