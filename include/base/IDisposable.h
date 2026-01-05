#pragma once
#include <stdexcept>
#include <string>

namespace base
{
	///
	/// @brief 可释放对象的接口。
	///
	class IDisposable
	{
	public:
		virtual ~IDisposable() = default;

		///
		/// @brief 处置对象，让对象准备好结束生命周期。类似于进入 “准备后事” 的状态。
		///
		/// @note 注意，对象并不是析构了，并不是完全无法访问，它仍然允许访问，仍然能执行一些
		/// 符合 “准备后事” 的工作。
		///
		virtual void Dispose() = 0;
	};

	///
	/// @brief 对象被释放之后再次使用就会抛出此异常。
	///
	class ObjectDisposedException :
		public std::runtime_error
	{
	public:
		ObjectDisposedException()
			: std::runtime_error(__func__)
		{
		}

		ObjectDisposedException(std::string const &message)
			: std::runtime_error(std::string{__func__} + ": " + message)
		{
		}
	};

} // namespace base
