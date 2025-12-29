#pragma once
#include "base/net/IPAddress.h"
#include <iostream>

namespace base::test
{
	inline void TestIpAddress()
	{
		{
			base::IPAddress ip{
				std::endian::big,
				{
					192,
					168,
					1,
					1,
				},
			};

			std::cout << ip << std::endl;
		}

		{
			base::IPAddress ip{
				std::endian::big,
				{
					0x20, 0x01, // 2001
					0x0d, 0xb8, // 0db8
					0x85, 0xa3, // 85a3
					0x00, 0x00, // 0000
					0x00, 0x00, // 0000
					0x8a, 0x2e, // 8a2e
					0x03, 0x70, // 0370
					0x73, 0x34  // 7334
				},
			};

			std::cout << ip << std::endl;
		}
	}

} // namespace base::test
