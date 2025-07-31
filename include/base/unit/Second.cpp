#include "Second.h"
#include "base/unit/Hour.h"
#include "base/unit/Hz.h"
#include "base/unit/Nanosecond.h"

/* #region 构造函数 */

base::unit::Second::Second(base::unit::Hour const &value)
{
	_value = static_cast<base::Fraction>(value) * 60 * 60;
}

base::unit::Second::Second(base::unit::Hz const &value)
{
	_value = static_cast<base::Fraction>(value).Reciprocal();
}

base::unit::Second::Second(base::unit::MHz const &value)
	: Second(base::unit::Hz{value})
{
}

/* #endregion */
