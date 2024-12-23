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
			std::string temp_str{
				reinterpret_cast<char const *>(span.Buffer()),
				static_cast<size_t>(span.Size()),
			};

			ret.Add(temp_str);
			break;
		}

		// 找到分隔符
		base::ReadOnlySpan sub_span = span.Slice(0, index);

		std::string temp_str{
			reinterpret_cast<char const *>(sub_span.Buffer()),
			static_cast<size_t>(sub_span.Size()),
		};

		ret.Add(temp_str);
		span = span.Slice(index + 1, span.Size() - (index + 1));
	}

	return ret;
}

base::String base::String::TrimStart() const
{
	if (_string.size() > INT32_MAX)
	{
		throw std::out_of_range{"字符串过大，请优化设计，不要直接占用 2GB 内存。"};
	}

	if (_string.size() == 0)
	{
		return base::String{};
	}

	int32_t start_index = 0;
	while (true)
	{
		if (!IsWhiteChar(_string[start_index]))
		{
			break;
		}

		start_index++;
	}

	std::string ret{_string.data() + start_index, _string.size() - start_index};
	return base::String{ret};
}

base::String base::String::TrimEnd() const
{
	if (_string.size() > INT32_MAX)
	{
		throw std::out_of_range{"字符串过大，请优化设计，不要直接占用 2GB 内存。"};
	}

	if (_string.size() == 0)
	{
		return base::String{};
	}

	int32_t end_index = _string.size() - 1;
	while (true)
	{
		if (!IsWhiteChar(_string[end_index]))
		{
			break;
		}

		end_index--;
		if (end_index < 0)
		{
			// 到索引 0 处仍然是空白字符，说明整个字符串都是空白字符。直接返回空字符串。
			return base::String{};
		}
	}

	std::string ret{_string.data(), end_index + 1};
	return base::String{ret};
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
