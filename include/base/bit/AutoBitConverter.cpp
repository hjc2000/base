#include "AutoBitConverter.h"
#include <algorithm>
#include <base/bit/BitConverter.h>

using namespace base;

bool base::AutoBitConverter::ShouldReverse()
{
	return std::endian::native != _remote_endian;
}

base::AutoBitConverter::AutoBitConverter(std::endian remote_endian)
	: _remote_endian(remote_endian)
{
}

#pragma region 转成数字类型
uint16_t base::AutoBitConverter::ToUInt16(uint8_t const *buffer, int32_t offset)
{
	uint16_t ret = BitConverter::ToUInt16(buffer, offset);
	uint8_t *p = reinterpret_cast<uint8_t *>(&ret);
	if (ShouldReverse())
	{
		std::reverse(p, p + 2);
	}

	return ret;
}

int16_t base::AutoBitConverter::ToInt16(uint8_t const *buffer, int32_t offset)
{
	int16_t ret = BitConverter::ToInt16(buffer, offset);
	uint8_t *p = reinterpret_cast<uint8_t *>(&ret);
	if (ShouldReverse())
	{
		std::reverse(p, p + 2);
	}

	return ret;
}

uint32_t base::AutoBitConverter::ToUInt32(uint8_t const *buffer, int32_t offset)
{
	uint32_t ret = BitConverter::ToUInt32(buffer, offset);
	uint8_t *p = reinterpret_cast<uint8_t *>(&ret);
	if (ShouldReverse())
	{
		std::reverse(p, p + 4);
	}

	return ret;
}

int32_t base::AutoBitConverter::ToInt32(uint8_t const *buffer, int32_t offset)
{
	int32_t ret = BitConverter::ToInt32(buffer, offset);
	uint8_t *p = reinterpret_cast<uint8_t *>(&ret);
	if (ShouldReverse())
	{
		std::reverse(p, p + 4);
	}

	return ret;
}

uint64_t base::AutoBitConverter::ToUInt64(uint8_t const *buffer, int32_t offset)
{
	uint64_t ret = BitConverter::ToUInt64(buffer, offset);
	uint8_t *p = reinterpret_cast<uint8_t *>(&ret);
	if (ShouldReverse())
	{
		std::reverse(p, p + 8);
	}

	return ret;
}

int64_t base::AutoBitConverter::ToInt64(uint8_t const *buffer, int32_t offset)
{
	int64_t ret = BitConverter::ToInt64(buffer, offset);
	uint8_t *p = reinterpret_cast<uint8_t *>(&ret);
	if (ShouldReverse())
	{
		std::reverse(p, p + 8);
	}

	return ret;
}

float base::AutoBitConverter::ToFloat(uint8_t const *buffer, int32_t offset)
{
	float ret = BitConverter::ToFloat(buffer, offset);
	uint8_t *p = reinterpret_cast<uint8_t *>(&ret);
	if (ShouldReverse())
	{
		std::reverse(p, p + 4);
	}

	return ret;
}

double base::AutoBitConverter::ToDouble(uint8_t const *buffer, int32_t offset)
{
	double ret = BitConverter::ToDouble(buffer, offset);
	uint8_t *p = reinterpret_cast<uint8_t *>(&ret);
	if (ShouldReverse())
	{
		std::reverse(p, p + 8);
	}

	return ret;
}
#pragma endregion

#pragma region 转到缓冲区
void base::AutoBitConverter::GetBytes(uint16_t value, uint8_t *out_buffer, int32_t offset)
{
	BitConverter::GetBytes(value, out_buffer, offset);
	if (ShouldReverse())
	{
		std::reverse(out_buffer + offset, out_buffer + offset + 2);
	}
}

void base::AutoBitConverter::GetBytes(int16_t value, uint8_t *out_buffer, int32_t offset)
{
	BitConverter::GetBytes(value, out_buffer, offset);
	if (ShouldReverse())
	{
		std::reverse(out_buffer + offset, out_buffer + offset + 2);
	}
}

