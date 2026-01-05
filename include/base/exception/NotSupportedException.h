#pragma once
#include <exception>

namespace base
{
	///
	/// @brief 一个功能不被支持时就抛出此异常。
	///
	class NotSupportedException :
		public std::exception
	{
	public:
		virtual char const *what() const noexcept override
		{
			return "不支持的功能。";
		}
	};

} // namespace base
