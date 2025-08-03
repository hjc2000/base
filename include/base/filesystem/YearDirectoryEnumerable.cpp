#include "YearDirectoryEnumerable.h" // IWYU pragma: keep
#include "base/Console.h"
#include "base/IDisposable.h"
#include "base/math/interval/Interval.h"
#include "base/string/define.h"
#include "base/string/Parse.h"
#include "base/time/DateTime.h"
#include "base/time/DateTimeInterval.h"
#include "filesystem.h"
#include <cstdint>
#include <stdexcept>

class base::filesystem::YearDirectoryEnumerable::Enumerator final :
	public base::IEnumerator<base::DirectoryEntry const>
{
private:
	///
	/// @brief “基路径/年/月/日/文件” 中的 “基路径”。
	///
	///
	base::Path _base_path;

	base::UtcHourOffset _utc_hour_offset;

	bool _disposed = false;

	base::Interval<base::DateTime> _year_date_time_interval;
	std::shared_ptr<base::IEnumerator<base::DirectoryEntry const>> _year_dir_iterator;
	int64_t _year{};

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

			base::ClosedInterval<base::DateTime> interval{
				base::DateTime{
					_utc_hour_offset,
					_year,
					1,
					1,
					0,
					0,
					0,
					0,
				},
				base::DateTime{
					_utc_hour_offset,
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

		return true;
	}

	///
	/// @brief 移动到下一个年目录。
	///
	/// @return 移动完之后如果 _year_dir_iterator 指向有效的年目录，则返回 true, 否则返回 false.
	///
	bool MoveToNextYear()
	{
		while (true)
		{
			if (_disposed)
			{
				return false;
			}

			// 先完成 _year_dir_iterator 的初始化或递增操作
			if (_year_dir_iterator == nullptr)
			{
				_year_dir_iterator = base::filesystem::CreateDirectoryEntryEnumerator(_base_path);
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

public:
	Enumerator(base::Path const &base_path,
			   base::Interval<base::DateTime> const &date_time_range,
			   base::UtcHourOffset const &utc_hour_offset)
	{
		_base_path = base_path;
		_year_date_time_interval = base::GetYearDateTimeInterval(date_time_range);
		_utc_hour_offset = utc_hour_offset;
		MoveToNextYear();
	}

	///
	/// @brief 迭代器当前是否指向尾后元素。
	///
	/// @return
	///
	virtual bool IsEnd() const override
	{
		if (_disposed)
		{
			return true;
		}

		if (_year_dir_iterator == nullptr)
		{
			return true;
		}

		return _year_dir_iterator->IsEnd();
	}

	///
	/// @brief 获取当前值的引用。
	///
	/// @note 迭代器构造后，如果被迭代的集合不为空，要立即让 CurrentValue 指向第一个有效元素。
	///
	/// @return
	///
	virtual base::DirectoryEntry const &CurrentValue() override
	{
		if (_disposed)
		{
			throw base::ObjectDisposedException{};
		}

		if (_year_dir_iterator == nullptr || _year_dir_iterator->IsEnd())
		{
			throw std::runtime_error{CODE_POS_STR + "没有当前值可用。"};
		}

		return _year_dir_iterator->CurrentValue();
	}

	///
	/// @brief 递增迭代器的位置。
	///
	///
	virtual void Add() override
	{
		MoveToNextYear();
	}
};

std::shared_ptr<base::IEnumerator<base::DirectoryEntry const>> base::filesystem::YearDirectoryEnumerable::GetEnumerator()
{
	if (_disposed)
	{
		throw base::ObjectDisposedException{};
	}

	return std::shared_ptr<Enumerator>{new Enumerator{
		_base_path,
		_date_time_range,
		_utc_hour_offset,
	}};
}
