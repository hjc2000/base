#pragma once
#include <exception>

namespace base
{
	namespace exception
	{
		///
		/// @brief 一个功能不被支持时就抛出此异常。
		///
		///
		class NotSupportedException :
			public std::exception
		{
		public:
			using std::exception::exception;

			virtual char const *what() const noexcept override
			{
				return "不支持的功能。";
			}
		};

	} // namespace exception
} // namespace base
