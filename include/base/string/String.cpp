#include "String.h"
#include "base/container/Range.h"
#include <stdexcept>

bool base::String::IsWhiteChar(char value)
{
	switch (value)
	{
	case ' ':
	case '\t':
	case '\r':
	case '\n':
		{
			return true;
		}
	}

	return false;
}

base::String::String(std::string const &o)
{
	_string = o;
}

base::String::String(char o)
{
	_string = o;
}

base::String::String(char const *str)
{
	_string = std::string{str};
}

base::String::String(base::ReadOnlySpan const &o)
{
	_string = std::string{
		reinterpret_cast<char const *>(o.Buffer()),
		static_cast<size_t>(o.Size()),
	};
}

base::String::String(base::Span const &o)
	: String(base::ReadOnlySpan{o})
{
}

std::string &base::String::StdString()
{
	return _string;
}

std::string const &base::String::StdString() const
{
	return _string;
}

char &base::String::operator[](int32_t index)
{
	if (_string.size() > INT32_MAX)
	{
		throw std::out_of_range{"字符串过大，请优化设计，不要直接占用 2GiB 内存。"};
	}

	if (index > static_cast<int32_t>(_string.size()))
	{
		throw std::out_of_range{"索引超出范围。"};
	}

	return _string[index];
}

char const &base::String::operator[](int32_t index) const
{
	return const_cast<base::String &>(*this)[index];
}

base::String base::String::operator[](base::Range const &range) const
{
	return Slice(range);
}

base::String &base::String::operator+=(base::String const &o)
{
	_string += o.StdString();
	return *this;
}

base::String base::String::operator+(base::String const &o) const
{
	std::string ret;
	ret.reserve(_string.size() + o.StdString().size());
	ret = _string + o.StdString();
	return base::String{ret};
}

bool base::String::operator==(base::String const &o) const
{
	return _string == o._string;
}

bool base::String::operator<(base::String const &o) const
{
	return _string < o._string;
}

bool base::String::operator>(base::String const &o) const
{
	return _string > o._string;
}

bool base::String::operator<=(base::String const &o) const
{
	return _string <= o._string;
}

bool base::String::operator>=(base::String const &o) const
{
	return _string <= o._string;
}

int32_t base::String::Length() const
{
	return _string.size();
}

base::List<base::String> base::String::Split(char separator, base::StringSplitOptions const &options) const
{
	if (_string.size() > INT32_MAX)
	{
		throw std::out_of_range{"字符串过大，请优化设计，不要直接占用 2GiB 内存。"};
	}

	base::List<base::String> ret;

	base::ReadOnlySpan span{
		reinterpret_cast<uint8_t const *>(_string.data()),
		static_cast<int32_t>(_string.size()),
	};

	/// @brief 在设定的选项下将字符串添加到列表中
	/// @param o 要被添加的字符串的引用。将会根据 options 对其进行修改后添加到 ret
	/// 列表中。
	auto AddToListUnderOptions = [&](base::String &o)
	{
		if (options.trim_each_substring)
		{
			o.Trim();
		}

		if (options.remove_empty_substring && o == "")
		{
			return;
		}

		ret.Add(o);
	};

	while (true)
	{
		int32_t index = span.IndexOf(separator);
		if (index < 0)
		{
			// 找不到分隔符，将剩余的整个 span 作为一个字符串。
			base::String temp_str{span};
			AddToListUnderOptions(temp_str);
			return ret;
		}

		// 找到分隔符
		base::String temp_str{span[base::Range{0, index}]};
		AddToListUnderOptions(temp_str);
		if (index + 1 >= span.Size())
		{
			// 已经到达末尾了，没有剩余字符了
			if (_string[_string.size() - 1] == separator)
			{
				// 如果以分隔符结尾，还需要末尾再添加一个空字符串。
				base::String temp_str{""};
				AddToListUnderOptions(temp_str);
			}

			return ret;
		}

		span = span[base::Range{index + 1, span.Size()}];
	}
}

void base::String::TrimStart()
{
	if (_string.size() > INT32_MAX)
	{
		throw std::out_of_range{"字符串过大，请优化设计，不要直接占用 2GiB 内存。"};
	}

	if (_string.size() == 0)
	{
		return;
	}

	for (int32_t i = 0; i < static_cast<int32_t>(_string.size()); i++)
	{
		if (!IsWhiteChar(_string[i]))
		{
			Remove(base::Range{0, i});
			return;
		}
	}
}

