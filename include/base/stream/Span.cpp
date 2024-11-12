#include "Span.h"
#include <algorithm>
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

int base::Span::Size() const
{
    return _size;
}

base::Span base::Span::Slice(int start, int size)
{
    if (start + size > _size)
    {
        throw std::out_of_range{"切片超出范围"};
    }

    return base::Span{_buffer + start, size};
}

void base::Span::Reverse()
{
    std::reverse(_buffer, _buffer + _size);
}

void base::Span::CopyFrom(int start, base::Span const &span)
{
    if (start + span.Size() > _size)
    {
        throw std::out_of_range{"本 Span 装不下传进来的这个 Span."};
    }

    std::copy(span.Buffer(),
              span.Buffer() + span.Size(),
              _buffer + start);
}
