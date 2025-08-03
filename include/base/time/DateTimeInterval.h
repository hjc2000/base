#pragma once
#include "base/math/Interval.h"
#include "base/time/DateTime.h"

namespace base
{
	///
	/// @brief 把日期时间区间的分辨率调整到整年。
	///
	/// @param value
	/// @return
	///
	constexpr base::Interval<base::DateTime> GetYearDateTimeInterval(base::Interval<base::DateTime> const &value)
	{
		switch (value.Type())
		{
		case IntervalType::Closed:
			{
				base::ClosedInterval<base::DateTime> interval{value};
				base::DateTime left = interval.Left();
				base::DateTime right = interval.Right();

				base::ClosedInterval<base::DateTime> ret{
					base::DateTime{
						left.Year(),
						1,
						1,
						0,
						0,
						0,
						0,
					},
					base::DateTime{
						right.Year(),
						12,
						31,
						23,
						59,
						59,
						static_cast<int64_t>(1e9) - 1,
					},
				};

				return ret;
			}
		case IntervalType::Open:
			{
				base::OpenInterval<base::DateTime> interval{value};
				base::DateTime left = interval.Left();
				base::DateTime right = interval.Right();

				base::OpenInterval<base::DateTime> ret{
					base::DateTime{
						left.Year(),
						1,
						1,
						0,
						0,
						0,
						0,
					},
					base::DateTime{
						right.Year(),
						12,
						31,
						23,
						59,
						59,
						static_cast<int64_t>(1e9) - 1,
					},
				};

				return ret;
			}
		case IntervalType::LeftOpenRightClosed:
			{
				base::LeftOpenRightClosedInterval<base::DateTime> interval{value};
				base::DateTime left = interval.Left();
				base::DateTime right = interval.Right();

				base::LeftOpenRightClosedInterval<base::DateTime> ret{
					base::DateTime{
						left.Year(),
						1,
						1,
						0,
						0,
						0,
						0,
					},
					base::DateTime{
						right.Year(),
						12,
						31,
						23,
						59,
						59,
						static_cast<int64_t>(1e9) - 1,
					},
				};

				return ret;
			}
		case IntervalType::LeftClosedRightOpen:
			{
				base::LeftClosedRightOpenInterval<base::DateTime> interval{value};
				base::DateTime left = interval.Left();
				base::DateTime right = interval.Right();

				base::LeftClosedRightOpenInterval<base::DateTime> ret{
					base::DateTime{
						left.Year(),
						1,
						1,
						0,
						0,
						0,
						0,
					},
					base::DateTime{
						right.Year(),
						12,
						31,
						23,
						59,
						59,
						static_cast<int64_t>(1e9) - 1,
					},
				};

				return ret;
			}
		case IntervalType::LeftInfiniteRightOpen:
			{
				base::LeftInfiniteRightOpenInterval<base::DateTime> interval{value};
				base::DateTime right = interval.Right();

				base::LeftInfiniteRightOpenInterval<base::DateTime> ret{
					base::DateTime{
						right.Year(),
						12,
						31,
						23,
						59,
						59,
						static_cast<int64_t>(1e9) - 1,
					},
				};

				return ret;
			}
		case IntervalType::LeftInfiniteRightClosed:
			{
				base::LeftInfiniteRightClosedInterval<base::DateTime> interval{value};
				base::DateTime right = interval.Right();

				base::LeftInfiniteRightClosedInterval<base::DateTime> ret{
					base::DateTime{
						right.Year(),
						12,
						31,
						23,
						59,
						59,
						static_cast<int64_t>(1e9) - 1,
					},
				};

				return ret;
			}
		case IntervalType::LeftOpenRightInfinite:
			{
				base::LeftOpenRightInfiniteInterval<base::DateTime> interval{value};
				base::DateTime left = interval.Left();

				base::LeftOpenRightInfiniteInterval<base::DateTime> ret{
					base::DateTime{
						left.Year(),
						1,
						1,
						0,
						0,
						0,
						0,
					},
				};

				return ret;
			}
		case IntervalType::LeftClosedRightInfinite:
			{
				base::LeftClosedRightInfiniteInterval<base::DateTime> interval{value};
				base::DateTime left = interval.Left();

				base::LeftClosedRightInfiniteInterval<base::DateTime> ret{
					base::DateTime{
						left.Year(),
						1,
						1,
						0,
						0,
						0,
						0,
					},
				};

				return ret;
			}
		default:
			{
				throw std::runtime_error{CODE_POS_STR + "不支持的区间类型。"};
			}
		}
	}

