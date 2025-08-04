#pragma once
#include "base/Console.h"
#include "base/filesystem/YearDirectoryEnumerator.h"
#include "base/IDisposable.h"
#include "base/math/interval/Interval.h"
#include "base/string/define.h"
#include "base/string/Parse.h"
#include "base/time/DateTime.h"
#include "base/time/DateTimeInterval.h"
#include "filesystem.h"
#include <cstdint>
#include <memory>
#include <stdexcept>

namespace base
{
	namespace filesystem
	{
		class YearMonthDayDirectoryEntryEnumerator final :
			public base::IEnumerator<base::DirectoryEntry const>,
			public IDisposable
		{
		private:
			bool _disposed = false;

			///
			/// @brief “基路径/年/月/日/文件” 中的 “基路径”。
			///
			///
			base::Path _base_path;
			base::Interval<base::DateTime> _date_time_range;
			base::UtcHourOffset _utc_hour_offset;

			base::Interval<base::DateTime> _year_month_date_time_interval;
			base::Interval<base::DateTime> _year_month_day_date_time_interval;

			///
			/// @brief 用来迭代基路径的迭代器。
			///
			///
			std::shared_ptr<base::filesystem::YearDirectoryEnumerator> _year_dir_iterator;
			std::shared_ptr<base::IEnumerator<base::DirectoryEntry const>> _month_dir_iterator;
			std::shared_ptr<base::IEnumerator<base::DirectoryEntry const>> _day_dir_iterator;
			std::shared_ptr<base::IEnumerator<base::DirectoryEntry const>> _file_iterator;

			int64_t _month{};
			int64_t _day{};

			/* #region 检查年、月、日条目 */

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

					base::DateTime right{
						_utc_hour_offset,
						_year_dir_iterator->Year(),
						_month,
						10,
						23,
						59,
						59,
						static_cast<int64_t>(1e9) - 1,
					};

					base::ClosedInterval<base::DateTime> interval{
						base::DateTime{
							_utc_hour_offset,
							_year_dir_iterator->Year(),
							_month,
							1,
							0,
							0,
							0,
							0,
						},
						base::DateTime{
							_utc_hour_offset,
							_year_dir_iterator->Year(),
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

					base::ClosedInterval<base::DateTime> interval{
						base::DateTime{
							_utc_hour_offset,
							_year_dir_iterator->Year(),
							_month,
							_day,
							0,
							0,
							0,
							0,
						},
						base::DateTime{
							_utc_hour_offset,
							_year_dir_iterator->Year(),
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

			/* #endregion */

			/* #region 递增迭代器 */

			bool MoveToNextMonth()
			{
				while (true)
				{
					if (_disposed)
					{
						return false;
					}

					if (_month_dir_iterator == nullptr || _month_dir_iterator->IsEnd())
					{
						if (!_year_dir_iterator->MoveToNext())
						{
							return false;
						}

						base::DirectoryEntry entry = _year_dir_iterator->CurrentValue();
						base::Path year_dir_path = entry.Path();
						_month_dir_iterator = base::filesystem::CreateDirectoryEntryEnumerator(year_dir_path);
					}

					if (!_month_dir_iterator->MoveToNext())
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
					if (_disposed)
					{
						return false;
					}

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

					if (!_day_dir_iterator->MoveToNext())
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
					if (_disposed)
					{
						return false;
					}

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
												 base::Interval<base::DateTime> const &date_time_range,
												 base::UtcHourOffset const &utc_hour_offset)
			{
				_base_path = base_path;
				_date_time_range = date_time_range;
				_utc_hour_offset = utc_hour_offset;

				_year_dir_iterator = std::shared_ptr<base::filesystem::YearDirectoryEnumerator>{new base::filesystem::YearDirectoryEnumerator{
					base_path,
					true,
					date_time_range,
					utc_hour_offset,
				}};

				_year_month_date_time_interval = base::GetYearMonthDateTimeInterval(date_time_range);
				_year_month_day_date_time_interval = base::GetYearMonthDayDateTimeInterval(date_time_range);

				MoveToNextFile();
			}

			~YearMonthDayDirectoryEntryEnumerator()
			{
				Dispose();
			}

			///
			/// @brief 处置对象，让对象准备好结束生命周期。类似于进入 “准备后事” 的状态。
			///
			/// @note 注意，对象并不是析构了，并不是完全无法访问，它仍然允许访问，仍然能执行一些
			/// 符合 “准备后事” 的工作。
			///
			/// @note 如果年目录非常多，而且很多非法的目录干扰，造成在迭代器移动到下一个日志文件时
			/// 需要遍历和筛选掉很多非法的目录，导致要很久才能退出迭代，就可以在循环中直接调用本方法。
			/// 本方法会让迭代器内部的递归迭代立刻停止，不再搜索合法的年、月、日目录。但是调用本方法
			/// 后必须立刻结束循环，不能再次访问迭代器。
			///
			virtual void Dispose() override
			{
				if (_disposed)
				{
					return;
				}

				_disposed = true;
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
				if (_disposed)
				{
					throw base::ObjectDisposedException{};
				}

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
				if (_disposed)
				{
					throw base::ObjectDisposedException{};
				}

				MoveToNextFile();
			}
		};

	} // namespace filesystem
} // namespace base
