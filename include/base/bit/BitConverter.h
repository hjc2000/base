#pragma once
#include <array>
#include <stdint.h>

namespace base
{
	class BitConverter
	{
	private:
		BitConverter() = delete;
		BitConverter(BitConverter const &o) = delete;
		BitConverter(BitConverter const &&o) = delete;
		BitConverter &operator=(BitConverter const &o) = delete;

	public:
#pragma region 转数字
		static uint16_t ToUInt16(uint8_t const *buffer, int32_t offset);
		static int16_t ToInt16(uint8_t const *buffer, int32_t offset);
		static uint16_t ToUInt16(uint8_t high, uint8_t low);

		static uint32_t ToUInt32(uint8_t const *buffer, int32_t offset);
		static int32_t ToInt32(uint8_t const *buffer, int32_t offset);
		static uint32_t ToUInt32(uint8_t b3, uint8_t b2, uint8_t b1, uint8_t b0);
		static uint32_t ToUInt32(uint16_t high, uint16_t low);

		static uint64_t ToUInt64(uint8_t const *buffer, int32_t offset);
		static int64_t ToInt64(uint8_t const *buffer, int32_t offset);

		static float ToFloat(uint8_t const *buffer, int32_t offset);
		static double ToDouble(uint8_t const *buffer, int32_t offset);
#pragma endregion

#pragma region 转到缓冲区
		static void GetBytes(uint16_t value, uint8_t *out_buffer, int32_t offset);
		static void GetBytes(int16_t value, uint8_t *out_buffer, int32_t offset);

		static void GetBytes(uint32_t value, uint8_t *out_buffer, int32_t offset);
		static void GetBytes(int32_t value, uint8_t *out_buffer, int32_t offset);

		static void GetBytes(uint64_t value, uint8_t *out_buffer, int32_t offset);
		static void GetBytes(int64_t value, uint8_t *out_buffer, int32_t offset);

		static void GetBytes(float value, uint8_t *out_buffer, int32_t offset);
		static void GetBytes(double value, uint8_t *out_buffer, int32_t offset);
#pragma endregion

#pragma region 转字节数组
		static std::array<uint8_t, 2> GetBytes(uint16_t value);
		static std::array<uint8_t, 2> GetBytes(int16_t value);

		static std::array<uint8_t, 4> GetBytes(uint32_t value);
		static std::array<uint8_t, 4> GetBytes(int32_t value);

		static std::array<uint8_t, 8> GetBytes(uint64_t value);
		static std::array<uint8_t, 8> GetBytes(int64_t value);

		static std::array<uint8_t, 4> GetBytes(float value);
		static std::array<uint8_t, 8> GetBytes(double value);
#pragma endregion
	};
}
