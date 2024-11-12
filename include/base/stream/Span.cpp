#include "Span.h"
#include <stdexcept>

base::Span::Span(uint8_t *buffer, int size)
{
    if (buffer == nullptr)
    {
        throw std::invalid_argument{"buffer 不能是空指针"};
    }

    if (size <= 0)
    {
        throw std::invalid_argument{"size 不能 <=0."};
    }

    _buffer = buffer;
    _size = size;
}

base::Span::Span(Span const &o)
{
    *this = o;
}

base::Span &base::Span::operator=(Span const &o)
{
    _buffer = o._buffer;
    _size = o._size;
    return *this;
}

uint8_t &base::Span::operator[](int index)
{
    if (index < 0 || index >= _size)
    {
        throw std::out_of_range{"索引超出范围"};
    }

    return _buffer[index];
}

uint8_t base::Span::operator[](int index) const
{
    if (index < 0 || index >= _size)
    {
        throw std::out_of_range{"索引超出范围"};
    }

    return _buffer[index];
}

uint8_t *base::Span::Buffer()
{
    return _buffer;
}

uint8_t const *base::Span::Buffer() const
{
    return _buffer;
}
