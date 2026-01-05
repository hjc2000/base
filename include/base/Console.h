#pragma once
#include "base/task/Mutex.h"
#include "string/TextWriter.h"
#include <cstdint>
#include <memory>

namespace base
{
	///
	/// @brief 控制台。
	///
	class Console
	{
	private:
		base::task::Mutex _lock;
		std::shared_ptr<base::TextWriter> _output_writer;
		std::shared_ptr<base::TextWriter> _error_writer;

	public:
		~Console()
		{
			_output_writer.reset();
			_error_writer.reset();
		}

		/* #region OutputWriter */

		std::shared_ptr<base::TextWriter> OutputWriter() const
		{
			// 共享指针本身不线程安全，在另一个线程会写它的情况下，读写都需要加锁。
			base::task::MutexGuard g{_lock};
			return _output_writer;
		}

		void SetOutputWriter(std::shared_ptr<base::TextWriter> const &value)
		{
			// 共享指针本身不线程安全，在另一个线程会写它的情况下，读写都需要加锁。
			base::task::MutexGuard g{_lock};
			_output_writer = value;

			// 如果错误输出为空，则使用普通输出来输出错误
			if (_error_writer == nullptr)
			{
				_error_writer = value;
			}
		}

		std::shared_ptr<base::TextWriter> ErrorWriter() const
		{
			// 共享指针本身不线程安全，在另一个线程会写它的情况下，读写都需要加锁。
			base::task::MutexGuard g{_lock};
			return _error_writer;
		}

		void SetErrorWriter(std::shared_ptr<base::TextWriter> const &value)
		{
			// 共享指针本身不线程安全，在另一个线程会写它的情况下，读写都需要加锁。
			base::task::MutexGuard g{_lock};
			_error_writer = value;
		}

		/* #endregion */

		/* #region 写入 std::string */

		void Write(std::string const &str)
		{
			base::task::MutexGuard g{_lock};
			if (_output_writer == nullptr)
			{
				return;
			}

			_output_writer->Write(str);
		}

		void WriteLine(std::string const &str)
		{
			base::task::MutexGuard g{_lock};
			if (_output_writer == nullptr)
			{
				return;
			}

			_output_writer->WriteLine(str);
		}

		void WriteError(std::string const &str) noexcept
		{
			base::task::MutexGuard g{_lock};
			if (_error_writer == nullptr)
			{
				return;
			}

			try
			{
				_error_writer->Write(str);
			}
			catch (...)
			{
			}
		}

		void WriteErrorLine(std::string const &str) noexcept
		{
			base::task::MutexGuard g{_lock};
			if (_error_writer == nullptr)
			{
				return;
			}

			try
			{
				_error_writer->WriteLine(str);
			}
			catch (...)
			{
			}
		}

		/* #endregion */

		/* #region 写入 base::String */

		void Write(base::String const &str)
		{
			base::task::MutexGuard g{_lock};
			if (_output_writer == nullptr)
			{
				return;
			}

			_output_writer->Write(str);
		}

		void WriteLine(base::String const &str)
		{
			base::task::MutexGuard g{_lock};
			if (_output_writer == nullptr)
			{
				return;
			}

			_output_writer->WriteLine(str);
		}

		void WriteError(base::String const &str) noexcept
		{
			base::task::MutexGuard g{_lock};
			if (_error_writer == nullptr)
			{
				return;
			}

			try
			{
				_error_writer->Write(str);
			}
			catch (...)
			{
			}
		}

		void WriteErrorLine(base::String const &str) noexcept
		{
			base::task::MutexGuard g{_lock};
			if (_error_writer == nullptr)
			{
				return;
			}

			try
			{
				_error_writer->WriteLine(str);
			}
			catch (...)
			{
			}
		}

		/* #endregion */

		/* #region 写入 char */

		void Write(char c)
		{
			base::task::MutexGuard g{_lock};
			if (_output_writer == nullptr)
			{
				return;
			}

			_output_writer->Write(c);
		}

		void WriteLine(char c)
		{
			base::task::MutexGuard g{_lock};
			if (_output_writer == nullptr)
			{
				return;
			}

			_output_writer->WriteLine(c);
		}

		void WriteError(char c) noexcept
		{
			base::task::MutexGuard g{_lock};
			if (_error_writer == nullptr)
			{
				return;
			}

			try
			{
				_error_writer->Write(c);
			}
			catch (...)
			{
			}
		}

		void WriteErrorLine(char c) noexcept
		{
			base::task::MutexGuard g{_lock};
			if (_error_writer == nullptr)
			{
				return;
			}

			try
			{
				_error_writer->WriteLine(c);
			}
			catch (...)
			{
			}
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
			base::task::MutexGuard g{_lock};
			if (_output_writer == nullptr)
			{
				return;
			}

			_output_writer->Write(str);
		}

