#pragma once
#include "base/task/Mutex.h"
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
		base::task::Mutex _lock{};
		uint64_t _value = 0;

	public:
		Version() = default;

		Version(base::Version const &o);

		Version &operator=(base::Version const &o);

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

		bool operator==(base::Version const &another) const;

		bool operator<(base::Version const &another) const;

		bool operator>(base::Version const &another) const;

		bool operator<=(base::Version const &another) const;

		bool operator>=(base::Version const &another) const;

		/* #endregion */

		uint64_t Value() const;
	};
} // namespace base