void base::String::TrimEnd()
{
	if (_string.size() > INT32_MAX)
	{
		throw std::out_of_range{"字符串过大，请优化设计，不要直接占用 2GiB 内存。"};
	}

	if (_string.size() == 0)
	{
		return;
	}

	for (int32_t i = Length() - 1; i >= 0; i--)
	{
		if (!IsWhiteChar(_string[i]))
		{
			if (i == Length() - 1)
			{
				// 最后一个字符就是非空白字符
				return;
			}

			Remove(base::Range{i + 1, Length()});
			return;
		}
	}
}

void base::String::Trim()
{
	TrimStart();
	TrimEnd();
}

int32_t base::String::IndexOf(char match) const
{
	return Span().IndexOf(match);
}

int32_t base::String::IndexOf(int32_t start, char match) const
{
	return Span().IndexOf(start, match);
}

int32_t base::String::IndexOf(base::String const &match) const
{
	return Span().IndexOf(match.Span());
}

int32_t base::String::IndexOf(int32_t start, base::String const &match) const
{
	return Span().IndexOf(start, match.Span());
}

int32_t base::String::LastIndexOf(uint8_t match) const
{
	return Span().LastIndexOf(match);
}

int32_t base::String::LastIndexOf(int32_t start, uint8_t match) const
{
	return Span().LastIndexOf(start, match);
}

int32_t base::String::LastIndexOf(base::String const &match) const
{
	return Span().LastIndexOf(match.Span());
}

int32_t base::String::LastIndexOf(int32_t start, base::String const &match) const
{
	return Span().LastIndexOf(start, match.Span());
}

bool base::String::Contains(char match) const
{
	return IndexOf(match) >= 0;
}

bool base::String::Contains(base::String const &match) const
{
	return IndexOf(match) >= 0;
}

base::Span base::String::Span()
{
	return base::Span{
		reinterpret_cast<uint8_t *>(_string.data()),
		static_cast<int32_t>(_string.size()),
	};
}

base::ReadOnlySpan base::String::Span() const
{
	return base::ReadOnlySpan{
		reinterpret_cast<uint8_t const *>(_string.data()),
		static_cast<int32_t>(_string.size()),
	};
}

base::String base::String::Slice(base::Range const &range) const
{
	if (_string.size() > INT32_MAX)
	{
		throw std::out_of_range{"字符串过大，请优化设计，不要直接占用 2GiB 内存。"};
	}

	std::string ret{
		_string.data() + range.Begin(),
		static_cast<size_t>(range.Size()),
	};

	return base::String{ret};
}

void base::String::Reverse()
{
	std::reverse(_string.data(), _string.data() + _string.size());
}

void base::String::Remove(base::Range const &range)
{
	_string.erase(range.Begin(), range.Size());
}

void base::String::RemoveAt(int32_t index)
{
	_string.erase(index, 1);
}

void base::String::Replace(base::Range const &range, base::String const &replacement)
{
	_string.replace(range.Begin(), range.Size(), replacement.StdString());
}

void base::String::Replace(base::String const &match, base::String const &replacement)
{
	int32_t start = 0;
	while (true)
	{
		if (start >= Length())
		{
			return;
		}

		int32_t index = IndexOf(start, match);
		if (index < 0)
		{
			return;
		}

		Replace(base::Range{index, index + match.Length()}, replacement);
		start = index + replacement.Length();
	}
}

void base::String::ToLower()
{
	std::transform(_string.begin(),
				   _string.end(),
				   _string.begin(),
				   ::tolower);
}

void base::String::ToUpper()
{
	std::transform(_string.begin(),
				   _string.end(),
				   _string.begin(),
				   ::toupper);
}

bool base::String::StartWith(char match) const
{
	if (Length() == 0)
	{
		return false;
	}

	return _string[0] == match;
}

bool base::String::StartWith(base::String const &match) const
{
	int32_t index = IndexOf(match);
	return index == 0;
}

bool base::String::EndWith(char match) const
{
	if (Length() == 0)
	{
		return false;
	}

	return _string[_string.size() - 1] == match;
}

bool base::String::EndWith(base::String const &match) const
{
	int32_t index = LastIndexOf(match);
	if (index < 0)
	{
		return false;
	}

	return index == Length() - match.Length();
}

base::String operator+(char left, base::String const &right)
{
	return base::String{left + right.StdString()};
}

base::String operator+(std::string const &left, base::String const &right)
{
	return base::String{left + right.StdString()};
}

std::ostream &operator<<(std::ostream &os, base::String const &str)
{
	os << str.StdString();
	return os;
}
