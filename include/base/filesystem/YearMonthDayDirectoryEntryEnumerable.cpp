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

	void MoveToNextYear()
	{
		if (_year_dir_iterator == nullptr)
		{
			_year_dir_iterator = base::filesystem::CreateDirectoryEntryEnumerator(_enumerable._base_path);
			return;
		}

		if (_year_dir_iterator->IsEnd())
		{
			// 没有下一个年份了
			return;
		}

		_year_dir_iterator->Add();
	}

	void MoveToNextMonth()
	{
		if (_month_dir_iterator == nullptr || _month_dir_iterator->IsEnd())
		{
			MoveToNextYear();
			if (_year_dir_iterator->IsEnd())
			{
				return;
			}

			base::DirectoryEntry entry = _year_dir_iterator->CurrentValue();
			base::Path year_dir_path = entry.Path();
			_month_dir_iterator = base::filesystem::CreateDirectoryEntryEnumerator(year_dir_path);
			return;
		}

		_month_dir_iterator->Add();
	}

	void MoveToNextDay()
	{
		if (_day_dir_iterator == nullptr || _day_dir_iterator->IsEnd())
		{
			MoveToNextMonth();
			if (_month_dir_iterator->IsEnd())
			{
				return;
			}

			base::DirectoryEntry entry = _month_dir_iterator->CurrentValue();
			base::Path month_dir_path = entry.Path();
			_day_dir_iterator = base::filesystem::CreateDirectoryEntryEnumerator(month_dir_path);
			return;
		}

		_day_dir_iterator->Add();
	}

	void MoveToNextFile()
	{
		if (_file_iterator == nullptr || _file_iterator->IsEnd())
		{
			MoveToNextDay();
			if (_day_dir_iterator->IsEnd())
			{
				// 移动到下一天后 _day_dir_iterator 仍然结束，说明没有下一天了。
				return;
			}

			base::DirectoryEntry entry = _day_dir_iterator->CurrentValue();
			base::Path day_dir_path = entry.Path();
			_file_iterator = base::filesystem::CreateDirectoryEntryEnumerator(day_dir_path);
			return;
		}

		_file_iterator->Add();
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
