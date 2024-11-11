#pragma once
#include <array>
#include <bit>
#include <stdint.h>

namespace base
{
    /// @brief 构造时设置好通信对方的大小端，进行转换时能够自动进行大小端转换。
    class AutoBitConverter final
    {
    private:
        std::endian _remote_endian;

    public:
        /// @brief
        /// @param remote_endian 对方主机的字节序
        AutoBitConverter(std::endian remote_endian);

        /// @brief 是否应该翻转。
        /// @return 当远程字节序和本机字节序不同时，需要翻转，此时会返回 true.
        bool ShouldReverse() const;

#pragma region 转成数字类型
        uint16_t ToUInt16(uint8_t const *buffer, int32_t offset) const;
        int16_t ToInt16(uint8_t const *buffer, int32_t offset) const;

        uint32_t ToUInt32(uint8_t const *buffer, int32_t offset) const;
        int32_t ToInt32(uint8_t const *buffer, int32_t offset) const;

        uint64_t ToUInt64(uint8_t const *buffer, int32_t offset) const;
        int64_t ToInt64(uint8_t const *buffer, int32_t offset) const;

        float ToFloat(uint8_t const *buffer, int32_t offset) const;
        double ToDouble(uint8_t const *buffer, int32_t offset) const;
#pragma endregion

#pragma region 转到缓冲区
        void GetBytes(uint16_t value, uint8_t *out_buffer, int32_t offset) const;
        void GetBytes(int16_t value, uint8_t *out_buffer, int32_t offset) const;

        void GetBytes(uint32_t value, uint8_t *out_buffer, int32_t offset) const;
        void GetBytes(int32_t value, uint8_t *out_buffer, int32_t offset) const;

        void GetBytes(uint64_t value, uint8_t *out_buffer, int32_t offset) const;
        void GetBytes(int64_t value, uint8_t *out_buffer, int32_t offset) const;

        void GetBytes(float value, uint8_t *out_buffer, int32_t offset) const;
        void GetBytes(double value, uint8_t *out_buffer, int32_t offset) const;
#pragma endregion

#pragma region 转成字节数组
        std::array<uint8_t, 2> GetBytes(uint16_t value) const;
        std::array<uint8_t, 2> GetBytes(int16_t value) const;

        std::array<uint8_t, 4> GetBytes(uint32_t value) const;
        std::array<uint8_t, 4> GetBytes(int32_t value) const;

        std::array<uint8_t, 8> GetBytes(uint64_t value) const;
        std::array<uint8_t, 8> GetBytes(int64_t value) const;

        std::array<uint8_t, 4> GetBytes(float value) const;
        std::array<uint8_t, 8> GetBytes(double value) const;
#pragma endregion
    };
} // namespace base
