#pragma once
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

namespace base
{
	namespace filesystem
	{
		class YearDirectoryEnumerator final :
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

			base::UtcHourOffset _utc_hour_offset;
			bool _should_check_time_range = false;
			base::Interval<base::DateTime> _year_date_time_interval;
			std::shared_ptr<base::IEnumerator<base::DirectoryEntry const>> _year_dir_iterator;
			int64_t _year{};

			///
			/// @brief 检查当前 _year_dir_iterator 指向的条目是否是目录。
			///
			/// @return 是目录返回 true, 不是目录返回 false.
			///
			bool CheckIsDirectory()
			{
				if (!_year_dir_iterator->CurrentValue().IsDirectory())
				{
					return false;
				}

				return true;
			}

			bool CheckDirName()
			{
				try
				{
					base::Path year_dir_path = _year_dir_iterator->CurrentValue().Path();
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

					if (_year_dir_iterator == nullptr)
					{
						_year_dir_iterator = base::filesystem::CreateDirectoryEntryEnumerator(_base_path);
					}

					if (!_year_dir_iterator->MoveToNext())
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
			YearDirectoryEnumerator(base::Path const &base_path,
									base::Interval<base::DateTime> const &date_time_range,
									base::UtcHourOffset const &utc_hour_offset)
			{
				_base_path = base_path;
				_year_date_time_interval = base::GetYearDateTimeInterval(date_time_range);
				_utc_hour_offset = utc_hour_offset;
				_should_check_time_range = true;
				MoveToNextYear();
			}

			YearDirectoryEnumerator(base::Path const &base_path)
			{
				_base_path = base_path;
				_should_check_time_range = false;
				MoveToNextYear();
			}

			~YearDirectoryEnumerator()
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

			///
			/// @brief 如果迭代器没有结束，则本属性会把当前迭代器指向的年目录的年提取出来。
			///
			/// @return
			///
			int64_t Year() const
			{
				return _year;
			}
		};

	} // namespace filesystem
} // namespace base
