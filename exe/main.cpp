#include "base/bit/bit.h"
#include "base/math/Fraction.h"
#include "base/stream/BlockingCircleBufferMemoryStream.h"
#include "base/stream/ReadOnlySpan.h"
#include "base/stream/Span.h"
#include "base/string/Parse.h"
#include "base/string/ToHexString.h"
#include "base/task/delay.h"
#include "base/task/task.h"
#include "base/wrapper/number-wrapper.h"
#include <chrono>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <numbers>
#include <stdlib.h>

int main()
{
	{
		base::Fraction f{base::Double{std::numbers::pi}};
		constexpr int precision = 512;

		std::cout << "分数: " << f << std::endl;

		std::cout << "std::numbers::pi: \t\t"
				  << std::setprecision(precision)
				  << std::numbers::pi
				  << std::endl;

		std::cout << "分数表示的 pi 转为 double: \t"
				  << std::setprecision(precision)
				  << static_cast<double>(f)
				  << std::endl;

		std::cout << "误差: "
				  << std::setprecision(precision)
				  << static_cast<double>(f) - std::numbers::pi
				  << std::endl;
	}

	base::test::test_parse_double();

	{
		constexpr uint64_t a = static_cast<uint64_t>(0x123) << 52;
		constexpr uint64_t b = base::bit::ReadBits(a, 52, 63);
		std::cout << base::ToHexString(a) << std::endl;
		std::cout << base::ToHexString(b) << std::endl;
	}

	{
		base::BlockingCircleBufferMemoryStream mstream{100};

		base::task::run([&]()
						{
							uint8_t buffer[256]{};
							while (true)
							{
								int32_t have_read = mstream.Read(base::Span{buffer, sizeof(buffer)});
								for (int32_t i = 0; i < have_read; i++)
								{
									std::cout << std::to_string(buffer[i]) << ", ";
								}

								std::cout << std::endl;
								base::task::Delay(std::chrono::milliseconds{1000});
							}
						});

		uint8_t count = 0;
		uint8_t buffer[117]{};
		while (true)
		{
			for (size_t i = 0; i < sizeof(buffer); i++)
			{
				buffer[i] = count++;
			}

			mstream.Write(base::ReadOnlySpan{buffer, sizeof(buffer)});
		}
	}
}
