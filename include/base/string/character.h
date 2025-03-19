#pragma once

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

	} // namespace character
} // namespace base
