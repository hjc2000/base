#pragma once
#include <stdexcept>

namespace base
{
	///
	/// @brief 可释放对象的接口。
	///
	///
	class IDisposable
	{
	public:
		///
		/// @brief 主动释放对象，让对象不再能够工作。
		///
		///
		virtual void Dispose() = 0;
	};

	///
	/// @brief 对象被释放之后再次使用就会抛出此异常。
	///
	///
	class ObjectDisposedException :
		public std::runtime_error
	{
	public:
		ObjectDisposedException()
			: ObjectDisposedException("ObjectDisposedException")
		{
		}

		ObjectDisposedException(std::string const &message)
			: std::runtime_error(message)
		{
		}
	};
} // namespace base
