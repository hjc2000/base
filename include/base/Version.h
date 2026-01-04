#pragma once
#include "base/task/Mutex.h"
#include <cstdint>

namespace base
{
	///
	/// @brief 版本号。
	///
	class Version
	{
	private:
		base::task::Mutex _lock{};
		uint64_t _value = 0;

	public:
		Version() = default;

		Version(base::Version const &o)
		{
			*this = o;
		}

		Version &operator=(base::Version const &o)
		{
			base::task::MutexGuard g[]{_lock, o._lock};
			_value = o._value;
			return *this;
		}

		///
		/// @brief 前缀递增。
		///
		/// @return
		///
		base::Version &operator++()
		{
			base::task::MutexGuard g{_lock};
			++_value;
			return *this;
		}

		///
		/// @brief 后缀递增。
		///
		/// @return
		///
		base::Version operator++(int)
		{
			base::task::MutexGuard g{_lock};
			base::Version ret{*this};
			++(*this);
			return ret;
		}

		/* #region 比较运算符 */

		bool operator==(base::Version const &another) const
		{
			base::task::MutexGuard g[]{_lock, another._lock};
			return _value == another._value;
		}

		bool operator<(base::Version const &another) const
		{
			base::task::MutexGuard g[]{_lock, another._lock};
			return _value < another._value;
		}

		bool operator>(base::Version const &another) const
		{
			base::task::MutexGuard g[]{_lock, another._lock};
			return _value > another._value;
		}

		bool operator<=(base::Version const &another) const
		{
			base::task::MutexGuard g[]{_lock, another._lock};
			return _value <= another._value;
		}

		bool operator>=(base::Version const &another) const
		{
			base::task::MutexGuard g[]{_lock, another._lock};
			return _value >= another._value;
		}

		/* #endregion */

		uint64_t Value() const
		{
			base::task::MutexGuard g{_lock};
			return _value;
		}
	};

} // namespace base
