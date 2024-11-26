#include "ReadOnlyEthernetFrame.h"
#include <base/bit/AutoBitConverter.h>

base::ethernet::ReadOnlyEthernetFrame::ReadOnlyEthernetFrame(base::ReadOnlySpan const &span)
{
    _span = span;
}

base::Mac base::ethernet::ReadOnlyEthernetFrame::DestinationMac() const
{
    return base::Mac{std::endian::big, _span.Slice(0, 6)};
}

base::Mac base::ethernet::ReadOnlyEthernetFrame::SourceMac() const
{
    return base::Mac{std::endian::big, _span.Slice(6, 6)};
}

base::ReadOnlySpan base::ethernet::ReadOnlyEthernetFrame::VlanTag() const
{
    return base::ReadOnlySpan{_span.Slice(12, 4)};
}

bool base::ethernet::ReadOnlyEthernetFrame::HasVlanTag() const
{
    base::ReadOnlySpan span = _span.Slice(12, 2);
    base::AutoBitConverter converter{std::endian::big};
    uint16_t foo = converter.ToUInt16(span.Buffer(), 0);
    base::ethernet::LengthTypeEnum type_or_length = static_cast<base::ethernet::LengthTypeEnum>(foo);
    return type_or_length == base::ethernet::LengthTypeEnum::VlanTag;
}

base::ethernet::LengthTypeEnum base::ethernet::ReadOnlyEthernetFrame::TypeOrLength() const
{
    base::AutoBitConverter converter{std::endian::big};
    if (HasVlanTag())
    {
        base::ReadOnlySpan span = _span.Slice(16, 2);
        uint16_t type_or_length = converter.ToUInt16(span.Buffer(), 0);
        return static_cast<base::ethernet::LengthTypeEnum>(type_or_length);
    }
    else
    {
        base::ReadOnlySpan span = _span.Slice(12, 2);
        uint16_t type_or_length = converter.ToUInt16(span.Buffer(), 0);
        return static_cast<base::ethernet::LengthTypeEnum>(type_or_length);
    }
}

base::ReadOnlySpan base::ethernet::ReadOnlyEthernetFrame::Payload() const
{
    if (HasVlanTag())
    {
        return base::ReadOnlySpan{_span.Slice(18, _span.Size() - 18)};
    }
    else
    {
        return base::ReadOnlySpan{_span.Slice(14, _span.Size() - 14)};
    }
}
