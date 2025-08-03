#include "TestYearMonthDayDirectoryEntryEnumerable.h" // IWYU pragma: keep
#include "base/filesystem/DirectoryEntry.h"
#include "base/filesystem/Path.h"
#include "base/filesystem/YearMonthDayDirectoryEntryEnumerable.h"
#include "base/math/interval/Interval.h"
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

	// 把本项目的 test 目录中的 TestYearMonthDayDirectoryEntryEnumerable 目录拷贝到合适的
	// 地方，然后把下面的路径改一下，就可以测试了。
	base::filesystem::YearMonthDayDirectoryEntryEnumerable enumerable{
		base::Path{"C:/Users/huang/disk/ti600_2TB/.temp/TestYearMonthDayDirectoryEntryEnumerable"},
		interval,
		base::UtcHourOffset{8},
	};

	for (base::DirectoryEntry const &entry : enumerable)
	{
		std::cout << entry.Path() << std::endl;
	}
}

#endif // HAS_THREAD
