#include "EthernetFrame.h"

base::ethernet::EthernetFrame::EthernetFrame(base::Span const &span)
{
    _span = span;
}

base::Mac base::ethernet::EthernetFrame::DestinationMac() const
{
    return base::Mac();
}

void base::ethernet::EthernetFrame::SetDestinationMac(base::Mac const &value)
{
}

base::Mac base::ethernet::EthernetFrame::SourceMac() const
{
    return base::Mac();
}

void base::ethernet::EthernetFrame::SetSourceMac(base::Mac const &value)
{
}

base::Span base::ethernet::EthernetFrame::VlanTag() const
{
    return base::Span();
}

void base::ethernet::EthernetFrame::SetVlanTag(base::Span const &value)
{
}

bool base::ethernet::EthernetFrame::HasVlanTag() const
{
    return _has_vlan_tag;
}

void base::ethernet::EthernetFrame::SetHasVlanTag(bool value)
{
    _has_vlan_tag = value;
}

base::ethernet::LengthTypeEnum base::ethernet::EthernetFrame::TypeOrLength() const
{
    return base::ethernet::LengthTypeEnum::IP;
}

void base::ethernet::EthernetFrame::SetTypeOrLength(LengthTypeEnum value)
{
}

base::Span base::ethernet::EthernetFrame::Payload() const
{
    return base::Span();
}

void base::ethernet::EthernetFrame::SetPayload(base::Span const &value)
{
}
