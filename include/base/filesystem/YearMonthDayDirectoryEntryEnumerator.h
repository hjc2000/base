#pragma once
#include "base/filesystem/DayDirectoryEnumerator.h"
#include "base/filesystem/MonthDirectoryEnumerator.h"
#include "base/filesystem/YearDirectoryEnumerator.h"
#include "base/math/interval/Interval.h"
#include "base/string/define.h"
#include "base/time/DateTime.h"
#include "filesystem.h"
#include <memory>
#include <stdexcept>

namespace base
{
	namespace filesystem
	{
		class YearMonthDayDirectoryEntryEnumerator final :
			public base::IEnumerator<base::DirectoryEntry const>
		{
		private:
			///
			/// @brief “基路径/年/月/日/文件” 中的 “基路径”。
			///
			///
			base::Path _base_path;
			bool _should_check_time_range = false;
			base::Interval<base::DateTime> _date_time_range;
			base::UtcHourOffset _utc_hour_offset;

			///
			/// @brief 用来迭代基路径的迭代器。
			///
			///
			std::shared_ptr<base::filesystem::YearDirectoryEnumerator> _year_dir_iterator;
			std::shared_ptr<base::filesystem::MonthDirectoryEnumerator> _month_dir_iterator;
			std::shared_ptr<base::filesystem::DayDirectoryEnumerator> _day_dir_iterator;
			std::shared_ptr<base::IEnumerator<base::DirectoryEntry const>> _file_iterator;

			/* #region 递增迭代器 */

			bool MoveToNextMonth()
			{
				while (true)
				{
					if (_month_dir_iterator == nullptr || _month_dir_iterator->IsEnd())
					{
						if (!_year_dir_iterator->MoveToNext())
						{
							return false;
						}

						base::DirectoryEntry entry = _year_dir_iterator->CurrentValue();
						base::Path year_dir_path = entry.Path();

						_month_dir_iterator = std::shared_ptr<base::filesystem::MonthDirectoryEnumerator>{new base::filesystem::MonthDirectoryEnumerator{
							year_dir_path,
							_should_check_time_range,
							_year_dir_iterator->Year(),
							_date_time_range,
							_utc_hour_offset,
						}};
					}

					if (!_month_dir_iterator->MoveToNext())
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
					if (_day_dir_iterator == nullptr || _day_dir_iterator->IsEnd())
					{
						if (!MoveToNextMonth())
						{
							return false;
						}

						base::DirectoryEntry entry = _month_dir_iterator->CurrentValue();
						base::Path month_dir_path = entry.Path();

						_day_dir_iterator = std::shared_ptr<base::filesystem::DayDirectoryEnumerator>{new base::filesystem::DayDirectoryEnumerator{
							month_dir_path,
							_should_check_time_range,
							_year_dir_iterator->Year(),
							_month_dir_iterator->Month(),
							_date_time_range,
							_utc_hour_offset,
						}};
					}

					if (!_day_dir_iterator->MoveToNext())
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

					if (!_file_iterator->MoveToNext())
					{
						continue;
					}

					return true;
				}
			}

			/* #endregion */

		public:
			YearMonthDayDirectoryEntryEnumerator(base::Path const &base_path,
												 bool should_check_time_range,
												 base::Interval<base::DateTime> const &date_time_range,
												 base::UtcHourOffset const &utc_hour_offset)
			{
				_base_path = base_path;
				_should_check_time_range = should_check_time_range;
				_date_time_range = date_time_range;
				_utc_hour_offset = utc_hour_offset;

				_year_dir_iterator = std::shared_ptr<base::filesystem::YearDirectoryEnumerator>{new base::filesystem::YearDirectoryEnumerator{
					base_path,
					_should_check_time_range,
					date_time_range,
					utc_hour_offset,
				}};

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

			///
			/// @brief 通过目录获得的 年/月/日 的日期时间。分辨率只精确到日。
			///
			/// @return
			///
			base::DateTime YearMonthDayDateTime() const
			{
				base::DateTime ret{
					base::UtcHourOffset{0},
					_year_dir_iterator->Year(),
					_month_dir_iterator->Month(),
					_day_dir_iterator->Day(),
					0,
					0,
					0,
					0,
				};

				return ret;
			}
		};

	} // namespace filesystem
} // namespace base
