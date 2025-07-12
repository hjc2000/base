#include "Span.h"
#include "base/stream/ReadOnlySpan.h"
#include "base/string/String.h"

/* #region 生命周期 */

base::Span::Span(base::String &str)
{
	base::Span span = str.Span();
	*this = span;
}

/* #endregion */

/* #region 索引器 */

base::Span base::Span::operator[](base::Range const &range) const
{
	return Slice(range);
}

/* #endregion */

std::shared_ptr<base::IEnumerator<uint8_t>> base::Span::GetEnumerator()
{
	class Enumerator :
		public base::IEnumerator<uint8_t>
	{
	private:
		Span *_span = nullptr;
		int32_t _index = 0;

	public:
		Enumerator(Span *span)
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
		virtual uint8_t &CurrentValue() override
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

	return std::shared_ptr<IEnumerator<uint8_t>>{new Enumerator{this}};
}

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
