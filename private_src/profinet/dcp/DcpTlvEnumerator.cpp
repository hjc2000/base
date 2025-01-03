#include "DcpTlvEnumerator.h"

base::profinet::DcpTlvEnumerator::DcpTlvEnumerator(base::ReadOnlySpan const &span)
{
	_span = span;
	Reset();
}
