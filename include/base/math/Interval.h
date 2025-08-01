#pragma once
#include "base/string/define.h"
#include <stdexcept>

namespace base
{
	///
	/// @brief 闭区间。[Left, Right].
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
		constexpr ClosedInterval() = default;

		///
		/// @brief 构造函数。
		///
		/// @param left 区间左端点。
		/// @param right 区间右端点。
		///
		constexpr ClosedInterval(T const &left, T const &right)
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
		constexpr T Left() const
		{
			return _left;
		}

		///
		/// @brief 区间右端点。
		///
		/// @return T
		///
		constexpr T Right() const
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
			return value >= _left && value <= _right;
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

	///
	/// @brief 开区间。(Left, Right).
	///
	template <typename T>
	class OpenInterval
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
		constexpr OpenInterval() = default;

		///
		/// @brief 构造函数。
		///
		/// @param left 区间左端点。
		/// @param right 区间右端点。
		///
		constexpr OpenInterval(T const &left, T const &right)
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
		constexpr T Left() const
		{
			return _left;
		}

		///
		/// @brief 区间右端点。
		///
		/// @return T
		///
		constexpr T Right() const
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
			return value > _left && value < _right;
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
		constexpr T Left() const
		{
			return _left;
		}

		///
		/// @brief 区间右端点。
		///
		/// @return T
		///
		constexpr T Right() const
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

	///
	/// @brief 左闭右开区间。[Left, Right).
	///
	template <typename T>
	class LeftClosedRightOpenInterval
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
		constexpr LeftClosedRightOpenInterval() = default;

		///
		/// @brief 构造函数。
		///
		/// @param left 区间左端点。
		/// @param right 区间右端点。
		///
		constexpr LeftClosedRightOpenInterval(T const &left, T const &right)
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
		constexpr T Left() const
		{
			return _left;
		}

		///
		/// @brief 区间右端点。
		///
		/// @return T
		///
		constexpr T Right() const
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
			return value >= _left && value < _right;
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

	///
	/// @brief 左边负无穷，右边开的区间。 (-inf, Right).
	///
	template <typename T>
	class LeftInfiniteRightOpenInterval
	{
	private:
		T _right{};

	public:
		///
		/// @brief 构造函数。
		///
		/// @note 构造出来的区间左右端点是 T 类型的默认值。
		///
		constexpr LeftInfiniteRightOpenInterval() = default;

		///
		/// @brief 构造函数。
		///
		/// @param right 区间右端点。
		///
		constexpr LeftInfiniteRightOpenInterval(T const &right)
		{
			_right = right;
		}

		///
		/// @brief 区间右端点。
		///
		/// @return T
		///
		constexpr T Right() const
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
			return value < _right;
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
		constexpr T Right() const
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
		constexpr T Left() const
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

	///
	/// @brief 左边开，右边正无穷的区间。 (Left, +inf).
	///
	template <typename T>
	class LeftClosedRightInfiniteInterval
	{
	private:
		T _left{};

	public:
		///
		/// @brief 构造函数。
		///
		/// @note 构造出来的区间左右端点是 T 类型的默认值。
		///
		constexpr LeftClosedRightInfiniteInterval() = default;

		///
		/// @brief 构造函数。
		///
		/// @param left 区间右端点。
		///
		constexpr LeftClosedRightInfiniteInterval(T const &left)
		{
			_left = left;
		}

		///
		/// @brief 区间左端点。
		///
		/// @return T
		///
		constexpr T Left() const
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
			return value >= _left;
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

	enum class IntervalType
	{
		///
		/// @brief 闭区间。
		///
		///
		Closed,

		///
		/// @brief 开区间。
		///
		///
		Open,

		///
		/// @brief 左开右闭区间。
		///
		///
		LeftOpenRightClosed,

		///
		/// @brief 左闭右开区间。
		///
		///
		LeftClosedRightOpen,

		///
		/// @brief 左边负无穷，右边开的区间。
		///
		///
		LeftInfiniteRightOpen,

		///
		/// @brief 左边负无穷，右边闭的区间。
		///
		///
		LeftInfiniteRightClosed,

		///
		/// @brief 左边开，右边正无穷的区间。
		///
		///
		LeftOpenRightInfinite,

		///
		/// @brief 左边闭，右边正无穷的区间。
		///
		///
		LeftClosedRightInfinite
	};

	///
	/// @brief 通用集合。
	///
	///
	template <typename T>
	class Interval
	{
	private:
		base::IntervalType _type{};
		T _left{};
		T _right{};

	public:
		constexpr Interval() = default;

		constexpr Interval(base::ClosedInterval<T> const &interval)
		{
			_type = base::IntervalType::Closed;
			_left = interval.Left();
			_right = interval.Right();
		}

		constexpr Interval(base::OpenInterval<T> const &interval)
		{
			_type = base::IntervalType::Open;
			_left = interval.Left();
			_right = interval.Right();
		}

		constexpr Interval(base::LeftOpenRightClosedInterval<T> const &interval)
		{
			_type = base::IntervalType::LeftOpenRightClosed;
			_left = interval.Left();
			_right = interval.Right();
		}

		constexpr Interval(base::LeftClosedRightOpenInterval<T> const &interval)
		{
			_type = base::IntervalType::LeftClosedRightOpen;
			_left = interval.Left();
			_right = interval.Right();
		}

		constexpr Interval(base::LeftInfiniteRightOpenInterval<T> const &interval)
		{
			_type = base::IntervalType::LeftInfiniteRightOpen;
			_right = interval.Right();
		}

		constexpr Interval(base::LeftInfiniteRightClosedInterval<T> const &interval)
		{
			_type = base::IntervalType::LeftInfiniteRightClosed;
			_right = interval.Right();
		}

		constexpr Interval(base::LeftOpenRightInfiniteInterval<T> const &interval)
		{
			_type = base::IntervalType::LeftOpenRightInfinite;
			_left = interval.Left();
		}

		constexpr Interval(base::LeftClosedRightInfiniteInterval<T> const &interval)
		{
			_type = base::IntervalType::LeftClosedRightInfinite;
			_left = interval.Left();
		}

		constexpr base::IntervalType Type() const
		{
			return _type;
		}

		constexpr bool LeftIsInfinite() const
		{
			switch (_type)
			{
			case base::IntervalType::LeftInfiniteRightOpen:
				{
					return true;
				}
			case base::IntervalType::LeftInfiniteRightClosed:
				{
					return true;
				}
			default:
				{
					return false;
				}
			}
		}

		constexpr bool RightIsInfinite() const
		{
			switch (_type)
			{
			case base::IntervalType::LeftOpenRightInfinite:
				{
					return true;
				}
			case base::IntervalType::LeftClosedRightInfinite:
				{
					return true;
				}
			default:
				{
					return false;
				}
			}
		}
	};

} // namespace base
