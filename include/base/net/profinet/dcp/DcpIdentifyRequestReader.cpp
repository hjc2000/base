#include "DcpIdentifyRequestReader.h"

base::profinet::DcpIdentifyRequestReader::DcpIdentifyRequestReader(base::ReadOnlySpan const &span)
	: _fid_pdu_reader(span)
{
}
