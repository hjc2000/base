#include "Second.h"
#include "base/unit/Hour.h"
#include "base/unit/Hz.h"
#include "base/unit/MHz.h"
#include "base/unit/Nanosecond.h"

base::unit::Second::Second(base::unit::MHz const &value)
	: Second(base::unit::Hz{value})
{
}
