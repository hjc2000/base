#include "String.h"

base::List<base::String> base::String::Split(char separator, base::StringSplitOptions const &options) const
{
	if (_string.size() > INT32_MAX)
	{
		throw std::out_of_range{"字符串过大，请优化设计，不要直接占用 2GiB 内存。"};
	}

	base::List<base::String> ret;

	/// @brief 在设定的选项下将字符串添加到列表中
	/// @param o 要被添加的字符串的引用。将会根据 options 对其进行修改后添加到 ret
	/// 列表中。
	auto add_to_list_under_options = [&](base::String &o)
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

	base::ReadOnlySpan span{
		reinterpret_cast<uint8_t const *>(_string.data()),
		static_cast<int32_t>(_string.size()),
	};

	while (true)
	{
		int32_t index = span.IndexOf(separator);
		if (index < 0)
		{
			// 找不到分隔符，将剩余的整个 span 作为一个字符串。
			base::String temp_str{span};
			add_to_list_under_options(temp_str);
			return ret;
		}

		// 找到分隔符
		base::String temp_str{span[base::Range{0, index}]};
		add_to_list_under_options(temp_str);

		if (index + 1 >= span.Size())
		{
			// 已经到达末尾了，没有剩余字符了
			if (_string[_string.size() - 1] == separator)
			{
				// 如果以分隔符结尾，还需要末尾再添加一个空字符串。
				base::String temp_str{""};
				add_to_list_under_options(temp_str);
			}

			return ret;
		}

		span = span[base::Range{index + 1, span.Size()}];
	}
}
