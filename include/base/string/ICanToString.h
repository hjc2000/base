#pragma once
#include <string>

#if HAS_THREAD
#include <iostream>
#endif

namespace base
{
	/// @brief 继承此接口表示能够转化为字符串。
	class ICanToString
	{
	public:
		/// @brief 转化为字符串
		/// @return
		virtual std::string ToString() const = 0;
	};
} // namespace base

#if HAS_THREAD
std::ostream &operator<<(std::ostream &stream, base::ICanToString const &o);
#endif

namespace std
{
	std::string to_string(base::ICanToString const &o);
}
