#include "String.h"

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

char &base::String::operator[](size_t index)
{
	if (index > _string.size())
	{
		throw std::out_of_range{"索引超出范围。"};
	}

	return _string[index];
}

char const &base::String::operator[](size_t index) const
{
	if (index > _string.size())
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

size_t base::String::Length() const
{
	return _string.size();
}

base::String operator+(std::string const &left, base::String const &right)
{
	return base::String{right + left};
}
