#include "Period.h"
#include <base/unit/Hz.h>

base::Period::Period(base::Fraction const &value)
{
    _value = value;
}

base::Period::Period(int64_t value)
{
    _value = value;
}

base::Period::Period(base::Hz const &value)
{
    _value = value.Value().Reciprocal();
}
