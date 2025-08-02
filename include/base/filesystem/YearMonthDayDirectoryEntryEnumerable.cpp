#include "YearMonthDayDirectoryEntryEnumerable.h" // IWYU pragma: keep
#include "base/string/define.h"
#include "filesystem.h"
#include <stdexcept>

class base::filesystem::YearMonthDayDirectoryEntryEnumerable::Enumerator final :
	public base::IEnumerator<base::DirectoryEntry const>
{
private:
	YearMonthDayDirectoryEntryEnumerable &_enumerable;

	///
	/// @brief 用来迭代基路径的迭代器。
	///
	///
	std::shared_ptr<base::IEnumerator<base::DirectoryEntry const>> _year_dir_iterator;
	std::shared_ptr<base::IEnumerator<base::DirectoryEntry const>> _month_dir_iterator;
	std::shared_ptr<base::IEnumerator<base::DirectoryEntry const>> _day_dir_iterator;
	std::shared_ptr<base::IEnumerator<base::DirectoryEntry const>> _file_iterator;

	///
	/// @brief 移动到下一个年份。
	///
	/// @return 移动完之后如果 _year_dir_iterator 指向有效元素，则返回 true, 否则返回 false.
	///
	bool MoveToNextYear()
	{
		if (_year_dir_iterator == nullptr)
		{
			_year_dir_iterator = base::filesystem::CreateDirectoryEntryEnumerator(_enumerable._base_path);
			return _year_dir_iterator->IsNotEnd();
		}

		if (_year_dir_iterator->IsEnd())
		{
			// 没有下一个年份了
			return false;
		}

		_year_dir_iterator->Add();
		return _year_dir_iterator->IsNotEnd();
	}

	bool MoveToNextMonth()
	{
		while (true)
		{
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

			if (_month_dir_iterator->IsNotEnd())
			{
				return true;
			}

			// 没获取到有效的月目录迭代器，继续下一轮循环，继续前往下一个年目录。
		}
	}

	bool MoveToNextDay()
	{
		while (true)
		{
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

			if (_day_dir_iterator->IsNotEnd())
			{
				return true;
			}
		}
	}

	bool MoveToNextFile()
	{
		while (true)
		{
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

			if (_file_iterator->IsNotEnd())
			{
				return true;
			}
		}
	}

public:
	Enumerator(YearMonthDayDirectoryEntryEnumerable &enumerable)
		: _enumerable(enumerable)
	{
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
		if (_file_iterator == nullptr)
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
