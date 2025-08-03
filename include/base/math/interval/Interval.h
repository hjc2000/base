#pragma once
#include "base/math/interval/ClosedInterval.h"
#include "base/math/interval/IntervalType.h"
#include "base/math/interval/LeftClosedRightInfiniteInterval.h"
#include "base/math/interval/LeftClosedRightOpenInterval.h"
#include "base/math/interval/LeftInfiniteRightClosedInterval.h"
#include "base/math/interval/LeftInfiniteRightOpenInterval.h"
#include "base/math/interval/LeftOpenRightClosedInterval.h"
#include "base/math/interval/LeftOpenRightInfiniteInterval.h"
#include "base/math/interval/OpenInterval.h"
#include "base/string/define.h"
#include <stdexcept>

namespace base
{
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

		/* #region IsInRange */

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

		/* #endregion */

		/* #region HasIntersection */

		constexpr bool HasIntersection(base::ClosedInterval<T> const &value) const
		{
			if (IsInRange(value.Left()))
			{
				return true;
			}

			if (IsInRange(value.Right()))
			{
				return true;
			}

			return false;
		}

		constexpr bool HasIntersection(base::OpenInterval<T> const &value) const
		{
			if (IsInRange(value.Left()))
			{
				return true;
			}

			if (IsInRange(value.Right()))
			{
				return true;
			}

			return false;
		}

		constexpr bool HasIntersection(base::LeftOpenRightClosedInterval<T> const &value) const
		{
			if (IsInRange(value.Left()))
			{
				return true;
			}

			if (IsInRange(value.Right()))
			{
				return true;
			}

			return false;
		}

		constexpr bool HasIntersection(base::LeftClosedRightOpenInterval<T> const &value) const
		{
			if (IsInRange(value.Left()))
			{
				return true;
			}

			if (IsInRange(value.Right()))
			{
				return true;
			}

			return false;
		}

		constexpr bool HasIntersection(base::LeftInfiniteRightOpenInterval<T> const &value) const
		{
			if (IsInRange(value.Right()))
			{
				return true;
			}

			return false;
		}

		constexpr bool HasIntersection(base::LeftInfiniteRightClosedInterval<T> const &value) const
		{
			if (IsInRange(value.Right()))
			{
				return true;
			}

			return false;
		}

		constexpr bool HasIntersection(base::LeftOpenRightInfiniteInterval<T> const &value) const
		{
			if (IsInRange(value.Left()))
			{
				return true;
			}

			return false;
		}

		///
		/// @brief 检查一个区间是否在本区间内。
		///
		/// @param value
		/// @return
		///
		constexpr bool HasIntersection(base::LeftClosedRightInfiniteInterval<T> const &value) const
		{
			if (IsInRange(value.Left()))
			{
				return true;
			}

			return false;
		}

		constexpr bool HasIntersection(base::Interval<T> const &value) const
		{
			switch (value._type)
			{
			case base::IntervalType::Closed:
				{
					return HasIntersection(base::ClosedInterval<T>{value});
				}
			case base::IntervalType::Open:
				{
					return HasIntersection(base::OpenInterval<T>{value});
				}
			case base::IntervalType::LeftOpenRightClosed:
				{
					return HasIntersection(base::LeftOpenRightClosedInterval<T>{value});
				}
			case base::IntervalType::LeftClosedRightOpen:
				{
					return HasIntersection(base::LeftClosedRightOpenInterval<T>{value});
				}
			case base::IntervalType::LeftInfiniteRightOpen:
				{
					return HasIntersection(base::LeftInfiniteRightOpenInterval<T>{value});
				}
			case base::IntervalType::LeftInfiniteRightClosed:
				{
					return HasIntersection(base::LeftInfiniteRightClosedInterval<T>{value});
				}
			case base::IntervalType::LeftOpenRightInfinite:
				{
					return HasIntersection(base::LeftOpenRightInfiniteInterval<T>{value});
				}
			case base::IntervalType::LeftClosedRightInfinite:
				{
					return HasIntersection(base::LeftClosedRightInfiniteInterval<T>{value});
				}
			default:
				{
					throw std::runtime_error{CODE_POS_STR + "无法判断该区间是否包含元素。"};
				}
			}
		}

		/* #endregion */

		/* #region IsOutOfRange */

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

		///
		/// @brief 检查一个值是否在区间外。
		///
		/// @param value
		/// @return
		///
		constexpr bool IsOutOfRange(base::Interval<T> const &value) const
		{
			return !IsInRange(value);
		}

		/* #endregion */
	};

} // namespace base
