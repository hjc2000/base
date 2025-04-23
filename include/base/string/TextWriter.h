#pragma once
#include "base/stream/ReadOnlySpan.h"
#include "base/string/ICanToString.h"
#include "base/string/String.h"

namespace base
{
	class TextWriter
	{
	public:
		virtual void Write(base::ReadOnlySpan const &span) = 0;

		/* #region 写入 std::string */

		///
		/// @brief 向流中写入字符串。
		///
		/// @param str
		///
		void Write(std::string const &str)
		{
			base::ReadOnlySpan span{
				reinterpret_cast<uint8_t const *>(str.data()),
				static_cast<int32_t>(str.size()),
			};

			Write(span);
		}

		///
		/// @brief 向流中写入字符串然后换行。
		///
		/// @param str
		///
		void WriteLine(std::string const &str)
		{
			Write(str);
			WriteLine();
		}

		/* #endregion */

		/* #region 写入 base::String */

		///
		/// @brief 向流中写入字符串。
		///
		/// @param str
		///
		void Write(base::String const &str)
		{
			Write(str.StdString());
		}

		///
		/// @brief 向流中写入字符串然后换行。
		///
		/// @param str
		///
		void WriteLine(base::String const &str)
		{
			WriteLine(str.StdString());
		}

		/* #endregion */

		/* #region 写入 char */

		///
		/// @brief 向流中写入字符。
		///
		/// @param c
		///
		void Write(char c)
		{
			base::ReadOnlySpan span{
				reinterpret_cast<uint8_t const *>(&c),
				1,
			};

			Write(span);
		}

		///
		/// @brief 向流中写入字符然后换行。
		///
		/// @param c
		///
		void WriteLine(char c)
		{
			Write(c);
			WriteLine();
		}

		/* #endregion */

		/* #region char const * */

		///
		/// @brief 向流中写入字符串。
		///
		/// @param str C 风格的字符串。
		///
		void Write(char const *str)
		{
			int32_t end_index = 0;
			while (true)
			{
				if (str[end_index] == '\0')
				{
					break;
				}

				if (end_index == INT32_MAX)
				{
					break;
				}

				end_index++;
			}

			if (end_index <= 0)
			{
				return;
			}

			base::ReadOnlySpan span{
				reinterpret_cast<uint8_t const *>(str),
				end_index,
			};

			Write(span);
		}

		///
		/// @brief 向流中写入字符串。
		///
		/// @param str C 风格的字符串。
		///
		void WriteLine(char const *str)
		{
			Write(str);
			WriteLine();
		}

		///
		/// @brief 向流中写入字符串。
		///
		/// @param str
		/// @param length
		///
		void Write(char const *str, int32_t length)
		{
			if (length <= 0)
			{
				return;
			}

			base::ReadOnlySpan span{
				reinterpret_cast<uint8_t const *>(str),
				length,
			};

			Write(span);
		}

		///
		/// @brief 向流中写入字符串。
		///
		/// @param str
		/// @param length
		///
		void WriteLine(char const *str, int32_t length)
		{
			Write(str, length);
			WriteLine();
		}

		/* #endregion */

		/* #region 写入 base::ICanToString */

		///
		/// @brief 将 base::ICanToString 转换为字符串后写入流。
		///
		/// @param o
		///
		void Write(base::ICanToString const &o)
		{
			Write(o.ToString());
		}

		///
		/// @brief 将 base::ICanToString 转换为字符串后写入流，然后换行。
		///
		/// @param o
		///
		void WriteLine(base::ICanToString const &o)
		{
			WriteLine(o.ToString());
		}

		/* #endregion */

		/* #region 写入 base::ReadOnlySpan */

		void WriteLine(base::ReadOnlySpan const &span)
		{
			Write(span);
			WriteLine();
		}

		/* #endregion */

		///
		/// @brief 向流中写入换行符。
		///
		///
		void WriteLine()
		{
			Write('\n');
		}
	};
} // namespace base
