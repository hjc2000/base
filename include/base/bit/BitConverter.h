#pragma once
#include <array>
#include <stdint.h>

namespace base
{
    /// @brief 比特转换
    class BitConverter
    {
    private:
        BitConverter() = delete;
        BitConverter(BitConverter const &o) = delete;
        BitConverter(BitConverter const &&o) = delete;
        BitConverter &operator=(BitConverter const &o) = delete;

    public:
#pragma region 转数字
        /// @brief 从缓冲区中 offset 处开始，反序列化出 uint16_t
        /// @param buffer
        /// @param offset
        /// @return
        static uint16_t ToUInt16(uint8_t const *buffer, int32_t offset);

        /// @brief 从缓冲区中 offset 处开始，反序列化出 int16_t
        /// @param buffer
        /// @param offset
        /// @return
        static int16_t ToInt16(uint8_t const *buffer, int32_t offset);
        static uint16_t ToUInt16(uint8_t high, uint8_t low);

        /// @brief 从缓冲区中 offset 处开始，反序列化出 uint32_t
        /// @param buffer
        /// @param offset
        /// @return
        static uint32_t ToUInt32(uint8_t const *buffer, int32_t offset);

        /// @brief 从缓冲区中 offset 处开始，反序列化出 int32_t
        /// @param buffer
        /// @param offset
        /// @return
        static int32_t ToInt32(uint8_t const *buffer, int32_t offset);
        static uint32_t ToUInt32(uint8_t b3, uint8_t b2, uint8_t b1, uint8_t b0);
        static uint32_t ToUInt32(uint16_t high, uint16_t low);

        /// @brief 从缓冲区中 offset 处开始，反序列化出 uint64_t
        /// @param buffer
        /// @param offset
        /// @return
        static uint64_t ToUInt64(uint8_t const *buffer, int32_t offset);

        /// @brief 从缓冲区中 offset 处开始，反序列化出 int64_t
        /// @param buffer
        /// @param offset
        /// @return
        static int64_t ToInt64(uint8_t const *buffer, int32_t offset);

        /// @brief 从缓冲区中 offset 处开始，反序列化出 float
        /// @param buffer
        /// @param offset
        /// @return
        static float ToFloat(uint8_t const *buffer, int32_t offset);

        /// @brief 从缓冲区中 offset 处开始，反序列化出 double
        /// @param buffer
        /// @param offset
        /// @return
        static double ToDouble(uint8_t const *buffer, int32_t offset);
#pragma endregion

#pragma region 转到缓冲区
        /// @brief 将 value 序列化到缓冲区中的 offset 处。
        /// @param value
        /// @param out_buffer
        /// @param offset
        static void GetBytes(uint16_t value, uint8_t *out_buffer, int32_t offset);

        /// @brief 将 value 序列化到缓冲区中的 offset 处。
        /// @param value
        /// @param out_buffer
        /// @param offset
        static void GetBytes(int16_t value, uint8_t *out_buffer, int32_t offset);

        /// @brief 将 value 序列化到缓冲区中的 offset 处。
        /// @param value
        /// @param out_buffer
        /// @param offset
        static void GetBytes(uint32_t value, uint8_t *out_buffer, int32_t offset);

        /// @brief 将 value 序列化到缓冲区中的 offset 处。
        /// @param value
        /// @param out_buffer
        /// @param offset
        static void GetBytes(int32_t value, uint8_t *out_buffer, int32_t offset);

        /// @brief 将 value 序列化到缓冲区中的 offset 处。
        /// @param value
        /// @param out_buffer
        /// @param offset
        static void GetBytes(uint64_t value, uint8_t *out_buffer, int32_t offset);

        /// @brief 将 value 序列化到缓冲区中的 offset 处。
        /// @param value
        /// @param out_buffer
        /// @param offset
        static void GetBytes(int64_t value, uint8_t *out_buffer, int32_t offset);

        /// @brief 将 value 序列化到缓冲区中的 offset 处。
        /// @param value
        /// @param out_buffer
        /// @param offset
        static void GetBytes(float value, uint8_t *out_buffer, int32_t offset);

        /// @brief 将 value 序列化到缓冲区中的 offset 处。
        /// @param value
        /// @param out_buffer
        /// @param offset
        static void GetBytes(double value, uint8_t *out_buffer, int32_t offset);
#pragma endregion

#pragma region 转字节数组
        /// @brief 将 value 序列化到 std::array 中。
        /// @param value
        /// @return
        static std::array<uint8_t, 2> GetBytes(uint16_t value);

        /// @brief 将 value 序列化到 std::array 中。
        /// @param value
        /// @return
        static std::array<uint8_t, 2> GetBytes(int16_t value);

        /// @brief 将 value 序列化到 std::array 中。
        /// @param value
        /// @return
        static std::array<uint8_t, 4> GetBytes(uint32_t value);

        /// @brief 将 value 序列化到 std::array 中。
        /// @param value
        /// @return
        static std::array<uint8_t, 4> GetBytes(int32_t value);

        /// @brief 将 value 序列化到 std::array 中。
        /// @param value
        /// @return
        static std::array<uint8_t, 8> GetBytes(uint64_t value);

        /// @brief 将 value 序列化到 std::array 中。
        /// @param value
        /// @return
        static std::array<uint8_t, 8> GetBytes(int64_t value);

        /// @brief 将 value 序列化到 std::array 中。
        /// @param value
        /// @return
        static std::array<uint8_t, 4> GetBytes(float value);

        /// @brief 将 value 序列化到 std::array 中。
        /// @param value
        /// @return
        static std::array<uint8_t, 8> GetBytes(double value);
#pragma endregion
    };
} // namespace base
