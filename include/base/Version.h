#pragma once
#include <cstdint>

namespace base
{
	///
	/// @brief 版本号。
	///
	///
	class Version
	{
	private:
		uint64_t _value = 0;

	public:
		///
		/// @brief 前缀递增。
		///
		/// @return Version&
		///
		base::Version &operator++();

		///
		/// @brief 后缀递增。
		///
		/// @return Version
		///
		base::Version operator++(int);

		/* #region 比较运算符 */

		bool operator==(base::Version const &another) const
		{
			return _value == another._value;
		}

		bool operator<(base::Version const &another) const
		{
			return _value < another._value;
		}

		bool operator>(base::Version const &another) const
		{
			return _value > another._value;
		}

		bool operator<=(base::Version const &another) const
		{
			return _value <= another._value;
		}

		bool operator>=(base::Version const &another) const
		{
			return _value >= another._value;
		}

		/* #endregion */

		uint64_t Value() const;
	};
} // namespace base
