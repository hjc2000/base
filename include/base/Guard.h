#pragma once
#include <functional>

namespace base
{
	///
	/// @brief 析构时会执行构造函数中传进来的回调。
	///
	class Guard final
	{
	private:
		std::function<void()> _func;

	public:
		Guard(std::function<void()> func);

		~Guard();
	};
} // namespace base
