#include "KeyValueString.h"
#include "base/string/define.h"
#include "base/string/StringSplitOptions.h"
#include <stdexcept>

base::KeyValueString::KeyValueString(base::String const key_value_string)
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

base::KeyValueString::KeyValueString(base::String const &key, base::String const &value)
	: _key(key),
	  _value(value)
{
	CheckKeyValue();
}

void base::KeyValueString::CheckKeyValue() const
{
	if (_key.Contains('=') || _value.Contains('='))
	{
		throw std::invalid_argument{CODE_POS_STR + "键和值不能含有 '=' 字符"};
	}
}
