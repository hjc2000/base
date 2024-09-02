#include "Hz.h"
#include <base/unit/Period.h>

base::Hz::Hz(base::Fraction const &value)
{
    _value = value;
}

base::Hz::Hz(int64_t value)
{
    _value = value;
}

base::Hz::Hz(base::Period const &value)
{
    _value = value.Value().Reciprocal();
}
