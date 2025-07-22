#include "base/math/InertialElement.h"
#include "base/math/Int64Fraction.h"
#include "base/modbus/ModbusCrc16.h"
#include "base/modbus/WritingRecordsRequestWriter.h"
#include "base/stream/memcmp.h"
#include "base/stream/ReadOnlySpan.h"
#include "base/string/ToHexString.h"
#include <array>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <stdlib.h>

int main()
{
	{
		base::InertialElement<base::Int64Fraction> inertial_element{
			base::Int64Fraction{1, static_cast<int64_t>(1e6)},
			base::Int64Fraction{1, static_cast<int64_t>(1e9)},
			base::Int64Fraction{1, static_cast<int64_t>(1) << 32},
		};

		std::cout << "Kx: " << inertial_element.Kx() << std::endl;
		std::cout << "Ky: " << inertial_element.Ky() << std::endl;

		for (int i = 0; i < 10000; i++)
		{
			inertial_element.Input(100);
		}

		std::cout << base::floor(inertial_element.CurrentOutput()) << std::endl;
	}

	{
		constexpr uint8_t buffer_a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
		constexpr uint8_t buffer_b[10] = {2, 2, 3, 4, 5, 6, 7, 8, 9, 10};

		base::ReadOnlySpan span_a{buffer_a, sizeof(buffer_a)};
		base::ReadOnlySpan span_b{buffer_b, sizeof(buffer_b)};
		bool compare_result = span_a < span_b;
		constexpr int32_t result = base::memcmp(buffer_a, buffer_b, 10);
		std::cout << compare_result << std::endl;
		std::cout << result << std::endl;
	}

	{
		constexpr std::array<uint8_t, 6> arr{0x01, 0x03, 0x00, 0x00, 0x00, 0x01};
		base::modbus::ModbusCrc16 crc{};
		crc.Add(arr);
		std::cout << base::ToHexString(crc.RegisterValue()) << std::endl;
	}

	{
		uint8_t buffer[1024]{};
		base::Span span{buffer, sizeof(buffer)};
		base::modbus::WritingRecordsRequestWriter writer{span};
		writer.WriteStationNumber(1);
		writer.WriteFunctionCode();
		writer.WriteStartAddress(0x4050);
		writer.WriteRecordCount(2);
		writer.WriteDataByteCount(4);
		writer.WriteData<uint32_t>(10000);
		writer.WriteCrc();

		base::ToHexStringOption option{};
		option.with_0x_prefix = false;
		option.width = 2;
		for (uint8_t b : writer.SpanForSending())
		{
			std::cout << base::ToHexString(b, option) << " ";
		}
	}
}