	///
	/// @brief 把日期时间区间的分辨率调整到整月。
	///
	/// @param value
	/// @return
	///
	constexpr base::Interval<base::DateTime> GetYearMonthDateTimeInterval(base::Interval<base::DateTime> const &value)
	{
		switch (value.Type())
		{
		case IntervalType::Closed:
			{
				base::ClosedInterval<base::DateTime> interval{value};
				base::DateTime left = interval.Left();
				base::DateTime right = interval.Right();

				base::ClosedInterval<base::DateTime> ret{
					base::DateTime{
						left.Year(),
						left.Month(),
						1,
						0,
						0,
						0,
						0,
					},
					base::DateTime{
						right.Year(),
						right.Month(),
						right.CurrentMonthDayCount(),
						23,
						59,
						59,
						static_cast<int64_t>(1e9) - 1,
					},
				};

				return ret;
			}
		case IntervalType::Open:
			{
				base::OpenInterval<base::DateTime> interval{value};
				base::DateTime left = interval.Left();
				base::DateTime right = interval.Right();

				base::OpenInterval<base::DateTime> ret{
					base::DateTime{
						left.Year(),
						left.Month(),
						1,
						0,
						0,
						0,
						0,
					},
					base::DateTime{
						right.Year(),
						right.Month(),
						right.CurrentMonthDayCount(),
						23,
						59,
						59,
						static_cast<int64_t>(1e9) - 1,
					},
				};

				return ret;
			}
		case IntervalType::LeftOpenRightClosed:
			{
				base::LeftOpenRightClosedInterval<base::DateTime> interval{value};
				base::DateTime left = interval.Left();
				base::DateTime right = interval.Right();

				base::LeftOpenRightClosedInterval<base::DateTime> ret{
					base::DateTime{
						left.Year(),
						left.Month(),
						1,
						0,
						0,
						0,
						0,
					},
					base::DateTime{
						right.Year(),
						right.Month(),
						right.CurrentMonthDayCount(),
						23,
						59,
						59,
						static_cast<int64_t>(1e9) - 1,
					},
				};

				return ret;
			}
		case IntervalType::LeftClosedRightOpen:
			{
				base::LeftClosedRightOpenInterval<base::DateTime> interval{value};
				base::DateTime left = interval.Left();
				base::DateTime right = interval.Right();

				base::LeftClosedRightOpenInterval<base::DateTime> ret{
					base::DateTime{
						left.Year(),
						left.Month(),
						1,
						0,
						0,
						0,
						0,
					},
					base::DateTime{
						right.Year(),
						right.Month(),
						right.CurrentMonthDayCount(),
						23,
						59,
						59,
						static_cast<int64_t>(1e9) - 1,
					},
				};

				return ret;
			}
		case IntervalType::LeftInfiniteRightOpen:
			{
				base::LeftInfiniteRightOpenInterval<base::DateTime> interval{value};
				base::DateTime right = interval.Right();

				base::LeftInfiniteRightOpenInterval<base::DateTime> ret{
					base::DateTime{
						right.Year(),
						right.Month(),
						right.CurrentMonthDayCount(),
						23,
						59,
						59,
						static_cast<int64_t>(1e9) - 1,
					},
				};

				return ret;
			}
		case IntervalType::LeftInfiniteRightClosed:
			{
				base::LeftInfiniteRightClosedInterval<base::DateTime> interval{value};
				base::DateTime right = interval.Right();

				base::LeftInfiniteRightClosedInterval<base::DateTime> ret{
					base::DateTime{
						right.Year(),
						right.Month(),
						right.CurrentMonthDayCount(),
						23,
						59,
						59,
						static_cast<int64_t>(1e9) - 1,
					},
				};

				return ret;
			}
		case IntervalType::LeftOpenRightInfinite:
			{
				base::LeftOpenRightInfiniteInterval<base::DateTime> interval{value};
				base::DateTime left = interval.Left();

				base::LeftOpenRightInfiniteInterval<base::DateTime> ret{
					base::DateTime{
						left.Year(),
						left.Month(),
						1,
						0,
						0,
						0,
						0,
					},
				};

				return ret;
			}
		case IntervalType::LeftClosedRightInfinite:
			{
				base::LeftClosedRightInfiniteInterval<base::DateTime> interval{value};
				base::DateTime left = interval.Left();

				base::LeftClosedRightInfiniteInterval<base::DateTime> ret{
					base::DateTime{
						left.Year(),
						left.Month(),
						1,
						0,
						0,
						0,
						0,
					},
				};

				return ret;
			}
		default:
			{
				throw std::runtime_error{CODE_POS_STR + "不支持的区间类型。"};
			}
		}
	}

