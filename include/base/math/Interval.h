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
	/// @brief 通用区间。
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
		/* #region 构造函数 */

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

		/* #endregion */

		constexpr base::IntervalType Type() const
		{
			return _type;
		}

		constexpr T const &Left() const
		{
			if (LeftIsInfinite())
			{
				throw std::runtime_error{CODE_POS_STR + "区间左端是负无穷，本属性无效，无法返回有效值。"};
			}

			return _left;
		}

		constexpr T const &Right() const
		{
			if (RightIsInfinite())
			{
				throw std::runtime_error{CODE_POS_STR + "区间右端是正无穷，本属性无效，无法返回有效值。"};
			}

			return _right;
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

		/* #region 强制转换为特定区间 */

		constexpr explicit operator base::ClosedInterval<T>() const
		{
			if (_type != base::IntervalType::Closed)
			{
				throw std::runtime_error{CODE_POS_STR + "无法转换。"};
			}

			return base::ClosedInterval<T>{_left, _right};
		}

		constexpr explicit operator base::OpenInterval<T>() const
		{
			if (_type != base::IntervalType::Open)
			{
				throw std::runtime_error{CODE_POS_STR + "无法转换。"};
			}

			return base::OpenInterval<T>{_left, _right};
		}

		constexpr explicit operator base::LeftOpenRightClosedInterval<T>() const
		{
			if (_type != base::IntervalType::LeftOpenRightClosed)
			{
				throw std::runtime_error{CODE_POS_STR + "无法转换。"};
			}

			return base::LeftOpenRightClosedInterval<T>{_left, _right};
		}

		constexpr explicit operator base::LeftClosedRightOpenInterval<T>() const
		{
			if (_type != base::IntervalType::LeftClosedRightOpen)
			{
				throw std::runtime_error{CODE_POS_STR + "无法转换。"};
			}

			return base::LeftClosedRightOpenInterval<T>{_left, _right};
		}

		constexpr explicit operator base::LeftInfiniteRightOpenInterval<T>() const
		{
			if (_type != base::IntervalType::LeftInfiniteRightOpen)
			{
				throw std::runtime_error{CODE_POS_STR + "无法转换。"};
			}

			return base::LeftInfiniteRightOpenInterval<T>{_right};
		}

		constexpr explicit operator base::LeftInfiniteRightClosedInterval<T>() const
		{
			if (_type != base::IntervalType::LeftInfiniteRightClosed)
			{
				throw std::runtime_error{CODE_POS_STR + "无法转换。"};
			}

			return base::LeftInfiniteRightClosedInterval<T>{_right};
		}

		constexpr explicit operator base::LeftOpenRightInfiniteInterval<T>() const
		{
			if (_type != base::IntervalType::LeftOpenRightInfinite)
			{
				throw std::runtime_error{CODE_POS_STR + "无法转换。"};
			}

			return base::LeftOpenRightInfiniteInterval<T>{_left};
		}

		constexpr explicit operator base::LeftClosedRightInfiniteInterval<T>() const
		{
			if (_type != base::IntervalType::LeftClosedRightInfinite)
			{
				throw std::runtime_error{CODE_POS_STR + "无法转换。"};
			}

			return base::LeftClosedRightInfiniteInterval<T>{_left};
		}

		/* #endregion */

		///
		/// @brief 检查一个值是否在区间内。
		///
		/// @param value
		/// @return
		///
		constexpr bool IsInRange(T const &value) const
		{
			switch (_type)
			{
			case base::IntervalType::Closed:
				{
					return base::ClosedInterval<T>{*this}.IsInRange(value);
				}
			case base::IntervalType::Open:
				{
					return base::OpenInterval<T>{*this}.IsInRange(value);
				}
			case base::IntervalType::LeftOpenRightClosed:
				{
					return base::LeftOpenRightClosedInterval<T>{*this}.IsInRange(value);
				}
			case base::IntervalType::LeftClosedRightOpen:
				{
					return base::LeftClosedRightOpenInterval<T>{*this}.IsInRange(value);
				}
			case base::IntervalType::LeftInfiniteRightOpen:
				{
					return base::LeftInfiniteRightOpenInterval<T>{*this}.IsInRange(value);
				}
			case base::IntervalType::LeftInfiniteRightClosed:
				{
					return base::LeftInfiniteRightClosedInterval<T>{*this}.IsInRange(value);
				}
			case base::IntervalType::LeftOpenRightInfinite:
				{
					return base::LeftOpenRightInfiniteInterval<T>{*this}.IsInRange(value);
				}
			case base::IntervalType::LeftClosedRightInfinite:
				{
					return base::LeftClosedRightInfiniteInterval<T>{*this}.IsInRange(value);
				}
			default:
				{
					throw std::runtime_error{CODE_POS_STR + "无法判断该区间是否包含元素。"};
				}
			}
		}

		///
		/// @brief 检查一个区间是否在本区间内。
		///
		/// @param value
		/// @return
		///
		constexpr bool IsInRange(base::ClosedInterval<T> const &value) const
		{
			switch (_type)
			{
			case base::IntervalType::Closed:
				{
					if (value.Left() >= _left && value.Right() <= _right)
					{
						return true;
					}

					return false;
				}
			case base::IntervalType::Open:
				{
					if (value.Left() > _left && value.Right() < _right)
					{
						return true;
					}

					return false;
				}
			case base::IntervalType::LeftOpenRightClosed:
				{
					if (value.Left() > _left && value.Right() <= _right)
					{
						return true;
					}

					return false;
				}
			case base::IntervalType::LeftClosedRightOpen:
				{
					if (value.Left() >= _left && value.Right() < _right)
					{
						return true;
					}

					return false;
				}
			case base::IntervalType::LeftInfiniteRightOpen:
				{
					if (value.Right() < _right)
					{
						return true;
					}

					return false;
				}
			case base::IntervalType::LeftInfiniteRightClosed:
				{
					if (value.Right() <= _right)
					{
						return true;
					}

					return false;
				}
			case base::IntervalType::LeftOpenRightInfinite:
				{
					if (value.Left() > _left)
					{
						return true;
					}

					return false;
				}
			case base::IntervalType::LeftClosedRightInfinite:
				{
					if (value.Left() >= _left)
					{
						return true;
					}

					return false;
				}
			default:
				{
					throw std::runtime_error{CODE_POS_STR + "无法判断该区间是否包含元素。"};
				}
			}
		}

		///
		/// @brief 检查一个区间是否在本区间内。
		///
		/// @param value
		/// @return
		///
		constexpr bool IsInRange(base::OpenInterval<T> const &value) const
		{
			switch (_type)
			{
			case base::IntervalType::Closed:
				{
					if (value.Left() >= _left && value.Right() <= _right)
					{
						return true;
					}

					return false;
				}
			case base::IntervalType::Open:
				{
					if (value.Left() >= _left && value.Right() <= _right)
					{
						return true;
					}

					return false;
				}
			case base::IntervalType::LeftOpenRightClosed:
				{
					if (value.Left() >= _left && value.Right() <= _right)
					{
						return true;
					}

					return false;
				}
			case base::IntervalType::LeftClosedRightOpen:
				{
					if (value.Left() >= _left && value.Right() <= _right)
					{
						return true;
					}

					return false;
				}
			case base::IntervalType::LeftInfiniteRightOpen:
				{
					if (value.Right() <= _right)
					{
						return true;
					}

					return false;
				}
			case base::IntervalType::LeftInfiniteRightClosed:
				{
					if (value.Right() <= _right)
					{
						return true;
					}

					return false;
				}
			case base::IntervalType::LeftOpenRightInfinite:
				{
					if (value.Left() >= _left)
					{
						return true;
					}

					return false;
				}
			case base::IntervalType::LeftClosedRightInfinite:
				{
					if (value.Left() >= _left)
					{
						return true;
					}

					return false;
				}
			default:
				{
					throw std::runtime_error{CODE_POS_STR + "无法判断该区间是否包含元素。"};
				}
			}
		}

		///
		/// @brief 检查一个区间是否在本区间内。
		///
		/// @param value
		/// @return
		///
		constexpr bool IsInRange(base::LeftOpenRightClosedInterval<T> const &value) const
		{
			switch (_type)
			{
			case base::IntervalType::Closed:
				{
					if (value.Left() >= _left && value.Right() <= _right)
					{
						return true;
					}

					return false;
				}
			case base::IntervalType::Open:
				{
					if (value.Left() >= _left && value.Right() < _right)
					{
						return true;
					}

					return false;
				}
			case base::IntervalType::LeftOpenRightClosed:
				{
					if (value.Left() >= _left && value.Right() <= _right)
					{
						return true;
					}

					return false;
				}
			case base::IntervalType::LeftClosedRightOpen:
				{
					if (value.Left() >= _left && value.Right() < _right)
					{
						return true;
					}

					return false;
				}
			case base::IntervalType::LeftInfiniteRightOpen:
				{
					if (value.Right() < _right)
					{
						return true;
					}

					return false;
				}
			case base::IntervalType::LeftInfiniteRightClosed:
				{
					if (value.Right() <= _right)
					{
						return true;
					}

					return false;
				}
			case base::IntervalType::LeftOpenRightInfinite:
				{
					if (value.Left() >= _left)
					{
						return true;
					}

					return false;
				}
			case base::IntervalType::LeftClosedRightInfinite:
				{
					if (value.Left() >= _left)
					{
						return true;
					}

					return false;
				}
			default:
				{
					throw std::runtime_error{CODE_POS_STR + "无法判断该区间是否包含元素。"};
				}
			}
		}

		///
		/// @brief 检查一个区间是否在本区间内。
		///
		/// @param value
		/// @return
		///
		constexpr bool IsInRange(base::LeftClosedRightOpenInterval<T> const &value) const
		{
			switch (_type)
			{
			case base::IntervalType::Closed:
				{
					if (value.Left() >= _left && value.Right() <= _right)
					{
						return true;
					}

					return false;
				}
			case base::IntervalType::Open:
				{
					if (value.Left() > _left && value.Right() <= _right)
					{
						return true;
					}

					return false;
				}
			case base::IntervalType::LeftOpenRightClosed:
				{
					if (value.Left() > _left && value.Right() <= _right)
					{
						return true;
					}

					return false;
				}
			case base::IntervalType::LeftClosedRightOpen:
				{
					if (value.Left() >= _left && value.Right() <= _right)
					{
						return true;
					}

					return false;
				}
			case base::IntervalType::LeftInfiniteRightOpen:
				{
					if (value.Right() <= _right)
					{
						return true;
					}

					return false;
				}
			case base::IntervalType::LeftInfiniteRightClosed:
				{
					if (value.Right() <= _right)
					{
						return true;
					}

					return false;
				}
			case base::IntervalType::LeftOpenRightInfinite:
				{
					if (value.Left() > _left)
					{
						return true;
					}

					return false;
				}
			case base::IntervalType::LeftClosedRightInfinite:
				{
					if (value.Left() >= _left)
					{
						return true;
					}

					return false;
				}
			default:
				{
					throw std::runtime_error{CODE_POS_STR + "无法判断该区间是否包含元素。"};
				}
			}
		}

		///
		/// @brief 检查一个区间是否在本区间内。
		///
		/// @param value
		/// @return
		///
		constexpr bool IsInRange(base::LeftInfiniteRightOpenInterval<T> const &value) const
		{
			switch (_type)
			{
			case base::IntervalType::Closed:
				{
					return false;
				}
			case base::IntervalType::Open:
				{
					return false;
				}
			case base::IntervalType::LeftOpenRightClosed:
				{
					return false;
				}
			case base::IntervalType::LeftClosedRightOpen:
				{
					return false;
				}
			case base::IntervalType::LeftInfiniteRightOpen:
				{
					if (value.Right() <= _right)
					{
						return true;
					}

					return false;
				}
			case base::IntervalType::LeftInfiniteRightClosed:
				{
					if (value.Right() <= _right)
					{
						return true;
					}

					return false;
				}
			case base::IntervalType::LeftOpenRightInfinite:
				{
					return false;
				}
			case base::IntervalType::LeftClosedRightInfinite:
				{
					return false;
				}
			default:
				{
					throw std::runtime_error{CODE_POS_STR + "无法判断该区间是否包含元素。"};
				}
			}
		}

		///
		/// @brief 检查一个区间是否在本区间内。
		///
		/// @param value
		/// @return
		///
		constexpr bool IsInRange(base::LeftInfiniteRightClosedInterval<T> const &value) const
		{
			switch (_type)
			{
			case base::IntervalType::Closed:
				{
					return false;
				}
			case base::IntervalType::Open:
				{
					return false;
				}
			case base::IntervalType::LeftOpenRightClosed:
				{
					return false;
				}
			case base::IntervalType::LeftClosedRightOpen:
				{
					return false;
				}
			case base::IntervalType::LeftInfiniteRightOpen:
				{
					if (value.Right() < _right)
					{
						return true;
					}

					return false;
				}
			case base::IntervalType::LeftInfiniteRightClosed:
				{
					if (value.Right() <= _right)
					{
						return true;
					}

					return false;
				}
			case base::IntervalType::LeftOpenRightInfinite:
				{
					return false;
				}
			case base::IntervalType::LeftClosedRightInfinite:
				{
					return false;
				}
			default:
				{
					throw std::runtime_error{CODE_POS_STR + "无法判断该区间是否包含元素。"};
				}
			}
		}

		///
		/// @brief 检查一个区间是否在本区间内。
		///
		/// @param value
		/// @return
		///
		constexpr bool IsInRange(base::LeftOpenRightInfiniteInterval<T> const &value) const
		{
			switch (_type)
			{
			case base::IntervalType::Closed:
				{
					return false;
				}
			case base::IntervalType::Open:
				{
					return false;
				}
			case base::IntervalType::LeftOpenRightClosed:
				{
					return false;
				}
			case base::IntervalType::LeftClosedRightOpen:
				{
					return false;
				}
			case base::IntervalType::LeftInfiniteRightOpen:
				{
					return false;
				}
			case base::IntervalType::LeftInfiniteRightClosed:
				{
					return false;
				}
			case base::IntervalType::LeftOpenRightInfinite:
				{
					if (value.Left() >= _left)
					{
						return true;
					}

					return false;
				}
			case base::IntervalType::LeftClosedRightInfinite:
				{
					if (value.Left() >= _left)
					{
						return true;
					}

					return false;
				}
			default:
				{
					throw std::runtime_error{CODE_POS_STR + "无法判断该区间是否包含元素。"};
				}
			}
		}

		///
		/// @brief 检查一个区间是否在本区间内。
		///
		/// @param value
		/// @return
		///
		constexpr bool IsInRange(base::LeftClosedRightInfiniteInterval<T> const &value) const
		{
			switch (_type)
			{
			case base::IntervalType::Closed:
				{
					return false;
				}
			case base::IntervalType::Open:
				{
					return false;
				}
			case base::IntervalType::LeftOpenRightClosed:
				{
					return false;
				}
			case base::IntervalType::LeftClosedRightOpen:
				{
					return false;
				}
			case base::IntervalType::LeftInfiniteRightOpen:
				{
					return false;
				}
			case base::IntervalType::LeftInfiniteRightClosed:
				{
					return false;
				}
			case base::IntervalType::LeftOpenRightInfinite:
				{
					if (value.Left() > _left)
					{
						return true;
					}

					return false;
				}
			case base::IntervalType::LeftClosedRightInfinite:
				{
					if (value.Left() >= _left)
					{
						return true;
					}

					return false;
				}
			default:
				{
					throw std::runtime_error{CODE_POS_STR + "无法判断该区间是否包含元素。"};
				}
			}
		}

		///
		/// @brief 检查一个区间是否在本区间内。
		///
		/// @param value
		/// @return
		///
		constexpr bool IsInRange(base::Interval<T> const &value) const
		{
			switch (value._type)
			{
			case base::IntervalType::Closed:
				{
					return IsInRange(base::ClosedInterval<T>{value});
				}
			case base::IntervalType::Open:
				{
					return IsInRange(base::OpenInterval<T>{value});
				}
			case base::IntervalType::LeftOpenRightClosed:
				{
					return IsInRange(base::LeftOpenRightClosedInterval<T>{value});
				}
			case base::IntervalType::LeftClosedRightOpen:
				{
					return IsInRange(base::LeftClosedRightOpenInterval<T>{value});
				}
			case base::IntervalType::LeftInfiniteRightOpen:
				{
					return IsInRange(base::LeftInfiniteRightOpenInterval<T>{value});
				}
			case base::IntervalType::LeftInfiniteRightClosed:
				{
					return IsInRange(base::LeftInfiniteRightClosedInterval<T>{value});
				}
			case base::IntervalType::LeftOpenRightInfinite:
				{
					return IsInRange(base::LeftOpenRightInfiniteInterval<T>{value});
				}
			case base::IntervalType::LeftClosedRightInfinite:
				{
					return IsInRange(base::LeftClosedRightInfiniteInterval<T>{value});
				}
			default:
				{
					throw std::runtime_error{CODE_POS_STR + "无法判断该区间是否包含元素。"};
				}
			}
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
