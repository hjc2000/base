#include "ReadOnlySpan.h"
#include "base/string/String.h"

base::ReadOnlySpan::ReadOnlySpan(base::String const &str)
{
	base::ReadOnlySpan span = str.Span();
	*this = span;
}
