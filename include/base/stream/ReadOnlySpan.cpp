#include "ReadOnlySpan.h"
#include <base/string/define.h>
#include <stdexcept>

base::ReadOnlySpan::ReadOnlySpan(uint8_t const *buffer, int32_t size)
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

uint8_t const &base::ReadOnlySpan::operator[](int32_t index) const
{
	if (index < 0 || index >= _size)
	{
		throw std::out_of_range{std::string{CODE_POS_STR} + "索引超出范围"};
	}

	return _buffer[index];
}

uint8_t const *base::ReadOnlySpan::Buffer() const
{
	return _buffer;
}

int32_t base::ReadOnlySpan::Size() const
{
	return _size;
}

base::ReadOnlySpan base::ReadOnlySpan::Slice(int32_t start, int32_t size) const
{
	if (start + size > _size)
	{
		throw std::out_of_range{std::string{CODE_POS_STR} + "切片超出范围"};
	}

	return base::ReadOnlySpan{_buffer + start, size};
}

std::shared_ptr<base::IEnumerator<uint8_t const>> base::ReadOnlySpan::GetEnumerator()
{
	class Enumerator :
		public base::IEnumerator<uint8_t const>
	{
	private:
		ReadOnlySpan *_span = nullptr;
		bool _first_move = true;
		int32_t _index = 0;

	public:
		Enumerator(ReadOnlySpan *span)
		{
			_span = span;
			Reset();
		}

		/// @brief 获取当前值的引用
		/// @return
		uint8_t const &CurrentValue() override
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

	return std::shared_ptr<IEnumerator<uint8_t const>>{new Enumerator{this}};
}

int32_t base::ReadOnlySpan::IndexOf(uint8_t value) const
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
