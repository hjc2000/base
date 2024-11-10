#pragma once
#include <base/container/Array.h>
#include <cstdint>

namespace base
{
    /// @brief MAC 地址
    class Mac
    {
    private:
        base::Array<uint8_t, 6> _mac_buffer{};

    public:
        Mac(base::Array<uint8_t, 6> const &mac_buffer);
        Mac(Mac const &o);

        Mac &operator=(Mac const &o);

        explicit operator base::Array<uint8_t, 6>() const;

        /// @brief 访问 MAC 地址中指定索引的值。
        /// @param index
        /// @return
        uint8_t &operator[](int index);

        /// @brief 访问 MAC 地址中指定索引的值。
        /// @param index
        /// @return
        uint8_t const &operator[](int index) const;
    };
} // namespace base
