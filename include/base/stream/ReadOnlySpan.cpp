#include "ReadOnlySpan.h"
#include "base/container/Range.h"
#include "base/string/String.h"
#include <algorithm>
#include <cstdint>

/* #region 生命周期 */

base::ReadOnlySpan::ReadOnlySpan(uint8_t const *buffer, int32_t size)
{
	_buffer = buffer;
	_size = size;

	if (_buffer == nullptr)
	{
		_size = 0;
	}
}

base::ReadOnlySpan::ReadOnlySpan(char const *str)
{
	int32_t white_char_index = 0;
	while (true)
	{
		if (str[white_char_index] == '\0')
		{
			break;
		}

		white_char_index++;
	}

	_buffer = reinterpret_cast<uint8_t const *>(str);
	_size = white_char_index;
}

base::ReadOnlySpan::ReadOnlySpan(base::String const &str)
{
	base::ReadOnlySpan span = str.Span();
	*this = span;
}

base::ReadOnlySpan::ReadOnlySpan(base::ArraySpan<uint8_t> const &span)
{
	_buffer = span.Buffer();
	_size = span.Count();

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

/* #endregion */

/* #region 索引器 */

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

/* #endregion */

uint8_t const *base::ReadOnlySpan::Buffer() const
{
	return _buffer;
}

int32_t base::ReadOnlySpan::Size() const
{
	return _size;
}

std::shared_ptr<base::IEnumerator<uint8_t const>> base::ReadOnlySpan::GetEnumerator()
{
	class Enumerator :
		public base::IEnumerator<uint8_t const>
	{
	private:
		ReadOnlySpan *_span = nullptr;
		int32_t _index = 0;

	public:
		Enumerator(ReadOnlySpan *span)
		{
			_span = span;
		}

		///
		/// @brief 迭代器当前是否指向尾后元素。
		///
		/// @return
		///
		virtual bool IsEnd() const override
		{
			return _index == _span->Size();
		}

		///
		/// @brief 获取当前值的引用。
		///
		/// @return ItemType&
		///
		virtual uint8_t const &CurrentValue() override
		{
			return (*_span)[_index];
		}

		///
		/// @brief 递增迭代器的位置。
		///
		///
		virtual void Add() override
		{
			++_index;
		}
	};

	return std::shared_ptr<IEnumerator<uint8_t const>>{new Enumerator{this}};
}

/* #region Slice */

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

/* #endregion */

/* #region IndexOf */

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

	if (start >= Size())
	{
		throw std::invalid_argument{CODE_POS_STR + "start 索引超出边界，大于 Size."};
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
	if (start < 0)
	{
		throw std::invalid_argument{CODE_POS_STR + "start 不能小于 0."};
	}

	if (start >= Size())
	{
		throw std::invalid_argument{CODE_POS_STR + "start 索引超出边界，大于 Size."};
	}

	int32_t result = Slice(base::Range{start, _size}).IndexOf(match);
	if (result < 0)
	{
		return result;
	}

	return start + result;
}

/* #endregion */

/* #region LastIndexOf */

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

	if (start >= Size())
	{
		throw std::invalid_argument{CODE_POS_STR + "start 索引超出边界，大于 Size."};
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

	if (start >= Size())
	{
		throw std::invalid_argument{CODE_POS_STR + "start 索引超出边界，大于 Size."};
	}

	int32_t result = Slice(base::Range{0, start + 1}).LastIndexOf(match);
	return result;
}

/* #endregion */

/* #region 开始，结束 */

bool base::ReadOnlySpan::StartWith(uint8_t match)
{
	if (Size() == 0)
	{
		return false;
	}

	return _buffer[0] == match;
}

bool base::ReadOnlySpan::StartWith(base::ReadOnlySpan const &match)
{
	if (Size() < match.Size())
	{
		return false;
	}

	return Slice(base::Range{0, match.Size()}) == match;
}

bool base::ReadOnlySpan::EndWith(uint8_t match)
{
	if (Size() == 0)
	{
		return false;
	}

	return _buffer[_size - 1] == match;
}

bool base::ReadOnlySpan::EndWith(base::ReadOnlySpan const &match)
{
	if (Size() < match.Size())
	{
		return false;
	}

	return Slice(base::Range{_size - match.Size(), _size}) == match;
}

/* #endregion */

/* #region 比较 */

int32_t base::ReadOnlySpan::Compare(base::ReadOnlySpan const &another) const
{
	if (Size() == 0 && another.Size() == 0)
	{
		// 两段内存的大小都为 0，也认为相等。
		return 0;
	}

	int32_t result = memcmp(Buffer(),
							another.Buffer(),
							std::min<int32_t>(Size(), another.Size()));

	if (result == 0)
	{
		// 如果比较结果 == 0, 说明说比较的直接都相等。接下来就是谁更长，谁的字典序更后面了。
		// 如果本内存段更长，减法的结果是正数，表示本内存段应该排更后面。
		// 如果本内存段更短，减法的结果是负数，表示本内存段应该排更后面。
		return Size() - another.Size();
	}

	return result;
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

/* #endregion */
