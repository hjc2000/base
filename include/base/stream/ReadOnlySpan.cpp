#include "ReadOnlySpan.h"
#include <stdexcept>

base::ReadOnlySpan::ReadOnlySpan(uint8_t const *buffer, int size)
{
    _buffer = buffer;
    _size = size;
}

base::ReadOnlySpan::ReadOnlySpan(base::Span const &o)
{
    _buffer = o.Buffer();
    _size = o.Size();
}

base::ReadOnlySpan::ReadOnlySpan(ReadOnlySpan const &o)
{
    *this = o;
}

base::ReadOnlySpan &base::ReadOnlySpan::operator=(ReadOnlySpan const &o)
{
    _buffer = o._buffer;
    _size = o._size;
    return *this;
}

uint8_t base::ReadOnlySpan::operator[](int index) const
{
    if (index < 0 || index >= _size)
    {
        throw std::out_of_range{"索引超出范围"};
    }

    return _buffer[index];
}

uint8_t const *base::ReadOnlySpan::Buffer() const
{
    return _buffer;
}

int base::ReadOnlySpan::Size() const
{
    return _size;
}

base::ReadOnlySpan base::ReadOnlySpan::Slice(int start, int size) const
{
    if (start + size > _size)
    {
        throw std::out_of_range{"切片超出范围"};
    }

    return base::ReadOnlySpan{_buffer + start, size};
}
