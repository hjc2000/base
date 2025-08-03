#include "YearMonthDayDirectoryEntryEnumerable.h" // IWYU pragma: keep
#include "base/Console.h"
#include "base/math/Interval.h"
#include "base/string/define.h"
#include "base/string/Parse.h"
#include "base/time/DateTime.h"
#include "base/time/DateTimeInterval.h"
#include "filesystem.h"
#include <cstdint>
#include <stdexcept>

class base::filesystem::YearMonthDayDirectoryEntryEnumerable::Enumerator final :
	public base::IEnumerator<base::DirectoryEntry const>
{
private:
	YearMonthDayDirectoryEntryEnumerable &_enumerable;

	base::Interval<base::DateTime> _year_date_time_interval;
	base::Interval<base::DateTime> _year_month_date_time_interval;
	base::Interval<base::DateTime> _year_month_day_date_time_interval;

	///
	/// @brief 用来迭代基路径的迭代器。
	///
	///
	std::shared_ptr<base::IEnumerator<base::DirectoryEntry const>> _year_dir_iterator;
	std::shared_ptr<base::IEnumerator<base::DirectoryEntry const>> _month_dir_iterator;
	std::shared_ptr<base::IEnumerator<base::DirectoryEntry const>> _day_dir_iterator;
	std::shared_ptr<base::IEnumerator<base::DirectoryEntry const>> _file_iterator;

	int64_t _year{};
	int64_t _month{};
	int64_t _day{};

	/* #region 检查年、月、日条目 */

	bool CheckYearEntry()
	{
		base::DirectoryEntry entry = _year_dir_iterator->CurrentValue();
		if (!entry.IsDirectory())
		{
			return false;
		}

		// 当前迭代器指向的项目是目录，但还要检查目录名称是不是合法的年份数字。
		try
		{
			base::Path year_dir_path = entry.Path();
			_year = base::ParseInt64(year_dir_path.LastName().ToString(), 10);
		}
		catch (std::exception const &e)
		{
			base::console.WriteError(CODE_POS_STR + e.what());
			return false;
		}
		catch (...)
		{
			base::console.WriteError(CODE_POS_STR + "未知异常。");
			return false;
		}

		// 检查日期时间
		{
			base::ClosedInterval<base::DateTime> interval{
				base::DateTime{
					_enumerable._utc_hour_offset,
					_year,
					1,
					1,
					0,
					0,
					0,
					0,
				},
				base::DateTime{
					_enumerable._utc_hour_offset,
					_year,
					12,
					31,
					23,
					59,
					59,
					static_cast<int64_t>(1e9) - 1,
				},
			};

			if (!_year_date_time_interval.HasIntersection(interval))
			{
				return false;
			}
		}

		return true;
	}

	bool CheckMonthEntry()
	{
		base::DirectoryEntry entry = _month_dir_iterator->CurrentValue();
		if (!entry.IsDirectory())
		{
			return false;
		}

		try
		{
			base::Path month_dir_path = entry.Path();
			_month = base::ParseInt64(month_dir_path.LastName().ToString(), 10);
		}
		catch (std::exception const &e)
		{
			base::console.WriteError(CODE_POS_STR + e.what());
			return false;
		}
		catch (...)
		{
			base::console.WriteError(CODE_POS_STR + "未知异常。");
			return false;
		}

		// 检查日期时间
		{
			base::DateTime right{
				_enumerable._utc_hour_offset,
				_year,
				_month,
				10,
				23,
				59,
				59,
				static_cast<int64_t>(1e9) - 1,
			};

			base::ClosedInterval<base::DateTime> interval{
				base::DateTime{
					_enumerable._utc_hour_offset,
					_year,
					_month,
					1,
					0,
					0,
					0,
					0,
				},
				base::DateTime{
					_enumerable._utc_hour_offset,
					_year,
					_month,
					right.CurrentMonthDayCount(),
					23,
					59,
					59,
					static_cast<int64_t>(1e9) - 1,
				},
			};

			if (!_year_month_date_time_interval.HasIntersection(interval))
			{
				return false;
			}
		}

		return true;
	}

	bool CheckDayEntry()
	{
		base::DirectoryEntry entry = _day_dir_iterator->CurrentValue();
		if (!entry.IsDirectory())
		{
			return false;
		}

		try
		{
			base::Path day_dir_path = entry.Path();
			_day = base::ParseInt64(day_dir_path.LastName().ToString(), 10);
		}
		catch (std::exception const &e)
		{
			base::console.WriteError(CODE_POS_STR + e.what());
			return false;
		}
		catch (...)
		{
			base::console.WriteError(CODE_POS_STR + "未知异常。");
			return false;
		}

		// 检查日期时间
		{
			base::ClosedInterval<base::DateTime> interval{
				base::DateTime{
					_enumerable._utc_hour_offset,
					_year,
					_month,
					_day,
					0,
					0,
					0,
					0,
				},
				base::DateTime{
					_enumerable._utc_hour_offset,
					_year,
					_month,
					_day,
					23,
					59,
					59,
					static_cast<int64_t>(1e9) - 1,
				},
			};

			if (!_year_month_day_date_time_interval.HasIntersection(interval))
			{
				return false;
			}
		}

		return true;
	}

	/* #endregion */

	/* #region 递增迭代器 */

	///
	/// @brief 移动到下一个年目录。
	///
	/// @return 移动完之后如果 _year_dir_iterator 指向有效的年目录，则返回 true, 否则返回 false.
	///
	bool MoveToNextYear()
	{
		while (true)
		{
			// 先完成 _year_dir_iterator 的初始化或递增操作
			if (_year_dir_iterator == nullptr)
			{
				_year_dir_iterator = base::filesystem::CreateDirectoryEntryEnumerator(_enumerable._base_path);
			}
			else if (_year_dir_iterator->IsNotEnd())
			{
				// 只有迭代器还没结束时才能递增，否则其结果是未定义的。
				_year_dir_iterator->Add();
			}

			// 初始化或递增 _year_dir_iterator 完成。
			if (_year_dir_iterator->IsEnd())
			{
				return false;
			}

			// 已经成功让年目录迭代器指向下一个有效项目了，接下来需要进行一些过滤，确保它是有效的年目录。
			if (!CheckYearEntry())
			{
				continue;
			}

			// 历经重重考验，终于确认年迭代器指向的是有效的年目录了。
			return true;
		}
	}

	bool MoveToNextMonth()
	{
		while (true)
		{
			// 先完成 _month_dir_iterator 的初始化或递增操作。
			if (_month_dir_iterator == nullptr || _month_dir_iterator->IsEnd())
			{
				if (!MoveToNextYear())
				{
					return false;
				}

				base::DirectoryEntry entry = _year_dir_iterator->CurrentValue();
				base::Path year_dir_path = entry.Path();
				_month_dir_iterator = base::filesystem::CreateDirectoryEntryEnumerator(year_dir_path);
			}
			else
			{
				_month_dir_iterator->Add();
			}

			// 初始化或递增 _month_dir_iterator 完成。
			if (_month_dir_iterator->IsEnd())
			{
				continue;
			}

			if (!CheckMonthEntry())
			{
				continue;
			}

			return true;
		}
	}

	bool MoveToNextDay()
	{
		while (true)
		{
			// 先完成 _day_dir_iterator 的初始化或递增操作。
			if (_day_dir_iterator == nullptr || _day_dir_iterator->IsEnd())
			{
				if (!MoveToNextMonth())
				{
					return false;
				}

				base::DirectoryEntry entry = _month_dir_iterator->CurrentValue();
				base::Path month_dir_path = entry.Path();
				_day_dir_iterator = base::filesystem::CreateDirectoryEntryEnumerator(month_dir_path);
			}
			else
			{
				_day_dir_iterator->Add();
			}

			// 初始化或递增 _day_dir_iterator 完成。
			if (_day_dir_iterator->IsEnd())
			{
				continue;
			}

			if (!CheckDayEntry())
			{
				continue;
			}

			return true;
		}
	}

	bool MoveToNextFile()
	{
		while (true)
		{
			// 先完成 _file_iterator 的初始化或递增操作。
			if (_file_iterator == nullptr || _file_iterator->IsEnd())
			{
				if (!MoveToNextDay())
				{
					return false;
				}

				base::DirectoryEntry entry = _day_dir_iterator->CurrentValue();
				base::Path day_dir_path = entry.Path();
				_file_iterator = base::filesystem::CreateDirectoryEntryEnumerator(day_dir_path);
			}
			else
			{
				_file_iterator->Add();
			}

			// 初始化或递增 _file_iterator 完成。
			if (_file_iterator->IsEnd())
			{
				continue;
			}

			return true;
		}
	}

	/* #endregion */

public:
	Enumerator(YearMonthDayDirectoryEntryEnumerable &enumerable)
		: _enumerable(enumerable)
	{
		_year_date_time_interval = base::GetYearDateTimeInterval(_enumerable._date_time_range);
		_year_month_date_time_interval = base::GetYearMonthDateTimeInterval(_enumerable._date_time_range);
		_year_month_day_date_time_interval = base::GetYearMonthDayDateTimeInterval(_enumerable._date_time_range);

		MoveToNextFile();
	}

	///
	/// @brief 迭代器当前是否指向尾后元素。
	///
	/// @return
	///
	virtual bool IsEnd() const override
	{
		if (_file_iterator == nullptr)
		{
			return true;
		}

		return _file_iterator->IsEnd();
	}

	///
	/// @brief 获取当前值的引用。
	///
	/// @return
	///
	virtual base::DirectoryEntry const &CurrentValue() override
	{
		if (_file_iterator == nullptr || _file_iterator->IsEnd())
		{
			throw std::runtime_error{CODE_POS_STR + "没有当前值可用。"};
		}

		return _file_iterator->CurrentValue();
	}

	///
	/// @brief 递增迭代器的位置。
	///
	///
	virtual void Add() override
	{
		MoveToNextFile();
	}
};

std::shared_ptr<base::IEnumerator<base::DirectoryEntry const>> base::filesystem::YearMonthDayDirectoryEntryEnumerable::GetEnumerator()
{
	return std::shared_ptr<Enumerator>{new Enumerator{*this}};
}
