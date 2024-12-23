#include "String.h"
#include <base/stream/ReadOnlySpan.h>

base::String::String(std::string const &o)
{
	_string = o;
}

base::String::String(char o)
{
	_string = o;
}

base::String::String(String const &o)
{
	*this = o;
}

base::String &base::String::operator=(String const &o)
{
	_string = o._string;
	return *this;
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
		throw std::out_of_range{"字符串过大，请优化设计，不要直接占用 2GB 内存。"};
	}

	if (index > static_cast<int32_t>(_string.size()))
	{
		throw std::out_of_range{"索引超出范围。"};
	}

	return _string[index];
}

char const &base::String::operator[](int32_t index) const
{
	if (_string.size() > INT32_MAX)
	{
		throw std::out_of_range{"字符串过大，请优化设计，不要直接占用 2GB 内存。"};
	}

	if (index > static_cast<int32_t>(_string.size()))
	{
		throw std::out_of_range{"索引超出范围。"};
	}

	return _string[index];
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

int32_t base::String::Length() const
{
	return _string.size();
}

base::List<std::string> base::String::Split(char separator) const
{
	if (_string.size() > INT32_MAX)
	{
		throw std::out_of_range{"字符串过大，请优化设计，不要直接占用 2GB 内存。"};
	}

	base::List<std::string> ret;

	base::ReadOnlySpan span{
		reinterpret_cast<uint8_t const *>(_string.data()),
		static_cast<int32_t>(_string.size()),
	};

	while (span.Size() > 0)
	{
		int32_t index = span.IndexOf(separator);
		if (index < 0)
		{
			// 找不到分隔符，将剩余的整个 span 放到一个字符串中。
			std::string temp_str{reinterpret_cast<char const *>(span.Buffer()), span.Size()};
			ret.Add(temp_str);
			break;
		}

		// 找到分隔符
		base::ReadOnlySpan sub_span = span.Slice(0, index);
		std::string temp_str{reinterpret_cast<char const *>(sub_span.Buffer()), sub_span.Size()};
		ret.Add(temp_str);
		span = span.Slice(index + 1, span.Size() - (index + 1));
	}

	return ret;
}

base::String operator+(std::string const &left, base::String const &right)
{
	return base::String{right + left};
}

std::ostream &operator<<(std::ostream &os, base::String const &str)
{
	os << str.StdString();
	return os;
}
