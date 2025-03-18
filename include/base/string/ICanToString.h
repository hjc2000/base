#pragma once
#include <string>

namespace base
{
	///
	/// @brief 继承此接口表示能够转化为字符串。
	///
	///
	class ICanToString
	{
	public:
		///
		/// @brief 转化为字符串。
		///
		/// @return std::string
		///
		virtual std::string ToString() const = 0;

		///
		/// @brief 重载强制转换为字符串的运算符。
		///
		/// @return std::string
		///
		explicit operator std::string() const
		{
			return ToString();
		}
	};
} // namespace base

namespace std
{
	///
	/// @brief 将 base::ICanToString 对象转为字符串。
	///
	/// @param o
	/// @return std::string
	///
	std::string to_string(base::ICanToString const &o);

} // namespace std

#if HAS_THREAD

///
/// @brief 将 base::ICanToString 对象转为字符串后输出到输出流。
///
/// @param stream
/// @param o
/// @return std::ostream&
///
std::ostream &operator<<(std::ostream &stream, base::ICanToString const &o);

#endif
