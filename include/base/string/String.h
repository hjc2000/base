#pragma once
#include <base/container/List.h>
#include <base/container/Range.h>
#include <base/define.h>
#include <base/stream/ReadOnlySpan.h>
#include <stdexcept>
#include <stdint.h>
#include <string>

namespace base
{
	/// @brief String 类的 Split 方法的选项。
	struct StringSplitOptions
	{
		/// @brief 切割完之后是否对每个子字符串进行 Trim. 即去除头尾的空白字符。
		/// @note 如果 Trim 之后变成空字符串，并且 remove_empty_substring
		/// 选项为 true，则该字符串将会被移除。
		/// @note 默认值：false.
		bool trim_each_substring = false;

		/// @brief 如果为 true，连续在一起的分隔符不会导致切割出一个空字符串。
		/// 例如逗号作分隔符时， "123,,456" 不会被切割成 3 个字符串，即不会被切割成
		/// 	@li "123"
		/// 	@li ""
		/// 	@li "456"
		/// 而是会被切割成
		/// 	@li "123"
		/// 	@li "456"
		/// 空字符串被丢弃。
		///
		/// @note 默认值：true.
		bool remove_empty_substring = true;
	};

	/// @brief 对 std::string 进行包装。
	class String
	{
	private:
		std::string _string;

#pragma region IsWhiteChar

		static_function constexpr bool IsWhiteChar(char value)
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

#pragma endregion

	public:
#pragma region 生命周期
		/// @brief 无参构造函数。
		String() = default;

		/// @brief 从 std::string 构造。
		/// @param o
		String(std::string const &o);

		/// @brief 从单个字符构造。
		/// @param o
		String(char o);

		String(char const *str);

		String(base::ReadOnlySpan const &o);

		/// @brief 拷贝构造函数。
		/// @param o
		String(String const &o);

		/// @brief 赋值运算符。
		/// @param o
		/// @return
		String &operator=(String const &o);
#pragma endregion

		std::string &StdString();
		std::string const &StdString() const;

		char &operator[](int32_t index);
		char const &operator[](int32_t index) const;

		/// @brief 获取指定范围内的子字符串。
		/// @note 子字符串是从父字符串拷贝而来而不是引用父字符串的内存。
		/// @param range
		/// @return
		base::String operator[](base::Range const &range) const;

		base::String &operator+=(base::String const &o);
		base::String operator+(base::String const &o) const;

		bool operator==(base::String const &o) const
		{
			return _string == o._string;
		}

		/// @brief 字符串长度。不包括结尾的空字符。
		/// @return
		int32_t Length() const;

#pragma region 迭代
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

#pragma endregion

		/// @brief 根据分隔符，将字符串拆分成多个子字符串，放到列表中返回。
		/// @param separator
		/// @return
		base::List<base::String> Split(char separator,
									   base::StringSplitOptions const &options = StringSplitOptions{}) const;

#pragma region Trim
		/// @brief 裁剪掉字符串开头处的空白字符。
		/// @note 关于哪些是空白字符，见 IsWhiteChar 函数。
		/// @return
		base::String TrimStart() const;

		/// @brief 裁剪掉字符串末尾处的空白字符。
		/// @note 关于哪些是空白字符，见 IsWhiteChar 函数。
		/// @return
		base::String TrimEnd() const;

		/// @brief 裁剪掉字符串开头和结尾的空白字符。
		/// @note 关于哪些是空白字符，见 IsWhiteChar 函数。
		/// @return
		base::String Trim() const;
#pragma endregion

		/// @brief 获取某个字符在字符串中的第一个索引。
		/// @param value 要被查找索引的字符。
		/// @return 如果字符串中存在该字符，则返回第 1 个索引。如果字符串中不存在该字符，
		/// 则返回 -1.
		int32_t IndexOf(char value) const;

		int32_t IndexOf(base::String const &value) const;

		/// @brief 检查字符串中是否存在至少 1 个指定的字符。
		/// @param value 指定的字符。
		/// @return 如果存在，则返回 true, 如果不存在则返回 false.
		bool Contains(char value) const;

		base::Span AsSpan();
		base::ReadOnlySpan AsReadOnlySpan() const;

		/// @brief 获取指定范围内的子字符串。
		/// @note 子字符串是从父字符串拷贝而来而不是引用父字符串的内存。
		/// @param range
		/// @return
		base::String Slice(base::Range const &range) const;

		/// @brief 翻转字符串。
		void Reverse();

		/// @brief 移除指定范围内的字符。
		/// @param range
		void Remove(base::Range const &range);
		void RemoveAt(int32_t index);
	};
} // namespace base

base::String operator+(std::string const &left, base::String const &right);
std::ostream &operator<<(std::ostream &os, base::String const &str);
