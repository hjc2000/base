#pragma once
#include <array>
#include <base/define.h>
#include <stdint.h>

namespace base
{
    /// @brief 比特转换
    class BitConverter
    {
    private:
        BitConverter() = delete;

    public:
#pragma region 转数字
        /// @brief 从缓冲区中 offset 处开始，反序列化出 uint16_t
        /// @param buffer
        /// @param offset
        /// @return
        static_function uint16_t ToUInt16(uint8_t const *buffer, int32_t offset);

        /// @brief 从缓冲区中 offset 处开始，反序列化出 int16_t
        /// @param buffer
        /// @param offset
        /// @return
        static_function int16_t ToInt16(uint8_t const *buffer, int32_t offset);

        /// @brief 将高字节和低字节拼接成 uint16_t.
        /// @param high
        /// @param low
        /// @return
        static_function uint16_t ToUInt16(uint8_t high, uint8_t low);

        /// @brief 从缓冲区中 offset 处开始，反序列化出 uint32_t
        /// @param buffer
        /// @param offset
        /// @return
        static_function uint32_t ToUInt32(uint8_t const *buffer, int32_t offset);

        /// @brief 从缓冲区中 offset 处开始，反序列化出 int32_t
        /// @param buffer
        /// @param offset
        /// @return
        static_function int32_t ToInt32(uint8_t const *buffer, int32_t offset);

        /// @brief 将 4 个字节拼接成 uint32_t. b0 是最低字节，b3 是最高字节。
        /// @param b3 最高字节
        /// @param b2
        /// @param b1
        /// @param b0 最低字节
        /// @return
        static_function uint32_t ToUInt32(uint8_t b3, uint8_t b2, uint8_t b1, uint8_t b0);

        /// @brief 将低 uint16_t 和高 uint16_t 拼接成 uint32_t.
        /// @param high
        /// @param low
        /// @return
        static_function uint32_t ToUInt32(uint16_t high, uint16_t low);

        /// @brief 从缓冲区中 offset 处开始，反序列化出 uint64_t
        /// @param buffer
        /// @param offset
        /// @return
        static_function uint64_t ToUInt64(uint8_t const *buffer, int32_t offset);

        /// @brief 从缓冲区中 offset 处开始，反序列化出 int64_t
        /// @param buffer
        /// @param offset
        /// @return
        static_function int64_t ToInt64(uint8_t const *buffer, int32_t offset);

        /// @brief 从缓冲区中 offset 处开始，反序列化出 float
        /// @param buffer
        /// @param offset
        /// @return
        static_function float ToFloat(uint8_t const *buffer, int32_t offset);

        /// @brief 从缓冲区中 offset 处开始，反序列化出 double
        /// @param buffer
        /// @param offset
        /// @return
        static_function double ToDouble(uint8_t const *buffer, int32_t offset);
#pragma endregion

#pragma region 转到缓冲区
        /// @brief 将 value 序列化到缓冲区中的 offset 处。
        /// @param value
        /// @param out_buffer
        /// @param offset
        static_function void GetBytes(uint16_t value, uint8_t *out_buffer, int32_t offset);

        /// @brief 将 value 序列化到缓冲区中的 offset 处。
        /// @param value
        /// @param out_buffer
        /// @param offset
        static_function void GetBytes(int16_t value, uint8_t *out_buffer, int32_t offset);

        /// @brief 将 value 序列化到缓冲区中的 offset 处。
        /// @param value
        /// @param out_buffer
        /// @param offset
        static_function void GetBytes(uint32_t value, uint8_t *out_buffer, int32_t offset);

        /// @brief 将 value 序列化到缓冲区中的 offset 处。
        /// @param value
        /// @param out_buffer
        /// @param offset
        static_function void GetBytes(int32_t value, uint8_t *out_buffer, int32_t offset);

        /// @brief 将 value 序列化到缓冲区中的 offset 处。
        /// @param value
        /// @param out_buffer
        /// @param offset
        static_function void GetBytes(uint64_t value, uint8_t *out_buffer, int32_t offset);

        /// @brief 将 value 序列化到缓冲区中的 offset 处。
        /// @param value
        /// @param out_buffer
        /// @param offset
        static_function void GetBytes(int64_t value, uint8_t *out_buffer, int32_t offset);

        /// @brief 将 value 序列化到缓冲区中的 offset 处。
        /// @param value
        /// @param out_buffer
        /// @param offset
        static_function void GetBytes(float value, uint8_t *out_buffer, int32_t offset);

        /// @brief 将 value 序列化到缓冲区中的 offset 处。
        /// @param value
        /// @param out_buffer
        /// @param offset
        static_function void GetBytes(double value, uint8_t *out_buffer, int32_t offset);
#pragma endregion

#pragma region 转字节数组
        /// @brief 将 value 序列化到 std::array 中。
        /// @param value
        /// @return
        static_function std::array<uint8_t, 2> GetBytes(uint16_t value);

        /// @brief 将 value 序列化到 std::array 中。
        /// @param value
        /// @return
        static_function std::array<uint8_t, 2> GetBytes(int16_t value);

        /// @brief 将 value 序列化到 std::array 中。
        /// @param value
        /// @return
        static_function std::array<uint8_t, 4> GetBytes(uint32_t value);

        /// @brief 将 value 序列化到 std::array 中。
        /// @param value
        /// @return
        static_function std::array<uint8_t, 4> GetBytes(int32_t value);

        /// @brief 将 value 序列化到 std::array 中。
        /// @param value
        /// @return
        static_function std::array<uint8_t, 8> GetBytes(uint64_t value);

        /// @brief 将 value 序列化到 std::array 中。
        /// @param value
        /// @return
        static_function std::array<uint8_t, 8> GetBytes(int64_t value);

        /// @brief 将 value 序列化到 std::array 中。
        /// @param value
        /// @return
        static_function std::array<uint8_t, 4> GetBytes(float value);

        /// @brief 将 value 序列化到 std::array 中。
        /// @param value
        /// @return
        static_function std::array<uint8_t, 8> GetBytes(double value);
#pragma endregion
    };
} // namespace base
