#pragma once
#include "base/stream/ReadOnlySpan.h"
#include "base/stream/Stream.h"
#include "base/string/ICanToString.h"
#include "base/string/String.h"
#include <cstdint>

namespace base
{
	///
	/// @brief 向流中写入字符串的工具。
	///
	///
	class StreamWriter
	{
	private:
		std::shared_ptr<base::Stream> _stream;

	public:
		StreamWriter(std::shared_ptr<base::Stream> const &stream);

		std::shared_ptr<base::Stream> Stream() const
		{
			return _stream;
		}

		/* #region 写入 std::string */

		///
		/// @brief 向流中写入字符串。
		///
		/// @param str
		///
		void Write(std::string const &str);

		///
		/// @brief 向流中写入字符串然后换行。
		///
		/// @param str
		///
		void WriteLine(std::string const &str);
		/* #endregion */

		/* #region 写入 base::String */

		///
		/// @brief 向流中写入字符串。
		///
		/// @param str
		///
		void Write(base::String const &str);

		///
		/// @brief 向流中写入字符串然后换行。
		///
		/// @param str
		///
		void WriteLine(base::String const &str);
		/* #endregion */

		/* #region 写入 char */

		///
		/// @brief 向流中写入字符。
		///
		/// @param c
		///
		void Write(char c);

		///
		/// @brief 向流中写入字符然后换行。
		///
		/// @param c
		///
		void WriteLine(char c);
		/* #endregion */

		/* #region char const * */

		///
		/// @brief 向流中写入字符串。
		///
		/// @param str C 风格的字符串。
		///
		void Write(char const *str);

		///
		/// @brief 向流中写入字符串。
		///
		/// @param str C 风格的字符串。
		///
		void WriteLine(char const *str);

		///
		/// @brief 向流中写入字符串。
		///
		/// @param str
		/// @param length
		///
		void Write(char const *str, int32_t length);

		///
		/// @brief 向流中写入字符串。
		///
		/// @param str
		/// @param length
		///
		void WriteLine(char const *str, int32_t length);

		/* #endregion */

		/* #region 写入 base::ICanToString */

		///
		/// @brief 将 base::ICanToString 转换为字符串后写入流。
		///
		/// @param o
		///
		void Write(base::ICanToString const &o);

		///
		/// @brief 将 base::ICanToString 转换为字符串后写入流，然后换行。
		///
		/// @param o
		///
		void WriteLine(base::ICanToString const &o);

		/* #endregion */

		/* #region 写入 base::ReadOnlySpan */

		///
		/// @brief 将 base::ReadOnlySpan 写入流。
		///
		/// @param span
		///
		void Write(base::ReadOnlySpan const &span);

		///
		/// @brief 将 base::ReadOnlySpan 写入流，然后换行。
		///
		/// @param span
		///
		void WriteLine(base::ReadOnlySpan const &span);
		/* #endregion */

		///
		/// @brief 向流中写入换行符。
		///
		///
		void WriteLine();
	};
} // namespace base
