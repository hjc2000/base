#pragma once
#include <string>

namespace base
{
	///
	/// @brief 继承此接口表示能够转化为字符串。
	///
	class ICanToString
	{
	public:
		virtual ~ICanToString() = default;

		///
		/// @brief 转化为字符串。
		///
		/// @return
		///
		virtual std::string ToString() const = 0;

		///
		/// @brief 重载强制转换为字符串的运算符。
		///
		/// @return
		///
		explicit operator std::string() const
		{
			return ToString();
		}
	};

	///
	/// @brief 将 base::ICanToString 对象转为字符串。
	///
	/// @param o
	/// @return
	///
	inline std::string to_string(base::ICanToString const &o)
	{
		return o.ToString();
	}

} // namespace base

///
/// @brief 将 base::ICanToString 对象转为字符串后输出到输出流。
///
/// @param stream
/// @param o
/// @return
///
inline std::ostream &operator<<(std::ostream &stream, base::ICanToString const &o)
{
	stream << o.ToString();
	return stream;
}