void base::AutoBitConverter::GetBytes(uint32_t value, uint8_t *out_buffer, int32_t offset)
{
	BitConverter::GetBytes(value, out_buffer, offset);
	if (ShouldReverse())
	{
		std::reverse(out_buffer + offset, out_buffer + offset + 4);
	}
}

void base::AutoBitConverter::GetBytes(int32_t value, uint8_t *out_buffer, int32_t offset)
{
	BitConverter::GetBytes(value, out_buffer, offset);
	if (ShouldReverse())
	{
		std::reverse(out_buffer + offset, out_buffer + offset + 4);
	}
}

void base::AutoBitConverter::GetBytes(uint64_t value, uint8_t *out_buffer, int32_t offset)
{
	BitConverter::GetBytes(value, out_buffer, offset);
	if (ShouldReverse())
	{
		std::reverse(out_buffer + offset, out_buffer + offset + 8);
	}
}

void base::AutoBitConverter::GetBytes(int64_t value, uint8_t *out_buffer, int32_t offset)
{
	BitConverter::GetBytes(value, out_buffer, offset);
	if (ShouldReverse())
	{
		std::reverse(out_buffer + offset, out_buffer + offset + 8);
	}
}

void base::AutoBitConverter::GetBytes(float value, uint8_t *out_buffer, int32_t offset)
{
	BitConverter::GetBytes(value, out_buffer, offset);
	if (ShouldReverse())
	{
		std::reverse(out_buffer + offset, out_buffer + offset + 4);
	}
}

void base::AutoBitConverter::GetBytes(double value, uint8_t *out_buffer, int32_t offset)
{
	BitConverter::GetBytes(value, out_buffer, offset);
	if (ShouldReverse())
	{
		std::reverse(out_buffer + offset, out_buffer + offset + 8);
	}
}
#pragma endregion

#pragma region 转成字节数组
std::array<uint8_t, 2> base::AutoBitConverter::GetBytes(uint16_t value)
{
	std::array<uint8_t, 2> ret = BitConverter::GetBytes(value);
	if (ShouldReverse())
	{
		std::reverse(ret.begin(), ret.end());
	}

	return ret;
}

std::array<uint8_t, 2> base::AutoBitConverter::GetBytes(int16_t value)
{
	std::array<uint8_t, 2> ret = BitConverter::GetBytes(value);
	if (ShouldReverse())
	{
		std::reverse(ret.begin(), ret.end());
	}

	return ret;
}

std::array<uint8_t, 4> base::AutoBitConverter::GetBytes(uint32_t value)
{
	std::array<uint8_t, 4> ret = BitConverter::GetBytes(value);
	if (ShouldReverse())
	{
		std::reverse(ret.begin(), ret.end());
	}

	return ret;
}

std::array<uint8_t, 4> base::AutoBitConverter::GetBytes(int32_t value)
{
	std::array<uint8_t, 4> ret = BitConverter::GetBytes(value);
	if (ShouldReverse())
	{
		std::reverse(ret.begin(), ret.end());
	}

	return ret;
}

std::array<uint8_t, 8> base::AutoBitConverter::GetBytes(uint64_t value)
{
	std::array<uint8_t, 8> ret = BitConverter::GetBytes(value);
	if (ShouldReverse())
	{
		std::reverse(ret.begin(), ret.end());
	}

	return ret;
}

std::array<uint8_t, 8> base::AutoBitConverter::GetBytes(int64_t value)
{
	std::array<uint8_t, 8> ret = BitConverter::GetBytes(value);
	if (ShouldReverse())
	{
		std::reverse(ret.begin(), ret.end());
	}

	return ret;
}

std::array<uint8_t, 4> base::AutoBitConverter::GetBytes(float value)
{
	std::array<uint8_t, 4> ret = BitConverter::GetBytes(value);
	if (ShouldReverse())
	{
		std::reverse(ret.begin(), ret.end());
	}

	return ret;
}

std::array<uint8_t, 8> base::AutoBitConverter::GetBytes(double value)
{
	std::array<uint8_t, 8> ret = BitConverter::GetBytes(value);
	if (ShouldReverse())
	{
		std::reverse(ret.begin(), ret.end());
	}

	return ret;
}
#pragma endregion
