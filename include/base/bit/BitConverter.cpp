#include "BitConverter.h"

using namespace base;

#pragma region 转数字类型
uint16_t base::BitConverter::ToUInt16(uint8_t const *buffer, int32_t offset)
{
	uint16_t const *p = reinterpret_cast<uint16_t const *>(buffer + offset);
	return *p;
}

int16_t base::BitConverter::ToInt16(uint8_t const *buffer, int32_t offset)
{
	int16_t const *p = reinterpret_cast<int16_t const *>(buffer + offset);
	return *p;
}

uint16_t base::BitConverter::ToUInt16(uint8_t high, uint8_t low)
{
	return ((uint16_t)high << 8) | low;
}

uint32_t base::BitConverter::ToUInt32(uint8_t const *buffer, int32_t offset)
{
	uint32_t const *p = reinterpret_cast<uint32_t const *>(buffer + offset);
	return *p;
}

int32_t base::BitConverter::ToInt32(uint8_t const *buffer, int32_t offset)
{
	int32_t const *p = reinterpret_cast<int32_t const *>(buffer + offset);
	return *p;
}

uint32_t base::BitConverter::ToUInt32(uint8_t b3, uint8_t b2, uint8_t b1, uint8_t b0)
{
	uint16_t high = ToUInt16(b3, b2);
	uint16_t low = ToUInt16(b1, b0);
	return ToUInt32(high, low);
}

uint32_t base::BitConverter::ToUInt32(uint16_t high, uint16_t low)
{
	return ((uint32_t)high << 16) | low;
}

uint64_t base::BitConverter::ToUInt64(uint8_t const *buffer, int32_t offset)
{
	uint64_t const *p = reinterpret_cast<uint64_t const *>(buffer + offset);
	return *p;
}

int64_t base::BitConverter::ToInt64(uint8_t const *buffer, int32_t offset)
{
	int64_t const *p = reinterpret_cast<int64_t const *>(buffer + offset);
	return *p;
}

float base::BitConverter::ToFloat(uint8_t const *buffer, int32_t offset)
{
	float const *p = reinterpret_cast<float const *>(buffer + offset);
	return *p;
}

double base::BitConverter::ToDouble(uint8_t const *buffer, int32_t offset)
{
	double const *p = reinterpret_cast<double const *>(buffer + offset);
	return *p;
}
#pragma endregion

#pragma region 转缓冲区
void base::BitConverter::GetBytes(uint16_t value, uint8_t *out_buffer, int32_t offset)
{
	uint8_t *buffer = reinterpret_cast<uint8_t *>(&value);
	std::copy(buffer, buffer + 2, out_buffer + offset);
}

void base::BitConverter::GetBytes(int16_t value, uint8_t *out_buffer, int32_t offset)
{
	uint8_t *buffer = reinterpret_cast<uint8_t *>(&value);
	std::copy(buffer, buffer + 2, out_buffer + offset);
}

void base::BitConverter::GetBytes(uint32_t value, uint8_t *out_buffer, int32_t offset)
{
	uint8_t *buffer = reinterpret_cast<uint8_t *>(&value);
	std::copy(buffer, buffer + 4, out_buffer + offset);
}

void base::BitConverter::GetBytes(int32_t value, uint8_t *out_buffer, int32_t offset)
{
	uint8_t *buffer = reinterpret_cast<uint8_t *>(&value);
	std::copy(buffer, buffer + 4, out_buffer + offset);
}

void base::BitConverter::GetBytes(uint64_t value, uint8_t *out_buffer, int32_t offset)
{
	uint8_t *buffer = reinterpret_cast<uint8_t *>(&value);
	std::copy(buffer, buffer + 8, out_buffer + offset);
}

void base::BitConverter::GetBytes(int64_t value, uint8_t *out_buffer, int32_t offset)
{
	uint8_t *buffer = reinterpret_cast<uint8_t *>(&value);
	std::copy(buffer, buffer + 8, out_buffer + offset);
}

void base::BitConverter::GetBytes(float value, uint8_t *out_buffer, int32_t offset)
{
	uint8_t *buffer = reinterpret_cast<uint8_t *>(&value);
	std::copy(buffer, buffer + 4, out_buffer + offset);
}

void base::BitConverter::GetBytes(double value, uint8_t *out_buffer, int32_t offset)
{
	uint8_t *buffer = reinterpret_cast<uint8_t *>(&value);
	std::copy(buffer, buffer + 8, out_buffer + offset);
}
#pragma endregion

#pragma region 转字节数组
std::array<uint8_t, 2> base::BitConverter::GetBytes(uint16_t value)
{
	std::array<uint8_t, 2> ret;
	GetBytes(value, ret.data(), 0);
	return ret;
}

std::array<uint8_t, 2> base::BitConverter::GetBytes(int16_t value)
{
	std::array<uint8_t, 2> ret;
	GetBytes(value, ret.data(), 0);
	return ret;
}

std::array<uint8_t, 4> base::BitConverter::GetBytes(uint32_t value)
{
	std::array<uint8_t, 4> ret;
	GetBytes(value, ret.data(), 0);
	return ret;
}

std::array<uint8_t, 4> base::BitConverter::GetBytes(int32_t value)
{
	std::array<uint8_t, 4> ret;
	GetBytes(value, ret.data(), 0);
	return ret;
}

std::array<uint8_t, 8> base::BitConverter::GetBytes(uint64_t value)
{
	std::array<uint8_t, 8> ret;
	GetBytes(value, ret.data(), 0);
	return ret;
}

std::array<uint8_t, 8> base::BitConverter::GetBytes(int64_t value)
{
	std::array<uint8_t, 8> ret;
	GetBytes(value, ret.data(), 0);
	return ret;
}

std::array<uint8_t, 4> base::BitConverter::GetBytes(float value)
{
	std::array<uint8_t, 4> ret;
	GetBytes(value, ret.data(), 0);
	return ret;
}

std::array<uint8_t, 8> base::BitConverter::GetBytes(double value)
{
	std::array<uint8_t, 8> ret;
	GetBytes(value, ret.data(), 0);
	return ret;
}
#pragma endregion
