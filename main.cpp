#include <array>
#include <base/bit/BitConverter.h>
#include <base/container/Array.h>
#include <base/container/Dictionary.h>
#include <base/container/List.h>
#include <base/net/IPAddress.h>
#include <base/net/Mac.h>
#include <base/sfinae/Equal.h>
#include <base/stream/MemoryStream.h>
#include <base/string/StringHelper.h>
#include <base/string/ToHexString.h>
#include <format>
#include <iostream>

int main()
{
	std::vector<uint8_t> buffer;
	for (int i = 0; i < 16 * 16; i++)
	{
		buffer.push_back(i);
	}

	base::ToHexStringOption options;
	options.width = 2;
	std::cout << base::ToHexString(buffer.data(), buffer.size(), options) << std::endl;
}
