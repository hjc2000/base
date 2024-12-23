#pragma once
#include <base/container/List.h>
#include <iostream>
#include <stdexcept>
#include <stdint.h>
#include <string>

namespace base
{
	/// @brief 对 std::string 进行包装。
	class String
	{
	private:
		std::string _string;

		static constexpr bool IsWhiteChar(char value)
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

		base::String &operator+=(base::String const &o);
		base::String operator+(base::String const &o) const;

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
		base::List<std::string> Split(char separator) const;

		/// @brief 裁剪掉字符串开头处的空白字符。
		/// @note 关于哪些是空白字符，见 IsWhiteChar 函数。
		/// @return
		base::String TrimStart() const;

		base::String TrimEnd() const;
	};
} // namespace base

base::String operator+(std::string const &left, base::String const &right);
std::ostream &operator<<(std::ostream &os, base::String const &str);
