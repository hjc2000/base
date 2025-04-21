#pragma once

#include "base/stream/Stream.h"
#include "base/task/Mutex.h"
#include "stream/StreamWriter.h"
#include <cstdint>
#include <memory>

namespace base
{
	///
	/// @brief 控制台。
	///
	///
	class Console
	{
	private:
		base::task::Mutex _lock;
		std::shared_ptr<base::Stream> _output_stream;
		std::shared_ptr<base::StreamWriter> _writer;

	public:
		/* #region OutputStream */

		std::shared_ptr<base::Stream> OutputStream() const
		{
			// 共享指针本身不线程安全，在另一个线程会写它的情况下，读写都需要加锁。
			base::task::MutexGuard g{_lock};
			return _output_stream;
		}

		void SetOutputStream(std::shared_ptr<base::Stream> const &value)
		{
			// 共享指针本身不线程安全，在另一个线程会写它的情况下，读写都需要加锁。
			base::task::MutexGuard g{_lock};
			_output_stream = value;
			if (_output_stream == nullptr)
			{
				_writer = nullptr;
			}
			else
			{
				_writer = std::shared_ptr<base::StreamWriter>{new base::StreamWriter{_output_stream}};
			}
		}

		/* #endregion */

		/* #region 写入 std::string */

		///
		/// @brief 向流中写入字符串。
		///
		/// @param str
		///
		void Write(std::string const &str)
		{
			base::task::MutexGuard g{_lock};
			if (_writer == nullptr)
			{
				return;
			}

			_writer->Write(str);
		}

		///
		/// @brief 向流中写入字符串然后换行。
		///
		/// @param str
		///
		void WriteLine(std::string const &str)
		{
			base::task::MutexGuard g{_lock};
			if (_writer == nullptr)
			{
				return;
			}

			_writer->WriteLine(str);
		}

		void WriteErrorLine(std::string const &str) noexcept
		{
			base::task::MutexGuard g{_lock};
			if (_writer == nullptr)
			{
				return;
			}

			try
			{
				_writer->WriteLine(str);
			}
			catch (...)
			{
			}
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
			base::task::MutexGuard g{_lock};
			if (_writer == nullptr)
			{
				return;
			}

			_writer->Write(str);
		}

		///
		/// @brief 向流中写入字符串然后换行。
		///
		/// @param str
		///
		void WriteLine(base::String const &str)
		{
			base::task::MutexGuard g{_lock};
			if (_writer == nullptr)
			{
				return;
			}

			_writer->WriteLine(str);
		}

		void WriteErrorLine(base::String const &str) noexcept
		{
			base::task::MutexGuard g{_lock};
			if (_writer == nullptr)
			{
				return;
			}

			try
			{
				_writer->WriteLine(str);
			}
			catch (...)
			{
			}
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
			base::task::MutexGuard g{_lock};
			if (_writer == nullptr)
			{
				return;
			}

			_writer->Write(c);
		}

		///
		/// @brief 向流中写入字符然后换行。
		///
		/// @param c
		///
		void WriteLine(char c)
		{
			base::task::MutexGuard g{_lock};
			if (_writer == nullptr)
			{
				return;
			}

			_writer->WriteLine(c);
		}

		void WriteErrorLine(char c) noexcept
		{
			base::task::MutexGuard g{_lock};
			if (_writer == nullptr)
			{
				return;
			}

			try
			{
				_writer->WriteLine(c);
			}
			catch (...)
			{
			}
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
			base::task::MutexGuard g{_lock};
			if (_writer == nullptr)
			{
				return;
			}

			_writer->Write(str);
		}

		///
		/// @brief 向流中写入字符串。
		///
		/// @param str C 风格的字符串。
		///
		void WriteLine(char const *str)
		{
			base::task::MutexGuard g{_lock};
			if (_writer == nullptr)
			{
				return;
			}

			_writer->WriteLine(str);
		}

		void WriteErrorLine(char const *str) noexcept
		{
			base::task::MutexGuard g{_lock};
			if (_writer == nullptr)
			{
				return;
			}

			try
			{
				_writer->WriteLine(str);
			}
			catch (...)
			{
			}
		}

		///
		/// @brief 向流中写入字符串。
		///
		/// @param str
		/// @param length
		///
		void Write(char const *str, int32_t length)
		{
			base::task::MutexGuard g{_lock};
			if (_writer == nullptr)
			{
				return;
			}

			_writer->Write(str, length);
		}

		///
		/// @brief 向流中写入字符串。
		///
		/// @param str
		/// @param length
		///
		void WriteLine(char const *str, int32_t length)
		{
			base::task::MutexGuard g{_lock};
			if (_writer == nullptr)
			{
				return;
			}

			_writer->WriteLine(str, length);
		}

		void WriteErrorLine(char const *str, int32_t length) noexcept
		{
			base::task::MutexGuard g{_lock};
			if (_writer == nullptr)
			{
				return;
			}

			try
			{
				_writer->WriteLine(str, length);
			}
			catch (...)
			{
			}
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
			base::task::MutexGuard g{_lock};
			if (_writer == nullptr)
			{
				return;
			}

			_writer->Write(o);
		}

		///
		/// @brief 将 base::ICanToString 转换为字符串后写入流，然后换行。
		///
		/// @param o
		///
		void WriteLine(base::ICanToString const &o)
		{
			base::task::MutexGuard g{_lock};
			if (_writer == nullptr)
			{
				return;
			}

			_writer->WriteLine(o);
		}

		void WriteErrorLine(base::ICanToString const &o) noexcept
		{
			base::task::MutexGuard g{_lock};
			if (_writer == nullptr)
			{
				return;
			}

			try
			{
				_writer->WriteLine(o);
			}
			catch (...)
			{
			}
		}

		/* #endregion */

		/* #region 写入 base::ReadOnlySpan */

		///
		/// @brief 将 base::ReadOnlySpan 写入流。
		///
		/// @param span
		///
		void Write(base::ReadOnlySpan const &span)
		{
			base::task::MutexGuard g{_lock};
			if (_writer == nullptr)
			{
				return;
			}

			_writer->Write(span);
		}

		///
		/// @brief 将 base::ReadOnlySpan 写入流，然后换行。
		///
		/// @param span
		///
		void WriteLine(base::ReadOnlySpan const &span)
		{
			base::task::MutexGuard g{_lock};
			if (_writer == nullptr)
			{
				return;
			}

			_writer->WriteLine(span);
		}

		void WriteErrorLine(base::ReadOnlySpan const &span) noexcept
		{
			base::task::MutexGuard g{_lock};
			if (_writer == nullptr)
			{
				return;
			}

			try
			{
				_writer->WriteLine(span);
			}
			catch (...)
			{
			}
		}

		/* #endregion */

		///
		/// @brief 向流中写入换行符。
		///
		///
		void WriteLine()
		{
			base::task::MutexGuard g{_lock};
			if (_writer == nullptr)
			{
				return;
			}

			_writer->WriteLine();
		}

		void WriteErrorLine() noexcept
		{
			base::task::MutexGuard g{_lock};
			if (_writer == nullptr)
			{
				return;
			}

			try
			{
				_writer->WriteLine();
			}
			catch (...)
			{
			}
		}
	};

	extern base::Console console;

} // namespace base
