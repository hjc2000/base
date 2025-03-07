#pragma once
#include <base/container/List.h>
#include <base/container/Range.h>
#include <base/define.h>
#include <base/stream/ReadOnlySpan.h>
#include <base/string/StringSplitOptions.h>
#include <cctype>
#include <stdint.h>
#include <string>

namespace base
{
	/**
	 * @brief 对 std::string 进行包装。
	 *
	 */
	class String
	{
	private:
		std::string _string{};
		static_function bool IsWhiteChar(char value);

	public:
		// 构造函数

		String() = default;
		String(std::string const &o);
		String(char o);
		String(char const *str);
		String(base::ReadOnlySpan const &o);
		String(base::Span const &o);

	public:
		/**
		 * @brief 获取被本类包装的 std::string 对象的引用。
		 *
		 * @return std::string&
		 */
		std::string &StdString();

		/**
		 * @brief 获取被本类包装的 std::string 对象的引用。
		 *
		 * @return std::string const&
		 */
		std::string const &StdString() const;

	public:
		// 索引器

		/**
		 * @brief 获取指定索引位置的字符的引用。
		 *
		 * @param index
		 * @return char&
		 */
		char &operator[](int32_t index);

		/**
		 * @brief 获取指定索引位置的字符的引用。
		 *
		 * @param index
		 * @return char const&
		 */
		char const &operator[](int32_t index) const;

		/**
		 * @brief 获取指定范围内的子字符串。
		 *
		 * @note 子字符串是从父字符串拷贝而来而不是引用父字符串的内存。
		 *
		 * @param range
		 * @return base::String
		 */
		base::String operator[](base::Range const &range) const;

	public:
		base::String &operator+=(base::String const &o);
		base::String operator+(base::String const &o) const;

	public:
		bool operator==(base::String const &o) const;
		bool operator<(base::String const &o) const;
		bool operator>(base::String const &o) const;
		bool operator<=(base::String const &o) const;
		bool operator>=(base::String const &o) const;

	public:
		/**
		 * @brief 字符串长度。不包括结尾的空字符。
		 *
		 * @return int32_t
		 */
		int32_t Length() const;

		/**
		 * @brief 根据分隔符，将字符串拆分成多个子字符串，放到列表中返回。
		 *
		 * @param separator
		 * @param options
		 * @return base::List<base::String>
		 */
		base::List<base::String> Split(char separator,
									   base::StringSplitOptions const &options = StringSplitOptions{}) const;

	public:
		// Trim

		/**
		 * @brief 裁剪掉字符串开头处的空白字符。
		 *
		 * @note 关于哪些是空白字符，见 IsWhiteChar 函数。
		 */
		void TrimStart();

		/**
		 * @brief 裁剪掉字符串末尾处的空白字符。
		 *
		 * @note 关于哪些是空白字符，见 IsWhiteChar 函数。
		 */
		void TrimEnd();

		/**
		 * @brief 裁剪掉字符串开头和结尾的空白字符。
		 *
		 * @note 关于哪些是空白字符，见 IsWhiteChar 函数。
		 */
		void Trim();

	public:
		// 查找索引位置

		/**
		 * @brief 从本字符串查找匹配项所在的索引。
		 *
		 * @param match 匹配项。
		 * @return int32_t 找到了返回匹配位置的索引。没找到返回 -1.
		 */
		int32_t IndexOf(char match) const;

		/**
		 * @brief 从本字符串查找匹配项所在的索引。
		 *
		 * @param start 查找的起始索引。从此处往后开始查找。
		 * @param match 匹配项。
		 * @return int32_t 找到了返回匹配位置的索引。没找到返回 -1.
		 */
		int32_t IndexOf(int32_t start, char match) const;

		/**
		 * @brief 从本字符串查找匹配项所在的索引。
		 *
		 * @param match 匹配项。
		 * @return int32_t 找到了返回匹配位置的索引。没找到返回 -1.
		 */
		int32_t IndexOf(base::String const &match) const;