	///
	/// @brief 把日期时间区间的分辨率调整到整日。
	///
	/// @param value
	/// @return
	///
	constexpr base::Interval<base::DateTime> GetYearMonthDayDateTimeInterval(base::Interval<base::DateTime> const &value)
	{
		switch (value.Type())
		{
		case IntervalType::Closed:
			{
				base::ClosedInterval<base::DateTime> interval{value};
				base::DateTime left = interval.Left();
				base::DateTime right = interval.Right();

				base::ClosedInterval<base::DateTime> ret{
					base::DateTime{
						left.Year(),
						left.Month(),
						left.Day(),
						0,
						0,
						0,
						0,
					},
					base::DateTime{
						right.Year(),
						right.Month(),
						right.Day(),
						23,
						59,
						59,
						static_cast<int64_t>(1e9) - 1,
					},
				};

				return ret;
			}
		case IntervalType::Open:
			{
				base::OpenInterval<base::DateTime> interval{value};
				base::DateTime left = interval.Left();
				base::DateTime right = interval.Right();

				base::OpenInterval<base::DateTime> ret{
					base::DateTime{
						left.Year(),
						left.Month(),
						left.Day(),
						0,
						0,
						0,
						0,
					},
					base::DateTime{
						right.Year(),
						right.Month(),
						right.Day(),
						23,
						59,
						59,
						static_cast<int64_t>(1e9) - 1,
					},
				};

				return ret;
			}
		case IntervalType::LeftOpenRightClosed:
			{
				base::LeftOpenRightClosedInterval<base::DateTime> interval{value};
				base::DateTime left = interval.Left();
				base::DateTime right = interval.Right();

				base::LeftOpenRightClosedInterval<base::DateTime> ret{
					base::DateTime{
						left.Year(),
						left.Month(),
						left.Day(),
						0,
						0,
						0,
						0,
					},
					base::DateTime{
						right.Year(),
						right.Month(),
						right.Day(),
						23,
						59,
						59,
						static_cast<int64_t>(1e9) - 1,
					},
				};

				return ret;
			}
		case IntervalType::LeftClosedRightOpen:
			{
				base::LeftClosedRightOpenInterval<base::DateTime> interval{value};
				base::DateTime left = interval.Left();
				base::DateTime right = interval.Right();

				base::LeftClosedRightOpenInterval<base::DateTime> ret{
					base::DateTime{
						left.Year(),
						left.Month(),
						left.Day(),
						0,
						0,
						0,
						0,
					},
					base::DateTime{
						right.Year(),
						right.Month(),
						right.Day(),
						23,
						59,
						59,
						static_cast<int64_t>(1e9) - 1,
					},
				};

				return ret;
			}
		case IntervalType::LeftInfiniteRightOpen:
			{
				base::LeftInfiniteRightOpenInterval<base::DateTime> interval{value};
				base::DateTime right = interval.Right();

				base::LeftInfiniteRightOpenInterval<base::DateTime> ret{
					base::DateTime{
						right.Year(),
						right.Month(),
						right.Day(),
						23,
						59,
						59,
						static_cast<int64_t>(1e9) - 1,
					},
				};

				return ret;
			}
		case IntervalType::LeftInfiniteRightClosed:
			{
				base::LeftInfiniteRightClosedInterval<base::DateTime> interval{value};
				base::DateTime right = interval.Right();

				base::LeftInfiniteRightClosedInterval<base::DateTime> ret{
					base::DateTime{
						right.Year(),
						right.Month(),
						right.Day(),
						23,
						59,
						59,
						static_cast<int64_t>(1e9) - 1,
					},
				};

				return ret;
			}
		case IntervalType::LeftOpenRightInfinite:
			{
				base::LeftOpenRightInfiniteInterval<base::DateTime> interval{value};
				base::DateTime left = interval.Left();

				base::LeftOpenRightInfiniteInterval<base::DateTime> ret{
					base::DateTime{
						left.Year(),
						left.Month(),
						left.Day(),
						0,
						0,
						0,
						0,
					},
				};

				return ret;
			}
		case IntervalType::LeftClosedRightInfinite:
			{
				base::LeftClosedRightInfiniteInterval<base::DateTime> interval{value};
				base::DateTime left = interval.Left();

				base::LeftClosedRightInfiniteInterval<base::DateTime> ret{
					base::DateTime{
						left.Year(),
						left.Month(),
						left.Day(),
						0,
						0,
						0,
						0,
					},
				};

				return ret;
			}
		default:
			{
				throw std::runtime_error{CODE_POS_STR + "不支持的区间类型。"};
			}
		}
	}

} // namespace base
