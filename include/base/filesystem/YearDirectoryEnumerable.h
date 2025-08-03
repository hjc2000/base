#pragma once
#include "base/container/iterator/IEnumerable.h"
#include "base/container/iterator/IEnumerator.h"
#include "base/filesystem/DirectoryEntry.h"
#include "base/filesystem/Path.h"
#include "base/math/interval/Interval.h"
#include "base/time/DateTime.h"
#include "base/time/UtcHourOffset.h"

namespace base
{
	namespace filesystem
	{
		class YearDirectoryEnumerable final :
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
			/// @brief 过滤的日期时间范围。迭代时范围外的年目录将不会获取到。
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
			/// @param utc_hour_offset 文件系统中年目录的 UTC 偏移量是多少。
			///
			YearDirectoryEnumerable(base::Path const &base_path,
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
			virtual std::shared_ptr<base::IEnumerator<base::DirectoryEntry const>> GetEnumerator() override;
		};

	} // namespace filesystem
} // namespace base
