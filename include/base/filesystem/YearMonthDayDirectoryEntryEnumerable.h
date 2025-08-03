#pragma once
#include "base/container/iterator/IEnumerable.h"
#include "base/container/iterator/IEnumerator.h"
#include "base/filesystem/DirectoryEntry.h"
#include "base/filesystem/Path.h"
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
			public base::IEnumerable<base::DirectoryEntry const>,
			public IDisposable
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

			~YearMonthDayDirectoryEntryEnumerable()
			{
				Dispose();
			}

			///
			/// @brief 处置对象，让对象准备好结束生命周期。类似于进入 “准备后事” 的状态。
			///
			/// @note 注意，对象并不是析构了，并不是完全无法访问，它仍然允许访问，仍然能执行一些
			/// 符合 “准备后事” 的工作。
			///
			virtual void Dispose() override
			{
				if (_disposed)
				{
					return;
				}

				_disposed = true;
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
