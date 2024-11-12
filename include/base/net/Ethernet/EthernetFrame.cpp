#include "EthernetFrame.h"

base::EthernetFrame::EthernetFrame(base::Span span)
{
}

base::Mac base::EthernetFrame::DestinationMac() const
{
    return base::Mac();
}

void base::EthernetFrame::SetDestinationMac(base::Mac const &value)
{
}

base::Mac base::EthernetFrame::SourceMac() const
{
    return base::Mac();
}

void base::EthernetFrame::SetSourceMac(base::Mac const &value)
{
}

base::Span base::EthernetFrame::VlanTag() const
{
    return base::Span();
}

void base::EthernetFrame::SetVlanTag(base::Span const &value)
{
}

uint16_t base::EthernetFrame::TypeOrLength() const
{
    return 0;
}

void base::EthernetFrame::SetTypeOrLength(uint16_t value)
{
}

base::Span base::EthernetFrame::Payload() const
{
    return base::Span();
}

void base::EthernetFrame::SetPayload(base::Span const &value)
{
}

base::Span base::EthernetFrame::FrameCheckSequence() const
{
    return base::Span();
}

void base::EthernetFrame::SetFrameCheckSequence(base::Span const &value)
{
}
