#pragma once
#include "base/filesystem/file.h"
#include "base/filesystem/filesystem.h"
#include "base/string/String.h"
#include <iostream>

namespace base::test
{
	inline void TestStdStringStreamSerializer()
	{
		base::String str{"0123456789"};

		base::filesystem::EnsureDirectory("test");
		std::shared_ptr<base::Stream> fs = base::file::OpenOrCreate("test/TestStdStringStreamSerializer.bin");
		str.SerializeIntoStream(*fs);

		fs->SetPosition(0);
		str.DeserializeFromStream(*fs);
		std::cout << str << std::endl;
	}

} // namespace base::test
