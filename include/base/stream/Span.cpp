#include "Span.h"
#include <algorithm>
#include <base/stream/ReadOnlySpan.h>
#include <base/string/define.h>
#include <stdexcept>

#pragma region 生命周期

base::Span::Span(uint8_t *buffer, int32_t size)
{
	if (buffer == nullptr)
	{
		throw std::invalid_argument{CODE_POS_STR + "buffer 不能是空指针"};
	}

	if (size <= 0)
	{
		throw std::invalid_argument{CODE_POS_STR + "size 不能 <=0."};
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

#pragma endregion

uint8_t &base::Span::operator[](int32_t index) const
{
	if (index < 0 || index >= _size)
	{
		throw std::out_of_range{CODE_POS_STR + "索引超出范围"};
	}

	return _buffer[index];
}

base::Span base::Span::operator[](base::Range const &range) const
{
	return Slice(range);
}

uint8_t *base::Span::Buffer() const
{
	return _buffer;
}

int32_t base::Span::Size() const
{
	return _size;
}

base::Span base::Span::Slice(int32_t start, int32_t size) const
{
	if (start + size > _size)
	{
		throw std::out_of_range{CODE_POS_STR + "切片超出范围"};
	}

	return base::Span{_buffer + start, size};
}

base::Span base::Span::Slice(base::Range const &range) const
{
	return Slice(range.Begin(), range.Size());
}

void base::Span::Reverse() const
{
	std::reverse(_buffer, _buffer + _size);
}

#pragma region CopyFrom

void base::Span::CopyFrom(int32_t start, base::Span const &span) const
{
	if (start + span.Size() > _size)
	{
		throw std::out_of_range{CODE_POS_STR + "本 Span 装不下传进来的这个 Span."};
	}

	std::copy(span.Buffer(),
			  span.Buffer() + span.Size(),
			  _buffer + start);
}

void base::Span::CopyFrom(base::Span const &span) const
{
	CopyFrom(0, span);
}

void base::Span::CopyFrom(int32_t start, base::ReadOnlySpan const &span) const
{
	CopyFrom(start, span.Buffer(), 0, span.Size());
}

void base::Span::CopyFrom(base::ReadOnlySpan const &span) const
{
	CopyFrom(0, span);
}

void base::Span::CopyFrom(int32_t start, std::initializer_list<uint8_t> const &list) const
{
	if (start + static_cast<int32_t>(list.size()) > _size)
	{
		std::string message = CODE_POS_STR +
							  std::string{"本 Span 无法在"} +
							  " start = " +
							  std::to_string(start) +
							  " 时放下该初始化列表。";

		throw std::out_of_range{message};
	}

	int32_t i = start;
	for (uint8_t num : list)
	{
		_buffer[i++] = num;
	}
}

void base::Span::CopyFrom(int32_t start, uint8_t const *buffer, int32_t offset, int32_t count) const
{
	if (start + count > _size)
	{
		throw std::out_of_range{CODE_POS_STR + "本 Span 装不下传进来的这个缓冲区。"};
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
		int32_t _index = 0;

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

void base::Span::FillWithZero()
{
	// std::fill(_buffer, _buffer + _size, 0);
	FillWith(0);
}

void base::Span::FillWith(uint8_t value)
{
	std::fill(_buffer, _buffer + _size, value);
}

int32_t base::Span::IndexOf(uint8_t value) const
{
	for (int32_t i = 0; i < _size; i++)
	{
		if (_buffer[i] == value)
		{
			return i;
		}
	}

	return -1;
}
