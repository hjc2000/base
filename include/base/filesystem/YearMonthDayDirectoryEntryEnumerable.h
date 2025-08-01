#pragma once
#include "base/container/iterator/IEnumerable.h"
#include "base/container/iterator/IEnumerator.h"
#include "base/filesystem/DirectoryEntry.h"
#include "base/filesystem/Path.h"
#include "base/math/Interval.h"
#include "base/time/DateTime.h"
#include "filesystem.h"

namespace base
{
	namespace filesystem
	{
		///
		/// @brief 用于迭代像 “基路径/年/月/日/文件” 这种目录结构的最后一层的文件。
		///
		///
		class YearMonthDayDirectoryEntryEnumerable final :
			public base::IEnumerable<base::DirectoryEntry const>
		{
		private:
			class Enumerator final :
				public base::IEnumerator<base::DirectoryEntry const>
			{
			private:
				YearMonthDayDirectoryEntryEnumerable &_enumerable;

				///
				/// @brief 用来迭代基路径的迭代器。
				///
				///
				std::shared_ptr<base::IEnumerator<base::DirectoryEntry const>> _base_dir_iterator;
				std::shared_ptr<base::IEnumerator<base::DirectoryEntry const>> _year_dir_iterator;
				std::shared_ptr<base::IEnumerator<base::DirectoryEntry const>> _month_dir_iterator;
				std::shared_ptr<base::IEnumerator<base::DirectoryEntry const>> _day_dir_iterator;
				std::shared_ptr<base::IEnumerator<base::DirectoryEntry const>> _file_iterator;

				///
				/// @brief 移动到下一年。
				///
				/// @warning 只能被 MoveToNextMonth 调用。
				///
				///
				void MoveToNextYear()
				{
					if (_base_dir_iterator == nullptr)
					{
						base::filesystem::DirectoryEntryEnumerable enumerable{_enumerable._base_path};
						_base_dir_iterator = enumerable.GetEnumerator();
						return;
					}

					if (_base_dir_iterator->IsEnd())
					{
						// 没有下一个年份了
						return;
					}

					_base_dir_iterator->Add();
				}

				void MoveToNextMonth()
				{
					if (_year_dir_iterator == nullptr || _year_dir_iterator->IsEnd())
					{
						// _year_dir_iterator 为空，还没有迭代过年份，或者 _year_dir_iterator 已经迭代
						// 完了，需要切换到下一个年份目录然后重新构造 _year_dir_iterator.
						MoveToNextYear();
						if (_base_dir_iterator->IsEnd())
						{
							return;
						}

						base::DirectoryEntry entry = _base_dir_iterator->CurrentValue();
						base::Path year_dir_path = entry.Path();
						base::filesystem::DirectoryEntryEnumerable enumerable{year_dir_path};
						_year_dir_iterator = enumerable.GetEnumerator();
						return;
					}

					_year_dir_iterator->Add();
				}

				void MoveToNextDay()
				{
					if (_month_dir_iterator == nullptr || _month_dir_iterator->IsEnd())
					{
						MoveToNextMonth();
						if (_year_dir_iterator->IsEnd())
						{
							return;
						}

						base::DirectoryEntry entry = _year_dir_iterator->CurrentValue();
						base::Path month_dir_path = entry.Path();
						base::filesystem::DirectoryEntryEnumerable enumerable{month_dir_path};
						_month_dir_iterator = enumerable.GetEnumerator();
						return;
					}

					_month_dir_iterator->Add();
				}

			public:
				Enumerator(YearMonthDayDirectoryEntryEnumerable &enumerable)
					: _enumerable(enumerable)
				{
				}

				///
				/// @brief 迭代器当前是否指向尾后元素。
				///
				/// @return
				///
				virtual bool IsEnd() const override
				{
					return _year_dir_iterator->IsEnd();
				}

				///
				/// @brief 获取当前值的引用。
				///
				/// @return
				///
				virtual base::DirectoryEntry const &CurrentValue() override
				{
					return _year_dir_iterator->CurrentValue();
				}

				///
				/// @brief 递增迭代器的位置。
				///
				///
				virtual void Add() override
				{
				}
			};

		private:
			///
			/// @brief “基路径/年/月/日/文件” 中的 “基路径”。
			///
			///
			base::Path _base_path;

			///
			/// @brief 过滤的日期时间范围。迭代时范围外的文件将不会获取到。
			///
			///
			base::ClosedInterval<base::DateTime> _date_time_range;

		public:
			YearMonthDayDirectoryEntryEnumerable(base::Path const &base_path,
												 base::ClosedInterval<base::DateTime> const &date_time_range)
			{
				_base_path = base_path;
				_date_time_range = date_time_range;
			}

			using base::IEnumerable<base::DirectoryEntry const>::GetEnumerator;

			///
			/// @brief 获取非 const 迭代器
			///
			/// @return
			///
			virtual std::shared_ptr<base::IEnumerator<base::DirectoryEntry const>> GetEnumerator() override
			{
				return std::shared_ptr<Enumerator>{new Enumerator{*this}};
			}
		};

	} // namespace filesystem
} // namespace base
