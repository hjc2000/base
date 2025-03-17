#include "Span.h"
#include <base/pch.h>
#include <base/stream/ReadOnlySpan.h>
#include <base/string/String.h>

/* #region 生命周期 */

base::Span::Span(uint8_t *buffer, int32_t size)
{
	_buffer = buffer;
	_size = size;

	if (_buffer == nullptr)
	{
		_size = 0;
	}
}

base::Span::Span(char *str)
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

	_buffer = reinterpret_cast<uint8_t *>(str);
	_size = white_char_index;
}

base::Span::Span(base::String &str)
{
	base::Span span = str.Span();
	*this = span;
}

base::Span::Span(base::ArraySpan<uint8_t> const &span)
{
	_buffer = span.Buffer();
	_size = span.Count();

	if (_buffer == nullptr)
	{
		_size = 0;
	}
}

/* #endregion */

/* #region 索引器 */

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

/* #endregion */

uint8_t *base::Span::Buffer() const
{
	return _buffer;
}

int32_t base::Span::Size() const
{
	return _size;
}

void base::Span::Reverse() const
{
	std::reverse(_buffer, _buffer + _size);
}

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

/* #region Slice */

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

/* #endregion */

/* #region CopyFrom */

void base::Span::CopyFrom(base::ReadOnlySpan const &span) const
{
	if (span.Size() != _size)
	{
		throw std::invalid_argument{CODE_POS_STR + "span 的大小和本对象不一致。"};
	}

	std::copy(span.Buffer(),
			  span.Buffer() + span.Size(),
			  _buffer);
}

void base::Span::CopyFrom(base::Span const &span) const
{
	CopyFrom(base::ReadOnlySpan{span});
}

void base::Span::CopyFrom(std::initializer_list<uint8_t> const &list) const
{
	if (static_cast<int32_t>(list.size()) != _size)
	{
		throw std::invalid_argument{CODE_POS_STR + "list 的大小和本对象不一致。"};
	}

	int32_t i = 0;
	for (uint8_t const &value : list)
	{
		_buffer[i] = value;
		i++;
	}
}

/* #endregion */

/* #region 填充 */

void base::Span::FillWithZero()
{
	// std::fill(_buffer, _buffer + _size, 0);
	FillWith(0);
}

void base::Span::FillWith(uint8_t value)
{
	std::fill(_buffer, _buffer + _size, value);
}

/* #endregion */

/* #region IndexOf */

int32_t base::Span::IndexOf(uint8_t match) const
{
	return base::ReadOnlySpan{*this}.IndexOf(match);
}

int32_t base::Span::IndexOf(int32_t start, uint8_t match) const
{
	return base::ReadOnlySpan{*this}.IndexOf(match);
}

int32_t base::Span::IndexOf(base::ReadOnlySpan const &match) const
{
	return base::ReadOnlySpan{*this}.IndexOf(match);
}

int32_t base::Span::IndexOf(int32_t start, base::ReadOnlySpan const &match) const
{
	return base::ReadOnlySpan{*this}.IndexOf(match);
}

/* #endregion */

/* #region LastIndexOf */

int32_t base::Span::LastIndexOf(uint8_t match) const
{
	return base::ReadOnlySpan{*this}.LastIndexOf(match);
}

int32_t base::Span::LastIndexOf(int32_t start, uint8_t match) const
{
	return base::ReadOnlySpan{*this}.LastIndexOf(start, match);
}

int32_t base::Span::LastIndexOf(base::ReadOnlySpan const &match) const
{
	return base::ReadOnlySpan{*this}.LastIndexOf(match);
}

int32_t base::Span::LastIndexOf(int32_t start, base::ReadOnlySpan const &match) const
{
	return base::ReadOnlySpan{*this}.LastIndexOf(start, match);
}

/* #endregion */

/* #region 开始，结束 */

bool base::Span::StartWith(uint8_t match)
{
	return base::ReadOnlySpan{*this}.StartWith(match);
}

bool base::Span::StartWith(base::ReadOnlySpan const &match)
{
	return base::ReadOnlySpan{*this}.StartWith(match);
}

bool base::Span::EndWith(uint8_t match)
{
	return base::ReadOnlySpan{*this}.EndWith(match);
}

bool base::Span::EndWith(base::ReadOnlySpan const &match)
{
	return base::ReadOnlySpan{*this}.EndWith(match);
}

/* #endregion */

/* #region 比较 */

int32_t base::Span::Compare(base::ReadOnlySpan const &another) const
{
	return base::ReadOnlySpan{*this}.Compare(another);
}

int32_t base::Span::Compare(base::Span const &another) const
{
	return base::ReadOnlySpan{*this}.Compare(another);
}

bool base::Span::operator==(base::ReadOnlySpan const &another) const
{
	return Compare(another) == 0;
}

bool base::Span::operator==(base::Span const &another) const
{
	return Compare(another) == 0;
}

bool base::Span::operator<(base::ReadOnlySpan const &another) const
{
	return Compare(another) < 0;
}

bool base::Span::operator<(base::Span const &another) const
{
	return Compare(another) < 0;
}

bool base::Span::operator>(base::ReadOnlySpan const &another) const
{
	return Compare(another) > 0;
}

bool base::Span::operator>(base::Span const &another) const
{
	return Compare(another) > 0;
}

bool base::Span::operator<=(base::ReadOnlySpan const &another) const
{
	return Compare(another) <= 0;
}

bool base::Span::operator<=(base::Span const &another) const
{
	return Compare(another) <= 0;
}

bool base::Span::operator>=(base::ReadOnlySpan const &another) const
{
	return Compare(another) >= 0;
}

bool base::Span::operator>=(base::Span const &another) const
{
	return Compare(another) >= 0;
}

/* #endregion */
