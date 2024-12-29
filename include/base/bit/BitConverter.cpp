#include "BitConverter.h"
#include <base/string/define.h>
using namespace base;

#pragma region 转数字类型

uint16_t base::BitConverter::ToUInt16(base::ReadOnlySpan const &span)
{
	uint16_t ret;
	if (span.Size() < static_cast<int32_t>(sizeof(ret)))
	{
		throw std::invalid_argument{CODE_POS_STR + "传入的 span 太小。"};
	}

	std::copy(span.Buffer(),
			  span.Buffer() + static_cast<int32_t>(sizeof(ret)),
			  reinterpret_cast<uint8_t *>(&ret));

	return ret;
}

int16_t base::BitConverter::ToInt16(base::ReadOnlySpan const &span)
{
	return static_cast<int16_t>(ToUInt16(span));
}

uint16_t base::BitConverter::ToUInt16(uint8_t high, uint8_t low)
{
	return (static_cast<uint16_t>(high) << 8) | low;
}

uint32_t base::BitConverter::ToUInt32(base::ReadOnlySpan const &span)
{
	uint32_t ret;

	if (span.Size() < static_cast<int32_t>(sizeof(ret)))
	{
		throw std::invalid_argument{CODE_POS_STR + "传入的 span 太小。"};
	}

	std::copy(span.Buffer(),
			  span.Buffer() + static_cast<int32_t>(sizeof(ret)),
			  reinterpret_cast<uint8_t *>(&ret));

	return ret;
}

int32_t base::BitConverter::ToInt32(base::ReadOnlySpan const &span)
{
	return static_cast<int32_t>(ToUInt32(span));
}

uint32_t base::BitConverter::ToUInt32(uint8_t b3, uint8_t b2, uint8_t b1, uint8_t b0)
{
	uint16_t high = ToUInt16(b3, b2);
	uint16_t low = ToUInt16(b1, b0);
	return ToUInt32(high, low);
}

uint32_t base::BitConverter::ToUInt32(uint16_t high, uint16_t low)
{
	return (static_cast<uint32_t>(high) << 16) | low;
}

uint64_t base::BitConverter::ToUInt64(base::ReadOnlySpan const &span)
{
	uint64_t ret;

	if (span.Size() < static_cast<int32_t>(sizeof(ret)))
	{
		throw std::invalid_argument{CODE_POS_STR + "传入的 span 太小。"};
	}

	std::copy(span.Buffer(),
			  span.Buffer() + static_cast<int32_t>(sizeof(ret)),
			  reinterpret_cast<uint8_t *>(&ret));

	return ret;
}

int64_t base::BitConverter::ToInt64(base::ReadOnlySpan const &span)
{
	return static_cast<int64_t>(ToUInt64(span));
}

float base::BitConverter::ToFloat(base::ReadOnlySpan const &span)
{
	float ret;

	if (span.Size() < static_cast<int32_t>(sizeof(ret)))
	{
		throw std::invalid_argument{CODE_POS_STR + "传入的 span 太小。"};
	}

	std::copy(span.Buffer(),
			  span.Buffer() + static_cast<int32_t>(sizeof(ret)),
			  reinterpret_cast<uint8_t *>(&ret));

	return ret;
}

double base::BitConverter::ToDouble(base::ReadOnlySpan const &span)
{
	double ret;

	if (span.Size() < static_cast<int32_t>(sizeof(ret)))
	{
		throw std::invalid_argument{CODE_POS_STR + "传入的 span 太小。"};
	}

	std::copy(span.Buffer(),
			  span.Buffer() + static_cast<int32_t>(sizeof(ret)),
			  reinterpret_cast<uint8_t *>(&ret));

	return ret;
}

#pragma endregion

#pragma region 转缓冲区

void base::BitConverter::GetBytes(uint16_t value, base::Span const &span)
{
	if (span.Size() < static_cast<int32_t>(sizeof(value)))
	{
		throw std::invalid_argument{CODE_POS_STR + "传入的 span 太小。"};
	}

	uint8_t *buffer = reinterpret_cast<uint8_t *>(&value);
	std::copy(buffer, buffer + static_cast<int32_t>(sizeof(value)), span.Buffer());
}

void base::BitConverter::GetBytes(int16_t value, base::Span const &span)
{
	if (span.Size() < static_cast<int32_t>(sizeof(value)))
	{
		throw std::invalid_argument{CODE_POS_STR + "传入的 span 太小。"};
	}

	uint8_t *buffer = reinterpret_cast<uint8_t *>(&value);
	std::copy(buffer, buffer + static_cast<int32_t>(sizeof(value)), span.Buffer());
}

void base::BitConverter::GetBytes(uint32_t value, base::Span const &span)
{
	if (span.Size() < static_cast<int32_t>(sizeof(value)))
	{
		throw std::invalid_argument{CODE_POS_STR + "传入的 span 太小。"};
	}

	uint8_t *buffer = reinterpret_cast<uint8_t *>(&value);
	std::copy(buffer, buffer + static_cast<int32_t>(sizeof(value)), span.Buffer());
}

void base::BitConverter::GetBytes(int32_t value, base::Span const &span)
{
	if (span.Size() < static_cast<int32_t>(sizeof(value)))
	{
		throw std::invalid_argument{CODE_POS_STR + "传入的 span 太小。"};
	}

	uint8_t *buffer = reinterpret_cast<uint8_t *>(&value);
	std::copy(buffer, buffer + static_cast<int32_t>(sizeof(value)), span.Buffer());
}

void base::BitConverter::GetBytes(uint64_t value, base::Span const &span)
{
	if (span.Size() < static_cast<int32_t>(sizeof(value)))
	{
		throw std::invalid_argument{CODE_POS_STR + "传入的 span 太小。"};
	}

	uint8_t *buffer = reinterpret_cast<uint8_t *>(&value);
	std::copy(buffer, buffer + static_cast<int32_t>(sizeof(value)), span.Buffer());
}

void base::BitConverter::GetBytes(int64_t value, base::Span const &span)
{
	if (span.Size() < static_cast<int32_t>(sizeof(value)))
	{
		throw std::invalid_argument{CODE_POS_STR + "传入的 span 太小。"};
	}

	uint8_t *buffer = reinterpret_cast<uint8_t *>(&value);
	std::copy(buffer, buffer + static_cast<int32_t>(sizeof(value)), span.Buffer());
}

void base::BitConverter::GetBytes(float value, base::Span const &span)
{
	if (span.Size() < static_cast<int32_t>(sizeof(value)))
	{
		throw std::invalid_argument{CODE_POS_STR + "传入的 span 太小。"};
	}

	uint8_t *buffer = reinterpret_cast<uint8_t *>(&value);
	std::copy(buffer, buffer + static_cast<int32_t>(sizeof(value)), span.Buffer());
}

void base::BitConverter::GetBytes(double value, base::Span const &span)
{
	if (span.Size() < static_cast<int32_t>(sizeof(value)))
	{
		throw std::invalid_argument{CODE_POS_STR + "传入的 span 太小。"};
	}

	uint8_t *buffer = reinterpret_cast<uint8_t *>(&value);
	std::copy(buffer, buffer + static_cast<int32_t>(sizeof(value)), span.Buffer());
}

#pragma endregion
