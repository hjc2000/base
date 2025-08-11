#include "TestMemoryMapFileList.h" // IWYU pragma: keep
#include "base/container/MemoryMapFileList.h"

void bsae::test::TestMemoryMapFileList()
{
	base::MemoryMapFileList<int> list{"test.map"};
}
