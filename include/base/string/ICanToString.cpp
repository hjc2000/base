#include "ICanToString.h"

#if HAS_THREAD
std::ostream &operator<<(std::ostream &stream, base::ICanToString const &o)
{
    stream << o;
    return stream;
}
#endif
