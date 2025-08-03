#include "YearMonthDayDirectoryEntryEnumerable.h" // IWYU pragma: keep
#include "base/filesystem/YearMonthDayDirectoryEntryEnumerator.h"
#include "base/IDisposable.h"

std::shared_ptr<base::IEnumerator<base::DirectoryEntry const>> base::filesystem::YearMonthDayDirectoryEntryEnumerable::GetEnumerator()
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
