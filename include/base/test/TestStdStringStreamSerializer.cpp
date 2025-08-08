#include "TestStdStringStreamSerializer.h" // IWYU pragma: keep
#include "base/bit/StdStringStreamSerializer.h"
#include "base/filesystem/filesystem.h"
#include "base/filesystem/IFileStream.h"
#include <iostream>
#include <string>

#if HAS_THREAD

void base::test::TestStdStringStreamSerializer()
{
	std::string str{"0123456789"};
	base::StdStringStreamSerializer serializer{str};

	base::filesystem::EnsureDirectory("test");
	std::shared_ptr<base::IFileStream> fs = base::file::OpenOrCreate("test/TestStdStringStreamSerializer.bin");
	serializer.SerializeIntoStream(*fs);

	fs->SetPosition(0);
	serializer.DeserializeFromStream(*fs);
	std::cout << str << std::endl;
}

#endif // HAS_THREAD