		///
		/// @brief
		///
		/// @param str C 风格的字符串。
		///
		void WriteLine(char const *str)
		{
			base::task::MutexGuard g{_lock};
			if (_output_writer == nullptr)
			{
				return;
			}

			_output_writer->WriteLine(str);
		}

		void WriteError(char const *str) noexcept
		{
			base::task::MutexGuard g{_lock};
			if (_error_writer == nullptr)
			{
				return;
			}

			try
			{
				_error_writer->Write(str);
			}
			catch (...)
			{
			}
		}

		void WriteErrorLine(char const *str) noexcept
		{
			base::task::MutexGuard g{_lock};
			if (_error_writer == nullptr)
			{
				return;
			}

			try
			{
				_error_writer->WriteLine(str);
			}
			catch (...)
			{
			}
		}

		void Write(char const *str, int64_t length)
		{
			base::task::MutexGuard g{_lock};
			if (_output_writer == nullptr)
			{
				return;
			}

			_output_writer->Write(str, length);
		}

		void WriteLine(char const *str, int64_t length)
		{
			base::task::MutexGuard g{_lock};
			if (_output_writer == nullptr)
			{
				return;
			}

			_output_writer->WriteLine(str, length);
		}

		void WriteError(char const *str, int64_t length) noexcept
		{
			base::task::MutexGuard g{_lock};
			if (_error_writer == nullptr)
			{
				return;
			}

			try
			{
				_error_writer->Write(str, length);
			}
			catch (...)
			{
			}
		}

		void WriteErrorLine(char const *str, int64_t length) noexcept
		{
			base::task::MutexGuard g{_lock};
			if (_error_writer == nullptr)
			{
				return;
			}

			try
			{
				_error_writer->WriteLine(str, length);
			}
			catch (...)
			{
			}
		}

		/* #endregion */

		/* #region 写入 base::ICanToString */

		void Write(base::ICanToString const &o)
		{
			base::task::MutexGuard g{_lock};
			if (_output_writer == nullptr)
			{
				return;
			}

			_output_writer->Write(o);
		}

		void WriteLine(base::ICanToString const &o)
		{
			base::task::MutexGuard g{_lock};
			if (_output_writer == nullptr)
			{
				return;
			}

			_output_writer->WriteLine(o);
		}

		void WriteError(base::ICanToString const &o) noexcept
		{
			base::task::MutexGuard g{_lock};
			if (_error_writer == nullptr)
			{
				return;
			}

			try
			{
				_error_writer->Write(o);
			}
			catch (...)
			{
			}
		}

		void WriteErrorLine(base::ICanToString const &o) noexcept
		{
			base::task::MutexGuard g{_lock};
			if (_error_writer == nullptr)
			{
				return;
			}

			try
			{
				_error_writer->WriteLine(o);
			}
			catch (...)
			{
			}
		}

		/* #endregion */

		/* #region 写入 base::ReadOnlySpan */

		void Write(base::ReadOnlySpan const &span)
		{
			base::task::MutexGuard g{_lock};
			if (_output_writer == nullptr)
			{
				return;
			}

			_output_writer->Write(span);
		}

		void WriteLine(base::ReadOnlySpan const &span)
		{
			base::task::MutexGuard g{_lock};
			if (_output_writer == nullptr)
			{
				return;
			}

			_output_writer->WriteLine(span);
		}

		void WriteError(base::ReadOnlySpan const &span) noexcept
		{
			base::task::MutexGuard g{_lock};
			if (_error_writer == nullptr)
			{
				return;
			}

			try
			{
				_error_writer->Write(span);
			}
			catch (...)
			{
			}
		}

		void WriteErrorLine(base::ReadOnlySpan const &span) noexcept
		{
			base::task::MutexGuard g{_lock};
			if (_error_writer == nullptr)
			{
				return;
			}

			try
			{
				_error_writer->WriteLine(span);
			}
			catch (...)
			{
			}
		}

		/* #endregion */

		/* #region 写入空行 */

		void WriteLine()
		{
			base::task::MutexGuard g{_lock};
			if (_output_writer == nullptr)
			{
				return;
			}

			_output_writer->WriteLine();
		}

		void WriteErrorLine() noexcept
		{
			base::task::MutexGuard g{_lock};
			if (_error_writer == nullptr)
			{
				return;
			}

			try
			{
				_error_writer->WriteLine();
			}
			catch (...)
			{
			}
		}

		/* #endregion */
	};

	base::Console &console();

} // namespace base
