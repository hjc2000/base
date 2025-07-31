#include "Span.h"
#include "base/stream/ReadOnlySpan.h"

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
	if (static_cast<int64_t>(list.size()) != _size)
	{
		throw std::invalid_argument{CODE_POS_STR + "list 的大小和本对象不一致。"};
	}

	int64_t i = 0;
	for (uint8_t const &value : list)
	{
		_buffer[i] = value;
		i++;
	}
}

/* #endregion */

/* #region IndexOf */

int64_t base::Span::IndexOf(uint8_t match) const
{
	return base::ReadOnlySpan{*this}.IndexOf(match);
}

int64_t base::Span::IndexOf(int64_t start, uint8_t match) const
{
	return base::ReadOnlySpan{*this}.IndexOf(match);
}

int64_t base::Span::IndexOf(base::ReadOnlySpan const &match) const
{
	return base::ReadOnlySpan{*this}.IndexOf(match);
}

int64_t base::Span::IndexOf(int64_t start, base::ReadOnlySpan const &match) const
{
	return base::ReadOnlySpan{*this}.IndexOf(match);
}

/* #endregion */

/* #region LastIndexOf */

int64_t base::Span::LastIndexOf(uint8_t match) const
{
	return base::ReadOnlySpan{*this}.LastIndexOf(match);
}

int64_t base::Span::LastIndexOf(int64_t start, uint8_t match) const
{
	return base::ReadOnlySpan{*this}.LastIndexOf(start, match);
}

int64_t base::Span::LastIndexOf(base::ReadOnlySpan const &match) const
{
	return base::ReadOnlySpan{*this}.LastIndexOf(match);
}

int64_t base::Span::LastIndexOf(int64_t start, base::ReadOnlySpan const &match) const
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

int64_t base::Span::Compare(base::ReadOnlySpan const &another) const
{
	return base::ReadOnlySpan{*this}.Compare(another);
}

int64_t base::Span::Compare(base::Span const &another) const
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
