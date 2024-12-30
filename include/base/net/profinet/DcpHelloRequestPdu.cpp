#include "DcpHelloRequestPdu.h"

base::profinet::DcpHelloRequestPdu::DcpHelloRequestPdu(base::profinet::FidApdu const &fid_apdu)
{
	_fid_apdu = fid_apdu;
}

base::Span base::profinet::DcpHelloRequestPdu::Span() const
{
	return _fid_apdu.Payload();
}

void base::profinet::DcpHelloRequestPdu::ConfigureLowlayer()
{
	_fid_apdu.ConfigureLowlayer();
	_fid_apdu.SetFrameId(base::profinet::FrameIdEnum::DcpHelloRequest);
}
