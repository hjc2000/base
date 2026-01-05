#include "KeyValueString.h"
#include "base/string/define.h"
#include "base/string/StringSplitOptions.h"
#include <exception>
#include <stdexcept>

base::KeyValueString::KeyValueString(base::String const key_value_string)
{
	try
	{
		base::StringSplitOptions options;
		options.remove_empty_substring = false;
		options.trim_each_substring = true;
		auto strs = key_value_string.Split('=', options);
		if (strs.Count() < 2)
		{
			throw std::invalid_argument{CODE_POS_STR + "非法键值对字符串。"};
		}

		_key = strs[0];
		_value = strs[1];
		CheckKeyValue();
	}
	catch (std::exception const &e)
	{
		throw std::runtime_error{CODE_POS_STR + e.what()};
	}
}

base::KeyValueString::KeyValueString(base::String const &key, base::String const &value)
{
	try
	{
		_key = key;
		_value = value;
		CheckKeyValue();
	}
	catch (std::exception const &e)
	{
		throw std::runtime_error{CODE_POS_STR + e.what()};
	}
}

void base::KeyValueString::CheckKeyValue() const
{
	if (_key.Contains('=') || _value.Contains('='))
	{
		throw std::invalid_argument{CODE_POS_STR + "键和值不能含有 '=' 字符"};
	}
}
