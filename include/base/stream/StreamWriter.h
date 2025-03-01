#pragma once
#include <base/stream/Stream.h>
#include <base/string/String.h>
#include <memory>

namespace base
{
	class StreamWriter
	{
	private:
		std::shared_ptr<base::Stream> _stream;

	public:
		StreamWriter(std::shared_ptr<base::Stream> const &stream);

	public:
		/**
		 * @brief 向流中写入字符串。
		 *
		 * @param str
		 */
		void Write(std::string const &str);

		/**
		 * @brief 向流中写入字符串。
		 *
		 * @param str
		 */
		void Write(base::String const &str);

		/**
		 * @brief 向流中写入字符。
		 *
		 * @param c
		 */
		void Write(char c);

		/**
		 * @brief 向流中写入字符串。
		 *
		 * @param str C 风格的字符串。
		 */
		void Write(char const *str);

	public:
		/**
		 * @brief 向流中写入字符串然后换行。
		 *
		 * @param str
		 */
		void WriteLine(std::string const &str);

		/**
		 * @brief 向流中写入字符串然后换行。
		 *
		 * @param str
		 */
		void WriteLine(base::String const &str);

		/**
		 * @brief 向流中写入字符然后换行。
		 *
		 * @param c
		 */
		void WriteLine(char c);

		/**
		 * @brief 向流中写入字符串。
		 *
		 * @param str C 风格的字符串。
		 */
		void WriteLine(char const *str);

		/**
		 * @brief 向流中写入换行符。
		 *
		 */
		void WriteLine();
	};
} // namespace base
