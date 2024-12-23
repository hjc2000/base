#include <array>
#include <base/bit/BitConverter.h>
#include <base/container/Array.h>
#include <base/container/Dictionary.h>
#include <base/container/List.h>
#include <base/net/IPAddress.h>
#include <base/net/Mac.h>
#include <base/sfinae/Equal.h>
#include <base/stream/MemoryStream.h>
#include <base/string/String.h>
#include <base/string/ToHexString.h>
#include <format>
#include <iostream>

int main()
{
	base::String str{"123,456,789   \r\n\t "};
	std::cout << str.Length() << std::endl;
	str = str.TrimEnd();
	std::cout << str.Length() << std::endl;

	base::List<std::string> string_list = str.Split(',');
	for (auto &str : string_list)
	{
		std::cout << str << std::endl;
	}
}
