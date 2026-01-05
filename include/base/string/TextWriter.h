#pragma once
#include "base/IDisposable.h"
#include "base/stream/ReadOnlySpan.h"
#include "base/string/ICanToString.h"
#include "base/string/String.h"

namespace base
{
	class TextWriter :
		public base::IDisposable
	{
	public:
		virtual void Write(base::ReadOnlySpan const &span) = 0;

		///
		/// @brief 处置对象。
		///
		/// @note 处置完后 Write 系列函数将不再可以调用，调用将抛出异常。
		///
		virtual void Dispose() override = 0;

		/* #region 写入 std::string */

		void Write(std::string const &str)
		{
			base::ReadOnlySpan span{
				reinterpret_cast<uint8_t const *>(str.data()),
				static_cast<int64_t>(str.size()),
			};

			Write(span);
		}

		void WriteLine(std::string const &str)
		{
			Write(str);
			WriteLine();
		}

		/* #endregion */

		/* #region 写入 base::String */

		void Write(base::String const &str)
		{
			Write(str.StdString());
		}

		void WriteLine(base::String const &str)
		{
			WriteLine(str.StdString());
		}

		/* #endregion */

		/* #region 写入 char */

		void Write(char c)
		{
			base::ReadOnlySpan span{
				reinterpret_cast<uint8_t const *>(&c),
				1,
			};

			Write(span);
		}

		void WriteLine(char c)
		{
			Write(c);
			WriteLine();
		}

		/* #endregion */

		/* #region char const * */

		///
		/// @brief
		///
		/// @param str C 风格的字符串。
		///
		void Write(char const *str)
		{
			int64_t end_index = 0;
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
		/// @brief
		///
		/// @param str C 风格的字符串。
		///
		void WriteLine(char const *str)
		{
			Write(str);
			WriteLine();
		}

		void Write(char const *str, int64_t length)
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

		void WriteLine(char const *str, int64_t length)
		{
			Write(str, length);
			WriteLine();
		}

		/* #endregion */

		/* #region 写入 base::ICanToString */

		void Write(base::ICanToString const &o)
		{
			Write(o.ToString());
		}

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

		void WriteLine()
		{
			Write('\n');
		}
	};

} // namespace base
