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
	base::String str{"\n\n\t ,, 123,,456,789,,   \n\n"};
	std::cout << str << std::endl;
	str = str.Trim();
	std::cout << str << std::endl;

	base::List<base::String> string_list = str.Split(',');
	int i = 0;
	for (auto &str : string_list)
	{
		std::cout << std::format("{}:  {}",
								 i++,
								 str.StdString())
				  << std::endl;
	}
}
