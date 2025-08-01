#pragma once
#include "base/filesystem/Path.h"
#include "base/math/Interval.h"
#include "base/time/DateTime.h"

namespace base
{
	namespace filesystem
	{
		///
		/// @brief 用于迭代像 “基路径/年/月/日/文件” 这种目录结构的最后一层的文件。
		///
		///
		class YearMonthDayDirectoryEntryEnumerable
		{
		public:
			YearMonthDayDirectoryEntryEnumerable(base::Path const &base_path,
												 base::ClosedInterval<base::DateTime> const &date_time_range)
			{
			}
		};

	} // namespace filesystem
} // namespace base
