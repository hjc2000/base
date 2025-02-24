#include "AutoBitConverter.h"
#include <algorithm>
#include <base/bit/BitConverter.h>
#include <base/string/define.h>

base::AutoBitConverter::AutoBitConverter(std::endian remote_endian)
	: _remote_endian(remote_endian)
{
}

bool base::AutoBitConverter::ShouldReverse() const
{
	return std::endian::native != _remote_endian;
}

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

uint16_t base::AutoBitConverter::ToUInt16(base::Stream &stream) const
{
	uint8_t buffer[sizeof(uint16_t)];
	int32_t have_read = stream.ReadExactly(buffer, 0, sizeof(buffer));
	if (have_read < static_cast<int32_t>(sizeof(buffer)))
	{
		throw std::runtime_error{CODE_POS_STR + "流中没有足够的字节。"};
	}

	return ToUInt16(base::Span{buffer, sizeof(buffer)});
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

int16_t base::AutoBitConverter::ToInt16(base::Stream &stream) const
{
	uint8_t buffer[sizeof(int16_t)];
	int32_t have_read = stream.ReadExactly(buffer, 0, sizeof(buffer));
	if (have_read < static_cast<int32_t>(sizeof(buffer)))
	{
		throw std::runtime_error{CODE_POS_STR + "流中没有足够的字节。"};
	}

	return ToInt16(base::Span{buffer, sizeof(buffer)});
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

uint32_t base::AutoBitConverter::ToUInt32(base::Stream &stream) const
{
	uint8_t buffer[sizeof(uint32_t)];
	int32_t have_read = stream.ReadExactly(buffer, 0, sizeof(buffer));
	if (have_read < static_cast<int32_t>(sizeof(buffer)))
	{
		throw std::runtime_error{CODE_POS_STR + "流中没有足够的字节。"};
	}

	return ToUInt32(base::Span{buffer, sizeof(buffer)});
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

int32_t base::AutoBitConverter::ToInt32(base::Stream &stream) const
{
	uint8_t buffer[sizeof(int32_t)];
	int32_t have_read = stream.ReadExactly(buffer, 0, sizeof(buffer));
	if (have_read < static_cast<int32_t>(sizeof(buffer)))
	{
		throw std::runtime_error{CODE_POS_STR + "流中没有足够的字节。"};
	}

	return ToInt32(base::Span{buffer, sizeof(buffer)});
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

uint64_t base::AutoBitConverter::ToUInt64(base::Stream &stream) const
{
	uint8_t buffer[sizeof(uint64_t)];
	int32_t have_read = stream.ReadExactly(buffer, 0, sizeof(buffer));
	if (have_read < static_cast<int32_t>(sizeof(buffer)))
	{
		throw std::runtime_error{CODE_POS_STR + "流中没有足够的字节。"};
	}

	return ToUInt64(base::Span{buffer, sizeof(buffer)});
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

int64_t base::AutoBitConverter::ToInt64(base::Stream &stream) const
{
	uint8_t buffer[sizeof(int64_t)];
	int32_t have_read = stream.ReadExactly(buffer, 0, sizeof(buffer));
	if (have_read < static_cast<int32_t>(sizeof(buffer)))
	{
		throw std::runtime_error{CODE_POS_STR + "流中没有足够的字节。"};
	}

	return ToInt64(base::Span{buffer, sizeof(buffer)});
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

float base::AutoBitConverter::ToFloat(base::Stream &stream) const
{
	uint8_t buffer[sizeof(float)];
	int32_t have_read = stream.ReadExactly(buffer, 0, sizeof(buffer));
	if (have_read < static_cast<int32_t>(sizeof(buffer)))
	{
		throw std::runtime_error{CODE_POS_STR + "流中没有足够的字节。"};
	}

	return ToFloat(base::Span{buffer, sizeof(buffer)});
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

double base::AutoBitConverter::ToDouble(base::Stream &stream) const
{
	uint8_t buffer[sizeof(double)];
	int32_t have_read = stream.ReadExactly(buffer, 0, sizeof(buffer));
	if (have_read < static_cast<int32_t>(sizeof(buffer)))
	{
		throw std::runtime_error{CODE_POS_STR + "流中没有足够的字节。"};
	}

	return ToDouble(base::Span{buffer, sizeof(buffer)});
}

void base::AutoBitConverter::GetBytes(uint16_t value, base::Span const &span) const
{
	base::BitConverter::GetBytes(value, span);
	if (ShouldReverse())
	{
		std::reverse(span.Buffer(), span.Buffer() + sizeof(value));
	}
}

void base::AutoBitConverter::GetBytes(uint16_t value, base::Stream &stream) const
{
	uint8_t *buffer = reinterpret_cast<uint8_t *>(&value);
	if (ShouldReverse())
	{
		std::reverse(buffer, buffer + sizeof(value));
	}

	stream.Write(buffer, 0, sizeof(value));
}

void base::AutoBitConverter::GetBytes(int16_t value, base::Span const &span) const
{
	base::BitConverter::GetBytes(value, span);
	if (ShouldReverse())
	{
		std::reverse(span.Buffer(), span.Buffer() + sizeof(value));
	}
}

void base::AutoBitConverter::GetBytes(int16_t value, base::Stream &stream) const
{
	uint8_t *buffer = reinterpret_cast<uint8_t *>(&value);
	if (ShouldReverse())
	{
		std::reverse(buffer, buffer + sizeof(value));
	}

	stream.Write(buffer, 0, sizeof(value));
}

void base::AutoBitConverter::GetBytes(uint32_t value, base::Span const &span) const
{
	base::BitConverter::GetBytes(value, span);
	if (ShouldReverse())
	{
		std::reverse(span.Buffer(), span.Buffer() + sizeof(value));
	}
}

void base::AutoBitConverter::GetBytes(uint32_t value, base::Stream &stream) const
{
	uint8_t *buffer = reinterpret_cast<uint8_t *>(&value);
	if (ShouldReverse())
	{
		std::reverse(buffer, buffer + sizeof(value));
	}

	stream.Write(buffer, 0, sizeof(value));
}

void base::AutoBitConverter::GetBytes(int32_t value, base::Span const &span) const
{
	base::BitConverter::GetBytes(value, span);
	if (ShouldReverse())
	{
		std::reverse(span.Buffer(), span.Buffer() + sizeof(value));
	}
}

void base::AutoBitConverter::GetBytes(int32_t value, base::Stream &stream) const
{
	uint8_t *buffer = reinterpret_cast<uint8_t *>(&value);
	if (ShouldReverse())
	{
		std::reverse(buffer, buffer + sizeof(value));
	}

	stream.Write(buffer, 0, sizeof(value));
}

void base::AutoBitConverter::GetBytes(uint64_t value, base::Span const &span) const
{
	base::BitConverter::GetBytes(value, span);
	if (ShouldReverse())
	{
		std::reverse(span.Buffer(), span.Buffer() + sizeof(value));
	}
}

void base::AutoBitConverter::GetBytes(uint64_t value, base::Stream &stream) const
{
	uint8_t *buffer = reinterpret_cast<uint8_t *>(&value);
	if (ShouldReverse())
	{
		std::reverse(buffer, buffer + sizeof(value));
	}

	stream.Write(buffer, 0, sizeof(value));
}

void base::AutoBitConverter::GetBytes(int64_t value, base::Span const &span) const
{
	base::BitConverter::GetBytes(value, span);
	if (ShouldReverse())
	{
		std::reverse(span.Buffer(), span.Buffer() + sizeof(value));
	}
}

void base::AutoBitConverter::GetBytes(int64_t value, base::Stream &stream) const
{
	uint8_t *buffer = reinterpret_cast<uint8_t *>(&value);
	if (ShouldReverse())
	{
		std::reverse(buffer, buffer + sizeof(value));
	}

	stream.Write(buffer, 0, sizeof(value));
}

void base::AutoBitConverter::GetBytes(float value, base::Span const &span) const
{
	base::BitConverter::GetBytes(value, span);
	if (ShouldReverse())
	{
		std::reverse(span.Buffer(), span.Buffer() + sizeof(value));
	}
}

void base::AutoBitConverter::GetBytes(float value, base::Stream &stream) const
{
	uint8_t *buffer = reinterpret_cast<uint8_t *>(&value);
	if (ShouldReverse())
	{
		std::reverse(buffer, buffer + sizeof(value));
	}

	stream.Write(buffer, 0, sizeof(value));
}

void base::AutoBitConverter::GetBytes(double value, base::Span const &span) const
{
	base::BitConverter::GetBytes(value, span);
	if (ShouldReverse())
	{
		std::reverse(span.Buffer(), span.Buffer() + sizeof(value));
	}
}

void base::AutoBitConverter::GetBytes(double value, base::Stream &stream) const
{
	uint8_t *buffer = reinterpret_cast<uint8_t *>(&value);
	if (ShouldReverse())
	{
		std::reverse(buffer, buffer + sizeof(value));
	}

	stream.Write(buffer, 0, sizeof(value));
}
