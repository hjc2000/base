#pragma once
#include "base/Console.h"
#include "base/math/interval/Interval.h"
#include "base/string/define.h"
#include "base/string/Parse.h"
#include "base/task/CancellationToken.h"
#include "base/time/DateTime.h"
#include "base/time/DateTimeInterval.h"
#include "filesystem.h"
#include <cstdint>
#include <stdexcept>

namespace base
{
	namespace filesystem
	{
		class DayDirectoryEnumerator final :
			public base::IEnumerator<base::DirectoryEntry const>
		{
		private:
			bool _has_not_moved = true;
			base::Path _year_month_path;
			base::UtcHourOffset _utc_hour_offset;
			bool _should_check_time_range = false;
			base::Interval<base::DateTime> _date_time_interval;
			std::shared_ptr<base::IEnumerator<base::DirectoryEntry const>> _day_dir_iterator;
			std::shared_ptr<base::CancellationToken> _cancellation_token;
			int64_t _year{};
			int64_t _month{};
			int64_t _day{};

			/* #region 检查 */

			///
			/// @brief 检查当前 _day_dir_iterator 指向的条目是否是目录。
			///
			/// @return 是目录返回 true, 不是目录返回 false.
			///
			bool CheckIsDirectory()
			{
				if (!_day_dir_iterator->CurrentValue().IsDirectory())
				{
					return false;
				}

				return true;
			}

			bool CheckDirName()
			{
				try
				{
					base::Path path = _day_dir_iterator->CurrentValue().Path();
					_day = base::Parse<int64_t>(path.LastName().ToString(), 10);
				}
				catch (std::exception const &e)
				{
					base::console().WriteError(CODE_POS_STR + e.what());
					return false;
				}
				catch (...)
				{
					base::console().WriteError(CODE_POS_STR + "未知异常。");
					return false;
				}

				return true;
			}

			bool CheckTimeRange()
			{
				if (!_should_check_time_range)
				{
					return true;
				}

				try
				{
					base::ClosedInterval<base::DateTime> interval{
						base::DateTime{
							_utc_hour_offset,
							_year,
							_month,
							_day,
							0,
							0,
							0,
							0,
						},
						base::DateTime{
							_utc_hour_offset,
							_year,
							_month,
							_day,
							23,
							59,
							59,
							static_cast<int64_t>(1e9) - 1,
						},
					};

					if (!_date_time_interval.HasIntersection(interval))
					{
						return false;
					}
				}
				catch (std::exception const &e)
				{
					base::console().WriteError(CODE_POS_STR + e.what());
					return false;
				}
				catch (...)
				{
					base::console().WriteError(CODE_POS_STR + "未知异常。");
					return false;
				}

				return true;
			}

			bool Check()
			{
				// 按顺序调用上方的检查函数。
				// 一定要按顺序，因为检查过程会为字段赋值，后一个检查会依赖前面检查的结果。
				if (!CheckIsDirectory())
				{
					return false;
				}

				if (!CheckDirName())
				{
					return false;
				}

				if (!CheckTimeRange())
				{
					return false;
				}

				return true;
			}

			/* #endregion */

			///
			/// @brief 移动到下一个日目录。
			///
			/// @return 移动完之后如果 _day_dir_iterator 指向有效的年目录，则返回 true, 否则返回 false.
			///
			bool MoveToNextDay()
			{
				while (true)
				{
					if (base::is_cancellation_requested(_cancellation_token))
					{
						return false;
					}

					if (_day_dir_iterator == nullptr)
					{
						_day_dir_iterator = base::filesystem::CreateDirectoryEntryEnumerator(_year_month_path);
					}

					if (!_day_dir_iterator->MoveToNext())
					{
						return false;
					}

					// 已经成功让年目录迭代器指向下一个有效项目了，接下来需要进行一些过滤，确保它是有效的年目录。
					if (!Check())
					{
						continue;
					}

					// 历经重重考验，终于确认年迭代器指向的是有效的年目录了。
					return true;
				}
			}

		public:
			DayDirectoryEnumerator(base::Path const &year_month_path,
								   bool should_check_time_range,
								   int64_t year,
								   int64_t month,
								   base::Interval<base::DateTime> const &date_time_range,
								   base::UtcHourOffset const &utc_hour_offset,
								   std::shared_ptr<base::CancellationToken> cancellation_token)
			{
				_year_month_path = year_month_path;
				_should_check_time_range = should_check_time_range;
				_cancellation_token = cancellation_token;

				_year = year;
				_month = month;
				_date_time_interval = base::GetYearMonthDayDateTimeInterval(date_time_range);
				_utc_hour_offset = utc_hour_offset;
				MoveToNextDay();
			}

			DayDirectoryEnumerator(base::Path const &base_path, std::shared_ptr<base::CancellationToken> cancellation_token)
			{
				_year_month_path = base_path;
				_should_check_time_range = false;
				_cancellation_token = cancellation_token;

				MoveToNextDay();
			}

			///
			/// @brief 迭代器当前是否指向尾后元素。
			///
			/// @return
			///
			virtual bool IsEnd() const override
			{
				if (base::is_cancellation_requested(_cancellation_token))
				{
					return true;
				}

				if (_day_dir_iterator == nullptr)
				{
					return true;
				}

				return _day_dir_iterator->IsEnd();
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
				base::throw_if_cancellation_is_requested(_cancellation_token);

				if (_day_dir_iterator == nullptr || _day_dir_iterator->IsEnd())
				{
					throw std::runtime_error{CODE_POS_STR + "没有当前值可用。"};
				}

				return _day_dir_iterator->CurrentValue();
			}

			///
			/// @brief 递增迭代器的位置。
			///
			///
			virtual void Add() override
			{
				base::throw_if_cancellation_is_requested(_cancellation_token);
				MoveToNextDay();
			}

			int64_t Day() const
			{
				return _day;
			}

			///
			/// @brief 从未被调用过 MoveToNext 方法。
			///
			/// @return
			///
			virtual bool HasNotMoved() override
			{
				return _has_not_moved;
			}

			///
			/// @brief 设置是否从未被调用过 MoveToNext 方法。
			///
			/// @param value
			///
			virtual void SetHasNotMoved(bool value) override
			{
				_has_not_moved = value;
			}
		};

	} // namespace filesystem
} // namespace base
