#include "ReadOnlySpan.h"
#include <base/string/define.h>
#include <cstring>
#include <stdexcept>

base::ReadOnlySpan::ReadOnlySpan(uint8_t const *buffer, int32_t size)
{
	_buffer = buffer;
	_size = size;

	if (_buffer == nullptr)
	{
		_size = 0;
	}
}

base::ReadOnlySpan::ReadOnlySpan(base::ReadOnlyArraySpan<uint8_t> const &span)
{
	_buffer = span.Buffer();
	_size = span.Count();

	if (_buffer == nullptr)
	{
		_size = 0;
	}
}

base::ReadOnlySpan::ReadOnlySpan(base::Span const &o)
{
	_buffer = o.Buffer();
	_size = o.Size();
}

uint8_t const &base::ReadOnlySpan::operator[](int32_t index) const
{
	if (index < 0 || index >= _size)
	{
		throw std::out_of_range{CODE_POS_STR + "索引超出范围"};
	}

	return _buffer[index];
}

base::ReadOnlySpan base::ReadOnlySpan::operator[](base::Range const &range) const
{
	return Slice(range);
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
		throw std::out_of_range{CODE_POS_STR + "切片超出范围"};
	}

	return base::ReadOnlySpan{_buffer + start, size};
}

base::ReadOnlySpan base::ReadOnlySpan::Slice(base::Range const &range) const
{
	return Slice(range.Begin(), range.Size());
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

int32_t base::ReadOnlySpan::IndexOf(uint8_t match) const
{
	for (int32_t i = 0; i < _size; i++)
	{
		if (_buffer[i] == match)
		{
			return i;
		}
	}

	return -1;
}

int32_t base::ReadOnlySpan::IndexOf(int32_t start, uint8_t match) const
{
	if (start < 0)
	{
		throw std::invalid_argument{CODE_POS_STR + "start 不能小于 0."};
	}

	int32_t result = Slice(base::Range{start, _size}).IndexOf(match);
	if (result < 0)
	{
		return result;
	}

	return start + result;
}

int32_t base::ReadOnlySpan::IndexOf(base::ReadOnlySpan const &match) const
{
	if (match.Size() == 0)
	{
		throw std::invalid_argument{CODE_POS_STR + "match 的长度不能是 0."};
	}

	if (Size() < match.Size())
	{
		// 本内存段的大小还没 match 的大，不可能匹配。
		return -1;
	}

	uint8_t const first_byte_of_match = match[0];
	for (int32_t i = 0; i < Size(); i++)
	{
		if (i + match.Size() > Size())
		{
			// 剩下的未匹配的部分已经没有 match 的长的，不可能匹配了。
			return -1;
		}

		if (_buffer[i] == first_byte_of_match)
		{
			// 匹配到第 1 个字符了。
			if (Slice(i, match.Size()) == match)
			{
				return i;
			}
		}
	}

	return -1;
}

int32_t base::ReadOnlySpan::IndexOf(int32_t start, base::ReadOnlySpan const &match) const
{
	int32_t result = Slice(base::Range{start, _size}).IndexOf(match);
	if (result < 0)
	{
		return result;
	}

	return start + result;
}

int32_t base::ReadOnlySpan::LastIndexOf(uint8_t match) const
{
	for (int32_t i = _size - 1; i >= 0; i--)
	{
		if (_buffer[i] == match)
		{
			return i;
		}
	}

	return -1;
}

int32_t base::ReadOnlySpan::LastIndexOf(int32_t start, uint8_t match) const
{
	if (start < 0)
	{
		throw std::invalid_argument{CODE_POS_STR + "start 不能小于 0."};
	}

	int32_t result = Slice(base::Range{0, start + 1}).LastIndexOf(match);
	return result;
}

int32_t base::ReadOnlySpan::LastIndexOf(base::ReadOnlySpan const &match) const
{
	if (match.Size() == 0)
	{
		throw std::invalid_argument{CODE_POS_STR + "match 的长度不能是 0."};
	}

	if (Size() < match.Size())
	{
		// 本内存段的大小还没 match 的大，不可能匹配。
		return -1;
	}

	uint8_t const first_byte_of_match = match[0];
	for (int32_t i = Size() - match.Size(); i >= 0; i--)
	{
		if (_buffer[i] == first_byte_of_match)
		{
			// 匹配到第 1 个字符了。
			if (Slice(i, match.Size()) == match)
			{
				return i;
			}
		}
	}

	return -1;
}

int32_t base::ReadOnlySpan::LastIndexOf(int32_t start, base::ReadOnlySpan const &match) const
{
	if (start < 0)
	{
		throw std::invalid_argument{CODE_POS_STR + "start 不能小于 0."};
	}

	int32_t result = Slice(base::Range{0, start + 1}).LastIndexOf(match);
	return result;
}

int32_t base::ReadOnlySpan::Compare(base::ReadOnlySpan const &another) const
{
	if (Size() != another.Size())
	{
		throw std::invalid_argument{CODE_POS_STR + "两段大小相等的内存才可以比较。"};
	}

	if (Size() == 0)
	{
		// 两段内存的大小都为 0，也认为相等。
		return 0;
	}

	return memcmp(_buffer, another.Buffer(), _size);
}

int32_t base::ReadOnlySpan::Compare(base::Span const &another) const
{
	return Compare(base::ReadOnlySpan{another});
}

bool base::ReadOnlySpan::operator==(base::ReadOnlySpan const &another) const
{
	return Compare(another) == 0;
}

bool base::ReadOnlySpan::operator==(base::Span const &another) const
{
	return Compare(another) == 0;
}

bool base::ReadOnlySpan::operator<(base::ReadOnlySpan const &another) const
{
	return Compare(another) < 0;
}

bool base::ReadOnlySpan::operator<(base::Span const &another) const
{
	return Compare(another) < 0;
}

bool base::ReadOnlySpan::operator>(base::ReadOnlySpan const &another) const
{
	return Compare(another) > 0;
}

bool base::ReadOnlySpan::operator>(base::Span const &another) const
{
	return Compare(another) > 0;
}

bool base::ReadOnlySpan::operator<=(base::ReadOnlySpan const &another) const
{
	return Compare(another) <= 0;
}

bool base::ReadOnlySpan::operator<=(base::Span const &another) const
{
	return Compare(another) <= 0;
}

bool base::ReadOnlySpan::operator>=(base::ReadOnlySpan const &another) const
{
	return Compare(another) >= 0;
}

bool base::ReadOnlySpan::operator>=(base::Span const &another) const
{
	return Compare(another) >= 0;
}
