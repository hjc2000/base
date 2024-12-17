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

class Test
{
public:
	bool operator==(Test const &o) const
	{
		return this == &o;
	}
};

int main()
{
	Test t1;
	Test t2;
	std::cout << base::Equal(t1, t2) << std::endl;
}
