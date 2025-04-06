#include "bit_converte.h"
#include "base/string/define.h"

uint16_t base::bit_converte::ToUInt16(base::ReadOnlySpan const &span)
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

uint16_t base::bit_converte::ToUInt16(base::Stream &stream)
{
	uint8_t buffer[sizeof(uint16_t)];
	int32_t have_read = stream.ReadExactly(buffer, 0, sizeof(buffer));
	if (have_read < static_cast<int32_t>(sizeof(buffer)))
	{
		throw std::runtime_error{CODE_POS_STR + "流中没有足够的字节。"};
	}

	return ToUInt16(base::Span{buffer, sizeof(buffer)});
}

int16_t base::bit_converte::ToInt16(base::ReadOnlySpan const &span)
{
	return static_cast<int16_t>(ToUInt16(span));
}

int16_t base::bit_converte::ToInt16(base::Stream &stream)
{
	uint8_t buffer[sizeof(int16_t)];
	int32_t have_read = stream.ReadExactly(buffer, 0, sizeof(buffer));
	if (have_read < static_cast<int32_t>(sizeof(buffer)))
	{
		throw std::runtime_error{CODE_POS_STR + "流中没有足够的字节。"};
	}

	return ToInt16(base::Span{buffer, sizeof(buffer)});
}

uint16_t base::bit_converte::ToUInt16(uint8_t high, uint8_t low)
{
	return (static_cast<uint16_t>(high) << 8) | low;
}

uint32_t base::bit_converte::ToUInt32(base::ReadOnlySpan const &span)
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

uint32_t base::bit_converte::ToUInt32(base::Stream &stream)
{
	uint8_t buffer[sizeof(uint32_t)];
	int32_t have_read = stream.ReadExactly(buffer, 0, sizeof(buffer));
	if (have_read < static_cast<int32_t>(sizeof(buffer)))
	{
		throw std::runtime_error{CODE_POS_STR + "流中没有足够的字节。"};
	}

	return ToUInt32(base::Span{buffer, sizeof(buffer)});
}

int32_t base::bit_converte::ToInt32(base::ReadOnlySpan const &span)
{
	return static_cast<int32_t>(ToUInt32(span));
}

int32_t base::bit_converte::ToInt32(base::Stream &stream)
{
	uint8_t buffer[sizeof(int32_t)];
	int32_t have_read = stream.ReadExactly(buffer, 0, sizeof(buffer));
	if (have_read < static_cast<int32_t>(sizeof(buffer)))
	{
		throw std::runtime_error{CODE_POS_STR + "流中没有足够的字节。"};
	}

	return ToInt32(base::Span{buffer, sizeof(buffer)});
}

uint32_t base::bit_converte::ToUInt32(uint8_t b3, uint8_t b2, uint8_t b1, uint8_t b0)
{
	uint16_t high = ToUInt16(b3, b2);
	uint16_t low = ToUInt16(b1, b0);
	return ToUInt32(high, low);
}

uint32_t base::bit_converte::ToUInt32(uint16_t high, uint16_t low)
{
	return (static_cast<uint32_t>(high) << 16) | low;
}

uint64_t base::bit_converte::ToUInt64(base::ReadOnlySpan const &span)
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

uint64_t base::bit_converte::ToUInt64(base::Stream &stream)
{
	uint8_t buffer[sizeof(uint64_t)];
	int32_t have_read = stream.ReadExactly(buffer, 0, sizeof(buffer));
	if (have_read < static_cast<int32_t>(sizeof(buffer)))
	{
		throw std::runtime_error{CODE_POS_STR + "流中没有足够的字节。"};
	}

	return ToUInt64(base::Span{buffer, sizeof(buffer)});
}

int64_t base::bit_converte::ToInt64(base::ReadOnlySpan const &span)
{
	return static_cast<int64_t>(ToUInt64(span));
}

int64_t base::bit_converte::ToInt64(base::Stream &stream)
{
	uint8_t buffer[sizeof(int64_t)];
	int32_t have_read = stream.ReadExactly(buffer, 0, sizeof(buffer));
	if (have_read < static_cast<int32_t>(sizeof(buffer)))
	{
		throw std::runtime_error{CODE_POS_STR + "流中没有足够的字节。"};
	}

	return ToInt64(base::Span{buffer, sizeof(buffer)});
}

float base::bit_converte::ToFloat(base::ReadOnlySpan const &span)
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

float base::bit_converte::ToFloat(base::Stream &stream)
{
	uint8_t buffer[sizeof(float)];
	int32_t have_read = stream.ReadExactly(buffer, 0, sizeof(buffer));
	if (have_read < static_cast<int32_t>(sizeof(buffer)))
	{
		throw std::runtime_error{CODE_POS_STR + "流中没有足够的字节。"};
	}

	return ToFloat(base::Span{buffer, sizeof(buffer)});
}

double base::bit_converte::ToDouble(base::ReadOnlySpan const &span)
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

double base::bit_converte::ToDouble(base::Stream &stream)
{
	uint8_t buffer[sizeof(double)];
	int32_t have_read = stream.ReadExactly(buffer, 0, sizeof(buffer));
	if (have_read < static_cast<int32_t>(sizeof(buffer)))
	{
		throw std::runtime_error{CODE_POS_STR + "流中没有足够的字节。"};
	}

	return ToDouble(base::Span{buffer, sizeof(buffer)});
}
