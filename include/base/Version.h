#pragma once
#include "base/task/IMutex.h"
#include "task/IMutex.h"
#include <cstdint>
#include <memory>

namespace base
{
	///
	/// @brief 版本号。
	///
	///
	class Version
	{
	private:
		std::shared_ptr<base::IMutex> _lock = base::CreateIMutex();
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
