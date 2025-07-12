#include "ReadOnlySpan.h"
#include "base/container/Range.h"
#include "base/string/String.h"
#include <algorithm>
#include <cstdint>

/* #region 构造函数 */

base::ReadOnlySpan::ReadOnlySpan(base::String const &str)
{
	base::ReadOnlySpan span = str.Span();
	*this = span;
}

base::ReadOnlySpan::ReadOnlySpan(base::Span const &o)
{
	_buffer = o.Buffer();
	_size = o.Size();
}

/* #endregion */

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

/* #endregion */
