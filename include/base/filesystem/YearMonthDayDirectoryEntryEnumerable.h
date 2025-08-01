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
				std::shared_ptr<base::IEnumerator<base::DirectoryEntry const>> _year_dir_iterator;
				std::shared_ptr<base::IEnumerator<base::DirectoryEntry const>> _month_dir_iterator;
				std::shared_ptr<base::IEnumerator<base::DirectoryEntry const>> _day_dir_iterator;
				std::shared_ptr<base::IEnumerator<base::DirectoryEntry const>> _file_iterator;

				void MoveToNextYear()
				{
				}

			public:
				Enumerator(YearMonthDayDirectoryEntryEnumerable &enumerable)
					: _enumerable(enumerable)
				{
					base::filesystem::DirectoryEntryEnumerable dir_enumerable{_enumerable._base_path};
					_year_dir_iterator = dir_enumerable.GetEnumerator();
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
