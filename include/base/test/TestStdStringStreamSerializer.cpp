#include "TestStdStringStreamSerializer.h" // IWYU pragma: keep
#include "base/filesystem/file.h"
#include "base/filesystem/filesystem.h"
#include "base/string/String.h"
#include <iostream>

#if HAS_THREAD

void base::test::TestStdStringStreamSerializer()
{
	base::String str{"0123456789"};

	base::filesystem::EnsureDirectory("test");
	std::shared_ptr<base::Stream> fs = base::file::OpenOrCreate("test/TestStdStringStreamSerializer.bin");
	str.SerializeIntoStream(*fs);

	fs->SetPosition(0);
	str.DeserializeFromStream(*fs);
	std::cout << str << std::endl;
}

#endif // HAS_THREAD