		/**
		 * @brief 从本字符串查找匹配项所在的索引。
		 *
		 * @param start 查找的起始索引。从此处往后开始查找。
		 * @param match 匹配项。
		 * @return int32_t 找到了返回匹配位置的索引。没找到返回 -1.
		 */
		int32_t IndexOf(int32_t start, base::String const &match) const;

		/**
		 * @brief 从后往前查找最后一个匹配项所在的索引。
		 *
		 * @param match 匹配项。
		 * @return int32_t 找到了返回匹配位置的索引。没找到返回 -1.
		 */
		int32_t LastIndexOf(uint8_t match) const;

		/**
		 * @brief 从 start 索引位置开始，从后往前查找匹配项。
		 *
		 * @param start 要从后往前查找的起始索引位置。
		 * @param match
		 * @return int32_t 找到了返回匹配位置的索引。没找到返回 -1.
		 */
		int32_t LastIndexOf(int32_t start, uint8_t match) const;

		/**
		 * @brief 从后往前查找最后一个匹配位置的索引。
		 *
		 * @param match 匹配项。
		 * @return int32_t
		 */
		int32_t LastIndexOf(base::String const &match) const;

		/**
		 * @brief 从 start 索引位置开始，从后往前查找匹配项。
		 *
		 * @param start 要从后往前查找的起始索引位置。
		 * @param match 匹配项。
		 * @return int32_t 找到了返回匹配位置的索引。没找到返回 -1.
		 */
		int32_t LastIndexOf(int32_t start, base::String const &match) const;

	public:
		/**
		 * @brief 检查本字符串中是否存在至少 1 个匹配项。
		 *
		 * @param match 匹配项。
		 * @return true 如果存在，则返回 true.
		 * @return false 如果不存在则返回 false.
		 */
		bool Contains(char match) const;

		/**
		 * @brief 检查本字符串中是否存在至少 1 个匹配项。
		 *
		 * @param match 匹配项。
		 * @return true 如果有则返回 true.
		 * @return false 没有则返回 false.
		 */
		bool Contains(base::String const &match) const;

		/**
		 * @brief 获取本字符串的内存段。内存段中不包括结尾的空字符。
		 *
		 * @return base::Span
		 */
		base::Span Span();

		/**
		 * @brief 获取本字符串的内存段。内存段中不包括结尾的空字符。
		 *
		 * @return base::ReadOnlySpan
		 */
		base::ReadOnlySpan Span() const;

		/**
		 * @brief 获取指定范围内的子字符串。
		 *
		 * @note 子字符串是从父字符串拷贝而来而不是引用父字符串的内存。
		 *
		 * @param range
		 * @return base::String
		 */
		base::String Slice(base::Range const &range) const;

		/**
		 * @brief 翻转字符串。
		 *
		 */
		void Reverse();

		/**
		 * @brief 移除指定范围内的字符。
		 *
		 * @param range
		 */
		void Remove(base::Range const &range);

		/**
		 * @brief 移除指定索引处的字符。
		 *
		 * @param index
		 */
		void RemoveAt(int32_t index);

		/**
		 * @brief 将字符串的指定范围替换为 replacement.
		 *
		 * @param range 要被替换的范围。
		 * @param replacement 替换后的内容。
		 */
		void Replace(base::Range const &range, base::String const &replacement);

		/**
		 * @brief 将本字符串中所有与 match 相同的部分替换成 replacement.
		 *
		 * @param match 要被替换的内容。
		 * @param replacement 替换后的内容。
		 */
		void Replace(base::String const &match, base::String const &replacement);

		/**
		 * @brief 将字符转换为小写。
		 *
		 */
		void ToLower();

		/**
		 * @brief 将字符转换为大写。
		 *
		 */
		void ToUpper();

	public:
		bool StartWith(char match) const;
		bool StartWith(base::String const &match) const;

		bool EndWith(char match) const;
		bool EndWith(base::String const &match) const;

	public:
		// 迭代器

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
	};
} // namespace base

base::String operator+(char left, base::String const &right);
base::String operator+(std::string const &left, base::String const &right);
std::ostream &operator<<(std::ostream &os, base::String const &str);
