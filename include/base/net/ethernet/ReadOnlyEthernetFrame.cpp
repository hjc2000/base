#include "ReadOnlyEthernetFrame.h"

base::ethernet::ReadOnlyEthernetFrame::ReadOnlyEthernetFrame(base::ReadOnlySpan const &span)
{
}

base::Mac base::ethernet::ReadOnlyEthernetFrame::DestinationMac() const
{
    return base::Mac();
}

base::Mac base::ethernet::ReadOnlyEthernetFrame::SourceMac() const
{
    return base::Mac();
}

base::ReadOnlySpan base::ethernet::ReadOnlyEthernetFrame::VlanTag() const
{
    return base::ReadOnlySpan();
}

base::ethernet::LengthTypeEnum base::ethernet::ReadOnlyEthernetFrame::TypeOrLength() const
{
    return base::ethernet::LengthTypeEnum();
}

base::ReadOnlySpan base::ethernet::ReadOnlyEthernetFrame::Payload() const
{
    return base::ReadOnlySpan();
}
