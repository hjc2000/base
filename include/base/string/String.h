#pragma once
#include "base/container/List.h"
#include "base/container/Range.h"
#include "base/stream/ReadOnlySpan.h"
#include "base/string/character.h"
#include "base/string/StringSplitOptions.h"
#include <cctype>
#include <cstddef>
#include <ostream>
#include <stdexcept>
#include <stdint.h>
#include <string>

namespace base
{
	///
	/// @brief 字符串长度。
	///
	///
	class StringLength
	{
	private:
		int32_t _value{};

	public:
		constexpr explicit StringLength(int32_t value)
			: _value(value)
		{
		}

		constexpr int32_t Value() const
		{
			return _value;
		}
	};

	///
	/// @brief 对 std::string 进行包装。
	///
	///
	class String

	{
	private:
		std::string _string{};

	public:
		/* #region 构造函数 */

		///
		/// @brief 无参构造函数，构造一个空字符串。
		///
		///
		String() = default;

		///
		/// @brief 从 std::string 中构造，将其内容拷贝过来。
		///
		/// @param str
		///
		String(std::string const &str)
		{
			_string = str;
		}

		///
		/// @brief 从一个字符构造。
		///
		/// @param c
		///
		String(char c)
		{
			_string = c;
		}

		///
		/// @brief 从 C 风格的字符串中构造。
		///
		/// @param str
		///
		String(char const *str)
		{
			_string = std::string{str};
		}

		///
		/// @brief 从只读内存段中构造，将其内容拷贝过来作为字符串。
		///
		/// @param span
		///
		String(base::ReadOnlySpan const &span)
		{
			_string = std::string{
				reinterpret_cast<char const *>(span.Buffer()),
				static_cast<size_t>(span.Size()),
			};
		}

		///
		/// @brief 从内存段中构造，将其内容拷贝过来作为字符串。
		///
		/// @param span
		///
		String(base::Span const &span)
			: String(base::ReadOnlySpan{span})
		{
		}

		/* #endregion */

		///
		/// @brief 获取被本类包装的 std::string 对象的引用。
		///
		/// @return
		///
		std::string &StdString()
		{
			return _string;
		}

		///
		/// @brief 获取被本类包装的 std::string 对象的引用。
		///
		/// @return
		///
		std::string const &StdString() const
		{
			return _string;
		}

		///
		/// @brief 获取本字符串的内存段。内存段中不包括结尾的空字符。
		///
		/// @return
		///
		base::Span Span()
		{
			return base::Span{
				reinterpret_cast<uint8_t *>(_string.data()),
				static_cast<int32_t>(_string.size()),
			};
		}

		///
		/// @brief 获取本字符串的内存段。内存段中不包括结尾的空字符。
		///
		/// @return
		///
		base::ReadOnlySpan Span() const
		{
			return base::ReadOnlySpan{
				reinterpret_cast<uint8_t const *>(_string.data()),
				static_cast<int32_t>(_string.size()),
			};
		}

		///
		/// @brief 字符串长度。不包括结尾的空字符。
		///
		/// @return
		///
		int32_t Length() const
		{
			return _string.size();
		}

		/* #region 索引器 */

		///
		/// @brief 获取指定索引位置的字符的引用。
		///
		/// @param index
		///
		/// @return
		///
		char &operator[](int32_t index)
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

		///
		/// @brief 获取指定索引位置的字符的引用。
		///
		/// @param index
		///
		/// @return
		///
		char const &operator[](int32_t index) const
		{
			return const_cast<base::String &>(*this)[index];
		}

		///
		/// @brief 获取指定范围内的子字符串。
		///
		/// @note 子字符串是从父字符串拷贝而来而不是引用父字符串的内存。
		///
		/// @param range
		///
		/// @return
		///
		base::String operator[](base::Range const &range) const
		{
			return Slice(range);
		}

		/* #endregion */

		base::String &operator+=(base::String const &o)
		{
			_string += o.StdString();
			return *this;
		}

		base::String operator+(base::String const &o) const
		{
			std::string ret;
			ret.reserve(_string.size() + o.StdString().size());
			ret = _string + o.StdString();
			return base::String{ret};
		}

		///
		/// @brief 根据分隔符，将字符串拆分成多个子字符串，放到列表中返回。
		///
		/// @param separator
		/// @param options
		///
		/// @return
		///
		base::List<base::String> Split(char separator,
									   base::StringSplitOptions const &options = StringSplitOptions{}) const;

		///
		/// @brief 获取指定范围内的子字符串。
		///
		/// @note 子字符串是从父字符串拷贝而来而不是引用父字符串的内存。
		///
		/// @param range
		///
		/// @return
		///
		base::String Slice(base::Range const &range) const
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

		/* #region 比较 */

