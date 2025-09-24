#pragma once
#include <cctype>
#include <cstdint>
#include <stdexcept>

namespace base
{
	namespace character
	{
		///
		/// @brief 判断一个字符是否是空白字符。
		///
		/// @param value
		///
		/// @return
		///
		constexpr bool is_white_char(char value)
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
		///
		/// @return
		///
		constexpr bool is_alpha(char value)
		{
			return std::isalpha(value);
		}

		///
		/// @brief 将字母转换为大写。
		///
		/// @param value
		/// @return
		///
		constexpr char to_upper(char value)
		{
			return std::toupper(value);
		}

		///
		/// @brief 将字母转换为小写。
		///
		/// @param value
		/// @return
		///
		constexpr char to_lower(char value)
		{
			return std::tolower(value);
		}

		///
		/// @brief 将数值转换为单个的 16 进制数字符。
		///
		/// @param value
		/// @return
		///
		constexpr char number_to_hex_char(uint8_t value)
		{
			if (value > 15)
			{
				throw std::out_of_range{"数值超出范围"};
			}

			if (value < 10)
			{
				return '0' + value;
			}

			return 'a' + value - 10;
		}

	} // namespace character
} // namespace base
