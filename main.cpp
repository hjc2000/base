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
	{
		base::IPAddress ip{"192.168.1.3"};
		std::cout << ip << std::endl;
	}

	{
		base::IPAddress ip{"2001:0db8:85a3:0000:0000:8a2e:0370:7334"};
		std::cout << ip << std::endl;
	}
}
