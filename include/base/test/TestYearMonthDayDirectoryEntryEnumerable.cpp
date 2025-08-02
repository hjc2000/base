#include "TestYearMonthDayDirectoryEntryEnumerable.h" // IWYU pragma: keep
#include "base/filesystem/DirectoryEntry.h"
#include "base/filesystem/Path.h"
#include "base/filesystem/YearMonthDayDirectoryEntryEnumerable.h"
#include "base/math/Interval.h"
#include "base/time/DateTime.h"
#include "base/time/UtcHourOffset.h"
#include <iostream>

#if HAS_THREAD

void base::test::TestYearMonthDayDirectoryEntryEnumerable()
{
	base::ClosedInterval<base::DateTime> interval{
		base::DateTime{
			base::UtcHourOffset{8},
			2023,
			8,
			1,
			0,
			0,
			0,
			0,
		},
		base::DateTime{
			base::UtcHourOffset{8},
			2025,
			1,
			1,
			0,
			0,
			0,
			0,
		},
	};

	base::filesystem::YearMonthDayDirectoryEntryEnumerable enumerable{
		base::Path{"C:/Users/huang/disk/ti600_2TB/.temp"},
		interval,
		base::UtcHourOffset{8},
	};

	for (base::DirectoryEntry const &entry : enumerable)
	{
		std::cout << entry.Path() << std::endl;
	}
}

#endif // HAS_THREAD
