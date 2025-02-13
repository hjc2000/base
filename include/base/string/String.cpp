#include "String.h"

#pragma region 生命周期

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

base::String::String(String const &o)
{
	*this = o;
}

base::String &base::String::operator=(String const &o)
{
	_string = o._string;
	return *this;
}

#pragma endregion

#pragma region StdString

std::string &base::String::StdString()
{
	return _string;
}

std::string const &base::String::StdString() const
{
	return _string;
}

#pragma endregion

#pragma region operator[]

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

#pragma endregion

#pragma region 加法运算符

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

#pragma endregion

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
			o = o.Trim();
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

#pragma region Trim

base::String base::String::TrimStart() const
{
	if (_string.size() > INT32_MAX)
	{
		throw std::out_of_range{"字符串过大，请优化设计，不要直接占用 2GiB 内存。"};
	}

	if (_string.size() == 0)
	{
		return base::String{};
	}

	for (int32_t i = 0; i < static_cast<int32_t>(_string.size()); i++)
	{
		if (!IsWhiteChar(_string[i]))
		{
			std::string ret{_string.data() + i, _string.size() - i};
			return base::String{ret};
		}
	}

	// 遍历完所有字符后都没有找到一个非空白字符，返回空字符串。
	return base::String{};
}

base::String base::String::TrimEnd() const
{
	if (_string.size() > INT32_MAX)
	{
		throw std::out_of_range{"字符串过大，请优化设计，不要直接占用 2GiB 内存。"};
	}

	if (_string.size() == 0)
	{
		return base::String{};
	}

	for (int32_t i = _string.size() - 1; i >= 0; i--)
	{
		if (!IsWhiteChar(_string[i]))
		{
			std::string ret{_string.data(), static_cast<size_t>(i + 1)};
			return ret;
		}
	}

	// 到索引 0 处仍然是空白字符，说明整个字符串都是空白字符。直接返回空字符串。
	return base::String{};
}

base::String base::String::Trim() const
{
	base::String ret = TrimStart();
	ret = ret.TrimEnd();
	return ret;
}

#pragma endregion

#pragma region IndexOf

int32_t base::String::IndexOf(char match) const
{
	return AsReadOnlySpan().IndexOf(match);
}

int32_t base::String::IndexOf(int32_t start, char match) const
{
	return AsReadOnlySpan().IndexOf(start, match);
}

int32_t base::String::IndexOf(base::String const &match) const
{
	return AsReadOnlySpan().IndexOf(match.AsReadOnlySpan());
}

int32_t base::String::IndexOf(int32_t start, base::String const &match) const
{
	return AsReadOnlySpan().IndexOf(start, match.AsReadOnlySpan());
}

#pragma endregion

#pragma region Contains

bool base::String::Contains(char match) const
{
	return IndexOf(match) >= 0;
}

bool base::String::Contains(base::String const &match) const
{
	return IndexOf(match) >= 0;
}

#pragma endregion

#pragma region AsSpan

base::Span base::String::AsSpan()
{
	return base::Span{
		reinterpret_cast<uint8_t *>(_string.data()),
		static_cast<int32_t>(_string.size()),
	};
}

base::ReadOnlySpan base::String::AsReadOnlySpan() const
{
	return base::ReadOnlySpan{
		reinterpret_cast<uint8_t const *>(_string.data()),
		static_cast<int32_t>(_string.size()),
	};
}

#pragma endregion

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

#pragma region 移除

void base::String::Remove(base::Range const &range)
{
	_string.erase(range.Begin(), range.Size());
}

void base::String::RemoveAt(int32_t index)
{
	_string.erase(index, 1);
}

#pragma endregion

#pragma region 重载全局运算符

base::String operator+(std::string const &left, base::String const &right)
{
	return base::String{right + left};
}

std::ostream &operator<<(std::ostream &os, base::String const &str)
{
	os << str.StdString();
	return os;
}

#pragma endregion
