#pragma once
#include <string>

namespace base
{
	class String
	{
	private:
		std::string _string;

	public:
		/// @brief 无参构造函数。
		String() = default;

		/// @brief 从 std::string 构造。
		/// @param o
		String(std::string const &o);

		/// @brief 拷贝构造函数。
		/// @param o
		String(String const &o);

		/// @brief 赋值运算符。
		/// @param o
		/// @return
		String &operator=(String const &o);

		std::string &StdString();
		std::string const &StdString() const;

		explicit operator std::string() const
		{
			return _string;
		}
	};
} // namespace base
