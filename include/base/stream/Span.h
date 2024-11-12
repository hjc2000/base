#pragma once
#include <cstdint>

namespace base
{
    /// @brief 引用一段连续内存，不持有这段内存。
    /// @warning 要求本类对象的生命周期内，引用的外部内存始终存活。
    class Span
    {
    private:
        uint8_t *_buffer = nullptr;
        int _size = 0;

    public:
        /// @brief 无参构造函数。引用一段空内存。
        /// @note 可以通过 Size 属性判断本对象是否引用到了有效的内存。
        Span() = default;

        /// @brief 引用 buffer 指向的内存。在本对象的生命周期内，buffer 指向的内存必须始终存活。
        /// @param buffer 要引用的内存。
        /// @param size buffer 的大小。
        Span(uint8_t *buffer, int size);

        /// @brief 拷贝构造函数
        /// @param o
        Span(Span const &o);

        /// @brief 赋值运算符
        /// @param o
        /// @return
        Span &operator=(Span const &o);

        uint8_t &operator[](int index);
        uint8_t operator[](int index) const;

        /// @brief 所引用的内存。
        /// @return
        uint8_t *Buffer();

        /// @brief 所引用的内存。
        /// @return
        uint8_t const *Buffer() const;

        /// @brief 所引用的内存大小
        /// @return
        int Size() const;

        /// @brief 将本 Span 切片，得到一个更小的 Span.
        /// @param start 切片起始位置。
        /// @param size 切片大小。
        /// @return
        base::Span Slice(int start, int size);

        /// @brief 翻转本 Span 所引用的内存段。
        void Reverse();

        /// @brief 将 span 所引用的内存的数据拷贝到本对象所引用的内存中。
        /// @param start 要放在本对象所引用的内存中的起始位置。
        /// @param span 要被拷贝的内存段。
        void CopyFrom(int start, base::Span const &span);
    };
} // namespace base
