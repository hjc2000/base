#include "ApduStatus.h"

base::profinet::ApduStatus::ApduStatus(base::Span const &span)
{
	_span = span;
}

base::Span const &base::profinet::ApduStatus::Span() const
{
	return _span;
}

uint16_t base::profinet::ApduStatus::CycleCounter() const
{
	return 0;
}

void base::profinet::ApduStatus::SetCycleCounter(uint16_t value)
{
}

uint8_t base::profinet::ApduStatus::DataStatus() const
{
	return 0;
}

void base::profinet::ApduStatus::SetDataStatus(uint8_t value)
{
}

uint8_t base::profinet::ApduStatus::TransferStatus() const
{
	return 0;
}

void base::profinet::ApduStatus::SetTransferStatus(uint8_t value)
{
}
