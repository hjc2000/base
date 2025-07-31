#include "Hz.h"
#include "base/unit/MHz.h"
#include "base/unit/Nanosecond.h"
#include "base/unit/Second.h"

/* #region 构造函数 */

base::unit::Hz::Hz(base::unit::Nanosecond const &value)
	: Hz(base::unit::Second{value})
{
}

/* #endregion */