		bool operator==(base::String const &o) const
		{
			return _string == o._string;
		}

		bool operator<(base::String const &o) const
		{
			return _string < o._string;
		}

		bool operator>(base::String const &o) const
		{
			return _string > o._string;
		}

		bool operator<=(base::String const &o) const
		{
			return _string <= o._string;
		}

		bool operator>=(base::String const &o) const
		{
			return _string <= o._string;
		}

		/* #endregion */

		///
		/// @brief 裁剪掉字符串开头处的空白字符。
		///
		/// @note 关于哪些是空白字符，见 IsWhiteChar 函数。
		///
		void TrimStart()
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
				if (!base::character::IsWhiteChar(_string[i]))
				{
					Remove(base::Range{0, i});
					return;
				}
			}
		}

		///
		/// @brief 裁剪掉字符串末尾处的空白字符。
		///
		/// @note 关于哪些是空白字符，见 IsWhiteChar 函数。
		///
		void TrimEnd()
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
				if (!base::character::IsWhiteChar(_string[i]))
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

		///
		/// @brief 裁剪掉字符串开头和结尾的空白字符。
		///
		/// @note 关于哪些是空白字符，见 IsWhiteChar 函数。
		///
		void Trim()
		{
			TrimStart();
			TrimEnd();
		}

		/* #region IndexOf */

		///
		/// @brief 从本字符串查找匹配项所在的索引。
		///
		/// @param match 匹配项。
		///
		/// @return 找到了返回匹配位置的索引。没找到返回 -1.
		///
		int32_t IndexOf(char match) const
		{
			return Span().IndexOf(match);
		}

		///
		/// @brief 从本字符串查找匹配项所在的索引。
		///
		/// @param start 查找的起始索引。从此处往后开始查找。
		/// @param match 匹配项。
		///
		/// @return 找到了返回匹配位置的索引。没找到返回 -1.
		///
		int32_t IndexOf(int32_t start, char match) const
		{
			return Span().IndexOf(start, match);
		}

		///
		/// @brief 从本字符串查找匹配项所在的索引。
		///
		/// @param match 匹配项。
		///
		/// @return 找到了返回匹配位置的索引。没找到返回 -1.
		///
		int32_t IndexOf(base::String const &match) const
		{
			return Span().IndexOf(match.Span());
		}

		///
		/// @brief 从本字符串查找匹配项所在的索引。
		///
		/// @param start 查找的起始索引。从此处往后开始查找。
		/// @param match 匹配项。
		///
		/// @return 找到了返回匹配位置的索引。没找到返回 -1.
		///
		int32_t IndexOf(int32_t start, base::String const &match) const
		{
			return Span().IndexOf(start, match.Span());
		}

		/* #endregion */

		/* #region LastIndexOf */

		///
		/// @brief 从后往前查找最后一个匹配项所在的索引。
		///
		/// @param match 匹配项。
		///
		/// @return 找到了返回匹配位置的索引。没找到返回 -1.
		///
		int32_t LastIndexOf(uint8_t match) const
		{
			return Span().LastIndexOf(match);
		}

		///
		/// @brief 从 start 索引位置开始，从后往前查找匹配项。
		///
		/// @param start 要从后往前查找的起始索引位置。
		/// @param match 匹配项。
		///
		/// @return 找到了返回匹配位置的索引。没找到返回 -1.
		///
		int32_t LastIndexOf(int32_t start, uint8_t match) const
		{
			return Span().LastIndexOf(start, match);
		}

		///
		/// @brief 从后往前查找最后一个匹配位置的索引。
		///
		/// @param match 匹配项。
		///
		/// @return
		///
		int32_t LastIndexOf(base::String const &match) const
		{
			return Span().LastIndexOf(match.Span());
		}

		///
		/// @brief 从 start 索引位置开始，从后往前查找匹配项。
		///
		/// @param start 要从后往前查找的起始索引位置。
		/// @param match 匹配项。
		///
		/// @return 找到了返回匹配位置的索引。没找到返回 -1.
		///
		int32_t LastIndexOf(int32_t start, base::String const &match) const
		{
			return Span().LastIndexOf(start, match.Span());
		}

		/* #endregion */

		///
		/// @brief 翻转字符串。
		///
		///
		void Reverse()
		{
			std::reverse(_string.data(), _string.data() + _string.size());
		}

		///
		/// @brief 移除指定范围内的字符。
		///
		/// @param range
		///
		void Remove(base::Range const &range)
		{
			_string.erase(range.Begin(), range.Size());
		}

		///
		/// @brief 移除指定索引处的字符。
		///
		/// @param index
		///
		void RemoveAt(int32_t index)
		{
			_string.erase(index, 1);
		}

		///
		/// @brief 将字符串的指定范围替换为 replacement.
		///
		/// @param range 要被替换的范围。
		/// @param replacement 替换后的内容。
		///
		void Replace(base::Range const &range, base::String const &replacement)
		{
			_string.replace(range.Begin(), range.Size(), replacement.StdString());
		}

		///
		/// @brief 将本字符串中所有与 match 相同的部分替换成 replacement.
		///
		/// @param match 要被替换的内容。
		/// @param replacement 替换后的内容。
		///
		void Replace(base::String const &match, base::String const &replacement)
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

		///
		/// @brief 将字符转换为小写。
		///
		///
		void ToLower()
		{
			std::transform(_string.begin(),
						   _string.end(),
						   _string.begin(),
						   ::tolower);
		}

		///
		/// @brief 将字符转换为大写。
		///
		///
		void ToUpper()
		{
			std::transform(_string.begin(),
						   _string.end(),
						   _string.begin(),
						   ::toupper);
		}

		///
		/// @brief 检查本字符串中是否存在至少 1 个匹配项。
		///
		/// @param match 匹配项。
		///
		/// @return
		///
		bool Contains(char match) const
		{
			return IndexOf(match) >= 0;
		}

		///
		/// @brief 检查本字符串中是否存在至少 1 个匹配项。
		///
		/// @param match 匹配项。
		///
		/// @return
		///
		bool Contains(base::String const &match) const
		{
			return IndexOf(match) >= 0;
		}

		///
		/// @brief 检查字符串是否以 match 开头。
		///
		/// @param match
		///
		/// @return
		///
		bool StartWith(char match) const
		{
			return Span().StartWith(match);
		}

		///
		/// @brief 检查字符串是否以 match 开头。
		///
		/// @param match
		///
		/// @return
		///
		bool StartWith(base::String const &match) const
		{
			return Span().StartWith(match.Span());
		}

		///
		/// @brief 检查字符串是否以 match 开头。
		///
		/// @param match
		///
		/// @return
		///
		bool EndWith(char match) const
		{
			return Span().EndWith(match);
		}

		///
		/// @brief 检查字符串是否以 match 开头。
		///
		/// @param match
		///
		/// @return
		///
		bool EndWith(base::String const &match) const
		{
			return Span().EndWith(match.Span());
		}

		/* #region 填充 */

		///
		/// @brief 向字符串左边填充指定字符以达到目标长度。
		///
		/// @param pad 用来填充的字符。
		/// @param length 目标长度。
		///
		void PadLeft(char pad, base::StringLength const &length)
		{
			int32_t padding = length.Value() - Length();
			if (padding <= 0)
			{
				return;
			}

			std::string pad_str{};
			pad_str.reserve(padding);
			for (int32_t i = 0; i < padding; i++)
			{
				pad_str += pad;
			}

			_string = pad_str + _string;
		}

		///
		/// @brief 向字符串左边填充空白字符以达到目标长度。
		///
		/// @param pad 用来填充的字符。
		/// @param length 目标长度。
		///
		void PadLeft(base::StringLength const &length)
		{
			PadLeft(' ', length);
		}

		///
		/// @brief 向字符串右边填充指定字符以达到目标长度。
		///
		/// @param pad 用来填充的字符。
		/// @param length 目标长度。
		///
		void PadRight(char pad, base::StringLength const &length)
		{
			int32_t padding = length.Value() - Length();
			if (padding <= 0)
			{
				return;
			}

			_string.reserve(_string.size() + padding);
			for (int32_t i = 0; i < padding; i++)
			{
				_string += pad;
			}
		}

		///
		/// @brief 向字符串右边填充空白字符以达到目标长度。
		///
		/// @param pad 用来填充的字符。
		/// @param length 目标长度。
		///
		void PadRight(base::StringLength const &length)
		{
			PadRight(' ', length);
		}

		/* #endregion */

		/* #region 迭代器 */

		using Iterator = std::string::iterator;

		Iterator begin()
		{
			return _string.begin();
		}

		Iterator end()
		{
			return _string.end();
		}

		using ConstIterator = std::string::const_iterator;

		ConstIterator begin() const
		{
			return _string.begin();
		}

		ConstIterator end() const
		{
			return _string.end();
		}

		/* #endregion */
	};

} // namespace base

inline base::String operator+(char left, base::String const &right)
{
	return base::String{left + right.StdString()};
}

inline base::String operator+(char const *left, base::String const &right)
{
	return base::String{left + right.StdString()};
}

inline base::String operator+(std::string const &left, base::String const &right)
{
	return base::String{left + right.StdString()};
}

#if HAS_THREAD

inline std::ostream &operator<<(std::ostream &os, base::String const &str)
{
	os << str.StdString();
	return os;
}

#endif // HAS_THREAD
