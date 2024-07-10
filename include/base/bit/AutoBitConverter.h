#pragma once
#include <array>
#include <bit>
#include <stdint.h>

namespace base
{
	/// @brief 构造时设置好通信对方的大小端，进行转换时能够自动进行大小端转换。
	class AutoBitConverter
	{
	private:
		std::endian _remote_endian;
		bool ShouldReverse();

	public:
		/// @brief
		/// @param remote_endian 对方主机的字节序
		AutoBitConverter(std::endian remote_endian);

#pragma region 转成数字类型
		uint16_t ToUInt16(uint8_t const *buffer, int32_t offset);
		int16_t ToInt16(uint8_t const *buffer, int32_t offset);

		uint32_t ToUInt32(uint8_t const *buffer, int32_t offset);
		int32_t ToInt32(uint8_t const *buffer, int32_t offset);

		uint64_t ToUInt64(uint8_t const *buffer, int32_t offset);
		int64_t ToInt64(uint8_t const *buffer, int32_t offset);

		float ToFloat(uint8_t const *buffer, int32_t offset);
		double ToDouble(uint8_t const *buffer, int32_t offset);
#pragma endregion

#pragma region 转到缓冲区
		void GetBytes(uint16_t value, uint8_t *out_buffer, int32_t offset);
		void GetBytes(int16_t value, uint8_t *out_buffer, int32_t offset);

		void GetBytes(uint32_t value, uint8_t *out_buffer, int32_t offset);
		void GetBytes(int32_t value, uint8_t *out_buffer, int32_t offset);

		void GetBytes(uint64_t value, uint8_t *out_buffer, int32_t offset);
		void GetBytes(int64_t value, uint8_t *out_buffer, int32_t offset);

		void GetBytes(float value, uint8_t *out_buffer, int32_t offset);
		void GetBytes(double value, uint8_t *out_buffer, int32_t offset);
#pragma endregion

#pragma region 转成字节数组
		std::array<uint8_t, 2> GetBytes(uint16_t value);
		std::array<uint8_t, 2> GetBytes(int16_t value);

		std::array<uint8_t, 4> GetBytes(uint32_t value);
		std::array<uint8_t, 4> GetBytes(int32_t value);

		std::array<uint8_t, 8> GetBytes(uint64_t value);
		std::array<uint8_t, 8> GetBytes(int64_t value);

		std::array<uint8_t, 4> GetBytes(float value);
		std::array<uint8_t, 8> GetBytes(double value);
#pragma endregion
	};
}
