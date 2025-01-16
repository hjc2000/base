#include "ICanToString.h"

std::ostream &operator<<(std::ostream &stream, base::ICanToString const &o)
{
	stream << o.ToString();
	return stream;
}

std::string std::to_string(base::ICanToString const &o)
{
	return o.ToString();
}
