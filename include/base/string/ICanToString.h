#pragma once
#include <iostream>
#include <string>

namespace base
{
	/// @brief 继承此接口表示能够转化为字符串。
	class ICanToString
	{
	public:
		/// @brief 转化为字符串
		/// @return
		virtual std::string ToString() const = 0;

		/// @brief 重载强制转换为字符串的运算符。
		explicit operator std::string() const
		{
			return ToString();
		}
	};
} // namespace base

std::ostream &operator<<(std::ostream &stream, base::ICanToString const &o);

namespace std
{
	std::string to_string(base::ICanToString const &o);
}
