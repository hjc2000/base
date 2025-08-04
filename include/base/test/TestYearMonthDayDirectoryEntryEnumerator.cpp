#include "TestYearMonthDayDirectoryEntryEnumerator.h" // IWYU pragma: keep
#include "base/container/iterator/Enumerable.h"
#include "base/filesystem/DirectoryEntry.h"
#include "base/filesystem/Path.h"
#include "base/filesystem/YearMonthDayDirectoryEntryEnumerator.h"
#include "base/math/interval/Interval.h"
#include "base/time/DateTime.h"
#include "base/time/UtcHourOffset.h"
#include <iostream>

#if HAS_THREAD

void base::test::TestYearMonthDayDirectoryEntryEnumerator()
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

	base::Path test_path{__test_resource_pasth};
	test_path += "TestYearMonthDayDirectoryEntryEnumerator";

	base::filesystem::YearMonthDayDirectoryEntryEnumerator enumerator{
		test_path,
		interval,
		base::UtcHourOffset{8},
	};

	for (base::DirectoryEntry const &entry : base::Enumerable{enumerator})
	{
		std::cout << entry.Path() << std::endl;
	}
}

#endif // HAS_THREAD
