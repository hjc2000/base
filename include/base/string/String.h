#pragma once
#include <stdexcept>
#include <stdint.h>
#include <string>

namespace base
{
	class String
	{
	private:
		std::string _string;

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

		char &operator[](size_t index);
		char const &operator[](size_t index) const;

		base::String &operator+=(base::String const &o);
		base::String operator+(base::String const &o) const;

		/// @brief 字符串长度。不包括结尾的空字符。
		/// @return
		size_t Length() const;

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
	};
} // namespace base

base::String operator+(std::string const &left, base::String const &right);
