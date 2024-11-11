#pragma once
#include <base/container/Array.h>
#include <cstdint>

namespace base
{
    /// @brief MAC 地址
    /// @note 按照小端序存放。即书写 MAC 字符串时，最右边的，即最低字节，存放在本对象的低索引处；
    /// 字符串最左边的，即最高字节，存放在本对象的最高索引处。
    class Mac
    {
    private:
        base::Array<uint8_t, 6> _mac_buffer{};

    public:
        /// @brief 构造函数。
        /// @param mac_buffer 该缓冲区内的 MAC 地址必须是按小端序存放。
        Mac(base::Array<uint8_t, 6> const &mac_buffer);

        /// @brief 拷贝构造函数。
        /// @param o
        Mac(Mac const &o);

        /// @brief 赋值运算符。
        /// @param o
        /// @return
        Mac &operator=(Mac const &o);

        /// @brief 显示将本对象强制转换为 base::Array<uint8_t, 6>.
        /// 原理是将 MAC 地址拷贝到 base::Array<uint8_t, 6> 中。
        explicit operator base::Array<uint8_t, 6>() const;

        /// @brief 访问 MAC 地址中指定索引的值。
        /// @param index
        /// @return
        uint8_t &operator[](int index);

        /// @brief 访问 MAC 地址中指定索引的值。
        /// @param index
        /// @return
        uint8_t const &operator[](int index) const;

        /// @brief 获取 MAC 地址中的 OUI.
        /// @return
        base::Array<uint8_t, 3> Oui() const;

        /// @brief 设置 OUI.
        /// @param value
        void SetOui(base::Array<uint8_t, 3> const &value);
    };
} // namespace base
