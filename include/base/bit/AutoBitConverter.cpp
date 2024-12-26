#include "AutoBitConverter.h"
#include <algorithm>
#include <base/bit/BitConverter.h>

using namespace base;

base::AutoBitConverter::AutoBitConverter(std::endian remote_endian)
	: _remote_endian(remote_endian)
{
}

bool base::AutoBitConverter::ShouldReverse() const
{
	return std::endian::native != _remote_endian;
}

#pragma region 转成数字类型

uint16_t base::AutoBitConverter::ToUInt16(base::ReadOnlySpan const &span) const
{
	uint16_t ret = BitConverter::ToUInt16(span);
	if (ShouldReverse())
	{
		uint8_t *p = reinterpret_cast<uint8_t *>(&ret);
		std::reverse(p, p + sizeof(ret));
	}

	return ret;
}

int16_t base::AutoBitConverter::ToInt16(base::ReadOnlySpan const &span) const
{
	int16_t ret = BitConverter::ToInt16(span);
	if (ShouldReverse())
	{
		uint8_t *p = reinterpret_cast<uint8_t *>(&ret);
		std::reverse(p, p + sizeof(ret));
	}

	return ret;
}

uint32_t base::AutoBitConverter::ToUInt32(base::ReadOnlySpan const &span) const
{
	uint32_t ret = BitConverter::ToUInt32(span);
	if (ShouldReverse())
	{
		uint8_t *p = reinterpret_cast<uint8_t *>(&ret);
		std::reverse(p, p + sizeof(ret));
	}

	return ret;
}

int32_t base::AutoBitConverter::ToInt32(base::ReadOnlySpan const &span) const
{
	int32_t ret = BitConverter::ToInt32(span);
	if (ShouldReverse())
	{
		uint8_t *p = reinterpret_cast<uint8_t *>(&ret);
		std::reverse(p, p + sizeof(ret));
	}

	return ret;
}

uint64_t base::AutoBitConverter::ToUInt64(base::ReadOnlySpan const &span) const
{
	uint64_t ret = BitConverter::ToUInt64(span);
	if (ShouldReverse())
	{
		uint8_t *p = reinterpret_cast<uint8_t *>(&ret);
		std::reverse(p, p + sizeof(ret));
	}

	return ret;
}

int64_t base::AutoBitConverter::ToInt64(base::ReadOnlySpan const &span) const
{
	int64_t ret = BitConverter::ToInt64(span);
	if (ShouldReverse())
	{
		uint8_t *p = reinterpret_cast<uint8_t *>(&ret);
		std::reverse(p, p + sizeof(ret));
	}

	return ret;
}

float base::AutoBitConverter::ToFloat(base::ReadOnlySpan const &span) const
{
	float ret = BitConverter::ToFloat(span);
	if (ShouldReverse())
	{
		uint8_t *p = reinterpret_cast<uint8_t *>(&ret);
		std::reverse(p, p + sizeof(ret));
	}

	return ret;
}

double base::AutoBitConverter::ToDouble(base::ReadOnlySpan const &span) const
{
	double ret = BitConverter::ToDouble(span);
	if (ShouldReverse())
	{
		uint8_t *p = reinterpret_cast<uint8_t *>(&ret);
		std::reverse(p, p + sizeof(ret));
	}

	return ret;
}

#pragma endregion

#pragma region 转到缓冲区

void base::AutoBitConverter::GetBytes(uint16_t value, base::Span const &span) const
{
	base::BitConverter::GetBytes(value, span);
	if (ShouldReverse())
	{
		std::reverse(span.Buffer(), span.Buffer() + sizeof(value));
	}
}

void base::AutoBitConverter::GetBytes(int16_t value, base::Span const &span) const
{
	base::BitConverter::GetBytes(value, span);
	if (ShouldReverse())
	{
		std::reverse(span.Buffer(), span.Buffer() + sizeof(value));
	}
}

void base::AutoBitConverter::GetBytes(uint32_t value, base::Span const &span) const
{
	base::BitConverter::GetBytes(value, span);
	if (ShouldReverse())
	{
		std::reverse(span.Buffer(), span.Buffer() + sizeof(value));
	}
}

void base::AutoBitConverter::GetBytes(int32_t value, base::Span const &span) const
{
	base::BitConverter::GetBytes(value, span);
	if (ShouldReverse())
	{
		std::reverse(span.Buffer(), span.Buffer() + sizeof(value));
	}
}

void base::AutoBitConverter::GetBytes(uint64_t value, base::Span const &span) const
{
	base::BitConverter::GetBytes(value, span);
	if (ShouldReverse())
	{
		std::reverse(span.Buffer(), span.Buffer() + sizeof(value));
	}
}

void base::AutoBitConverter::GetBytes(int64_t value, base::Span const &span) const
{
	base::BitConverter::GetBytes(value, span);
	if (ShouldReverse())
	{
		std::reverse(span.Buffer(), span.Buffer() + sizeof(value));
	}
}

void base::AutoBitConverter::GetBytes(float value, base::Span const &span) const
{
	base::BitConverter::GetBytes(value, span);
	if (ShouldReverse())
	{
		std::reverse(span.Buffer(), span.Buffer() + sizeof(value));
	}
}

void base::AutoBitConverter::GetBytes(double value, base::Span const &span) const
{
	base::BitConverter::GetBytes(value, span);
	if (ShouldReverse())
	{
		std::reverse(span.Buffer(), span.Buffer() + sizeof(value));
	}
}

#pragma endregion
