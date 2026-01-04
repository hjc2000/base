#include "Version.h" // IWYU pragma: keep

/* #region 比较运算符 */

bool base::Version::operator==(base::Version const &another) const
{
	base::task::MutexGuard g[]{_lock, another._lock};
	return _value == another._value;
}

bool base::Version::operator<(base::Version const &another) const
{
	base::task::MutexGuard g[]{_lock, another._lock};
	return _value < another._value;
}

bool base::Version::operator>(base::Version const &another) const
{
	base::task::MutexGuard g[]{_lock, another._lock};
	return _value > another._value;
}

bool base::Version::operator<=(base::Version const &another) const
{
	base::task::MutexGuard g[]{_lock, another._lock};
	return _value <= another._value;
}

bool base::Version::operator>=(base::Version const &another) const
{
	base::task::MutexGuard g[]{_lock, another._lock};
	return _value >= another._value;
}

/* #endregion */

uint64_t base::Version::Value() const
{
	base::task::MutexGuard g{_lock};
	return _value;
}
