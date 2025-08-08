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
		class MonthDirectoryEnumerator final :
			public base::IEnumerator<base::DirectoryEntry const>
		{
		private:
			bool _has_not_moved = true;
			base::Path _year_path;
			base::UtcHourOffset _utc_hour_offset;
			bool _should_check_time_range = false;
			base::Interval<base::DateTime> _date_time_interval;
			std::shared_ptr<base::IEnumerator<base::DirectoryEntry const>> _month_dir_iterator;
			int64_t _year{};
			int64_t _month{};

			std::shared_ptr<base::CancellationToken> _cancellation_token;

			/* #region 检查 */

			///
			/// @brief 检查当前 _month_dir_iterator 指向的条目是否是目录。
			///
			/// @return 是目录返回 true, 不是目录返回 false.
			///
			bool CheckIsDirectory()
			{
				if (!_month_dir_iterator->CurrentValue().IsDirectory())
				{
					return false;
				}

				return true;
			}

			bool CheckDirName()
			{
				try
				{
					base::Path path = _month_dir_iterator->CurrentValue().Path();
					_month = base::ParseInt64(path.LastName().ToString(), 10);
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

			bool CheckTimeRange()
			{
				if (!_should_check_time_range)
				{
					return true;
				}

				try
				{
					base::DateTime right{
						_utc_hour_offset,
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
							_utc_hour_offset,
							_year,
							_month,
							1,
							0,
							0,
							0,
							0,
						},
						base::DateTime{
							_utc_hour_offset,
							_year,
							_month,
							right.CurrentMonthDayCount(),
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
			/// @brief 移动到下一个月目录。
			///
			/// @return 移动完之后如果 _month_dir_iterator 指向有效的年目录，则返回 true, 否则返回 false.
			///
			bool MoveToNextMonth()
			{
				while (true)
				{
					if (_cancellation_token->IsCancellationRequested())
					{
						return false;
					}

					if (_month_dir_iterator == nullptr)
					{
						_month_dir_iterator = base::filesystem::CreateDirectoryEntryEnumerator(_year_path);
					}

					if (!_month_dir_iterator->MoveToNext())
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
			MonthDirectoryEnumerator(base::Path const &year_path,
									 bool should_check_time_range,
									 int64_t year,
									 base::Interval<base::DateTime> const &date_time_range,
									 base::UtcHourOffset const &utc_hour_offset,
									 std::shared_ptr<base::CancellationToken> cancellation_token)
			{
				_year_path = year_path;
				_should_check_time_range = should_check_time_range;
				_cancellation_token = cancellation_token;

				_year = year;
				_date_time_interval = base::GetYearMonthDateTimeInterval(date_time_range);
				_utc_hour_offset = utc_hour_offset;
				MoveToNextMonth();
			}

			MonthDirectoryEnumerator(base::Path const &base_path, std::shared_ptr<base::CancellationToken> cancellation_token)
			{
				_year_path = base_path;
				_should_check_time_range = false;
				_cancellation_token = cancellation_token;

				MoveToNextMonth();
			}

			///
			/// @brief 迭代器当前是否指向尾后元素。
			///
			/// @return
			///
			virtual bool IsEnd() const override
			{
				if (_cancellation_token->IsCancellationRequested())
				{
					return true;
				}

				if (_month_dir_iterator == nullptr)
				{
					return true;
				}

				return _month_dir_iterator->IsEnd();
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
				_cancellation_token->ThrowIfCancellationIsRequested();

				if (_month_dir_iterator == nullptr || _month_dir_iterator->IsEnd())
				{
					throw std::runtime_error{CODE_POS_STR + "没有当前值可用。"};
				}

				return _month_dir_iterator->CurrentValue();
			}

			///
			/// @brief 递增迭代器的位置。
			///
			///
			virtual void Add() override
			{
				_cancellation_token->ThrowIfCancellationIsRequested();
				MoveToNextMonth();
			}

			int64_t Month() const
			{
				return _month;
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
