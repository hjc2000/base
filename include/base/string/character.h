#pragma once

#include <cctype>

namespace base
{
	namespace character
	{
		///
		/// @brief 判断一个字符是否是空白字符。
		///
		/// @param value
		/// @return bool
		///
		constexpr bool IsWhiteChar(char value)
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

		///
		/// @brief 检查一个字符是不是英文字母。
		///
		/// @param value
		/// @return true
		/// @return false
		///
		constexpr bool IsAlpha(char value)
		{
			return std::isalpha(value);
		}

		///
		/// @brief 将字母转换为大写。
		///
		/// @param value
		/// @return constexpr char
		///
		constexpr char ToUpper(char value)
		{
			return std::toupper(value);
		}
	} // namespace character
} // namespace base
