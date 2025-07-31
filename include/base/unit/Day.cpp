#include "Day.h"
#include "base/unit/Hour.h"
#include "base/unit/Minute.h"
#include "base/unit/Nanosecond.h"

/* #region 强制转换运算符 */

base::unit::Day::operator std::chrono::days() const
{
	return std::chrono::days{base::unit::Hour{*this}};
}

base::unit::Day::operator std::chrono::hours() const
{
	return std::chrono::hours{base::unit::Hour{*this}};
}

base::unit::Day::operator std::chrono::minutes() const
{
	return std::chrono::minutes{base::unit::Hour{*this}};
}

base::unit::Day::operator std::chrono::seconds() const
{
	return std::chrono::seconds{base::unit::Hour{*this}};
}

base::unit::Day::operator std::chrono::milliseconds() const
{
	return std::chrono::milliseconds{base::unit::Hour{*this}};
}

base::unit::Day::operator std::chrono::microseconds() const
{
	return std::chrono::microseconds{base::unit::Hour{*this}};
}

base::unit::Day::operator std::chrono::nanoseconds() const
{
	return std::chrono::nanoseconds{base::unit::Hour{*this}};
}

/* #endregion */
