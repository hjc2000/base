#include "Span.h"
#include <algorithm>
#include <base/stream/ReadOnlySpan.h>
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

uint8_t &base::Span::operator[](int index) const
{
    if (index < 0 || index >= _size)
    {
        throw std::out_of_range{"索引超出范围"};
    }

    return _buffer[index];
}

uint8_t *base::Span::Buffer() const
{
    return _buffer;
}

int base::Span::Size() const
{
    return _size;
}

base::Span base::Span::Slice(int start, int size) const
{
    if (start + size > _size)
    {
        throw std::out_of_range{"切片超出范围"};
    }

    return base::Span{_buffer + start, size};
}

void base::Span::Reverse() const
{
    std::reverse(_buffer, _buffer + _size);
}

#pragma region CopyFrom

void base::Span::CopyFrom(int start, base::Span const &span) const
{
    if (start + span.Size() > _size)
    {
        throw std::out_of_range{"本 Span 装不下传进来的这个 Span."};
    }

    std::copy(span.Buffer(),
              span.Buffer() + span.Size(),
              _buffer + start);
}

void base::Span::CopyFrom(base::Span const &span) const
{
    CopyFrom(0, span);
}

void base::Span::CopyFrom(int start, base::ReadOnlySpan const &span) const
{
    CopyFrom(start, span.Buffer(), 0, span.Size());
}

void base::Span::CopyFrom(base::ReadOnlySpan const &span) const
{
    CopyFrom(0, span);
}

void base::Span::CopyFrom(int start, std::initializer_list<uint8_t> const &list) const
{
    if (start + static_cast<int>(list.size()) > _size)
    {
        throw std::out_of_range{
            std::string{"本 Span 无法在"} +
                " start = " +
                std::to_string(start) +
                " 时放下该初始化列表。",
        };
    }

    int i = start;
    for (uint8_t num : list)
    {
        _buffer[i++] = num;
    }
}

void base::Span::CopyFrom(int start, uint8_t const *buffer, int offset, int count) const
{
    if (start + count > _size)
    {
        throw std::out_of_range{"本 Span 装不下传进来的这个缓冲区。"};
    }

    std::copy(buffer + offset,
              buffer + offset + count,
              _buffer + start);
}

#pragma endregion

std::shared_ptr<base::IEnumerator<uint8_t>> base::Span::GetEnumerator()
{
    class Enumerator :
        public base::IEnumerator<uint8_t>
    {
    private:
        Span *_span = nullptr;
        bool _first_move = true;
        int _index = 0;

    public:
        Enumerator(Span *span)
        {
            _span = span;
            Reset();
        }

        /// @brief 获取当前值的引用
        /// @return
        uint8_t &CurrentValue() override
        {
            return (*_span)[_index];
        }

        /// @brief 迭代器前进到下一个值
        /// @return
        bool MoveNext() override
        {
            if (_first_move)
            {
                _first_move = false;
            }
            else
            {
                _index++;
            }

            return _index < _span->Size();
        }

        /// @brief 将迭代器重置到容器开始的位置。
        /// @note 开始位置是第一个元素前。也就是说重置后，要调用一次 MoveNext 才能获取到第一个值。
        void Reset() override
        {
            _first_move = true;
            _index = 0;
        }
    };

    return std::shared_ptr<IEnumerator<uint8_t>>{new Enumerator{this}};
}
