#pragma once
#include "base/container/iterator/IEnumerable.h"
#include "base/container/iterator/IEnumerator.h"
#include "base/filesystem/DirectoryEntry.h"
#include "base/filesystem/Path.h"
#include "base/filesystem/YearMonthDayDirectoryEntryEnumerator.h"
#include "base/IDisposable.h"
#include "base/math/interval/Interval.h"
#include "base/time/DateTime.h"
#include "base/time/UtcHourOffset.h"

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
			class Enumerator;

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
			base::Interval<base::DateTime> _date_time_range;

			base::UtcHourOffset _utc_hour_offset;

			bool _disposed = false;

		public:
			///
			/// @brief
			///
			/// @param base_path
			/// @param date_time_range
			/// @param utc_hour_offset 文件系统中的 年/月/日 目录代表的时间是什么时区的。
			///
			YearMonthDayDirectoryEntryEnumerable(base::Path const &base_path,
												 base::Interval<base::DateTime> const &date_time_range,
												 base::UtcHourOffset const &utc_hour_offset)
			{
				_base_path = base_path;
				_date_time_range = date_time_range;
				_utc_hour_offset = utc_hour_offset;
			}

			using base::IEnumerable<base::DirectoryEntry const>::GetEnumerator;

			///
			/// @brief 获取非 const 迭代器
			///
			/// @return
			///
			virtual std::shared_ptr<base::IEnumerator<base::DirectoryEntry const>> GetEnumerator() override
			{
				if (_disposed)
				{
					throw base::ObjectDisposedException{};
				}

				return std::shared_ptr<base::filesystem::YearMonthDayDirectoryEntryEnumerator>{new base::filesystem::YearMonthDayDirectoryEntryEnumerator{
					_base_path,
					_date_time_range,
					_utc_hour_offset,
				}};
			}
		};

	} // namespace filesystem
} // namespace base
