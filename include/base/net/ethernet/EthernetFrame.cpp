#include "EthernetFrame.h"
#include <base/bit/AutoBitConverter.h>

base::ethernet::EthernetFrame::EthernetFrame(base::Span const &span)
{
    _span = span;
}

base::Mac base::ethernet::EthernetFrame::DestinationMac() const
{
    return base::Mac{std::endian::big, _span.Slice(0, 6)};
}

void base::ethernet::EthernetFrame::SetDestinationMac(base::Mac const &value)
{
    base::Span span = _span.Slice(0, 6);
    span.CopyFrom(value.AsReadOnlySpan());
    span.Reverse();
}

base::Mac base::ethernet::EthernetFrame::SourceMac() const
{
    return base::Mac{std::endian::big, _span.Slice(6, 6)};
}

void base::ethernet::EthernetFrame::SetSourceMac(base::Mac const &value)
{
    base::Span span = _span.Slice(6, 6);
    span.CopyFrom(value.AsReadOnlySpan());
    span.Reverse();
}

base::Span base::ethernet::EthernetFrame::VlanTag() const
{
    if (HasVlanTag())
    {
        return base::Span{_span.Slice(12, 4)};
    }
    else
    {
        return base::Span{};
    }
}

void base::ethernet::EthernetFrame::SetVlanTag(base::Span const &value)
{
    base::Span span = _span.Slice(12, 4);
    span.CopyFrom(value);
}

bool base::ethernet::EthernetFrame::HasVlanTag() const
{
    base::Span span = _span.Slice(12, 2);
    base::AutoBitConverter converter{std::endian::big};
    uint16_t foo = converter.ToUInt16(span.Buffer(), 0);
    base::ethernet::LengthTypeEnum type_or_length = static_cast<base::ethernet::LengthTypeEnum>(foo);
    return type_or_length == base::ethernet::LengthTypeEnum::VlanTag;
}

void base::ethernet::EthernetFrame::ClearVlanTag()
{
    if (HasVlanTag())
    {
        base::Span span = _span.Slice(12, 4);
        span.FillWithZero();
    }
}

base::ethernet::LengthTypeEnum base::ethernet::EthernetFrame::TypeOrLength() const
{
    base::AutoBitConverter converter{std::endian::big};
    if (HasVlanTag())
    {
        base::Span span = _span.Slice(16, 2);
        uint16_t type_or_length = converter.ToUInt16(span.Buffer(), 0);
        return static_cast<base::ethernet::LengthTypeEnum>(type_or_length);
    }
    else
    {
        base::Span span = _span.Slice(12, 2);
        uint16_t type_or_length = converter.ToUInt16(span.Buffer(), 0);
        return static_cast<base::ethernet::LengthTypeEnum>(type_or_length);
    }
}

void base::ethernet::EthernetFrame::SetTypeOrLength(LengthTypeEnum value)
{
    base::AutoBitConverter converter{std::endian::big};
    if (HasVlanTag())
    {
        base::Span span = _span.Slice(16, 2);

        converter.GetBytes(static_cast<uint16_t>(value),
                           span.Buffer(),
                           0);
    }
    else
    {
        base::Span span = _span.Slice(12, 2);

        converter.GetBytes(static_cast<uint16_t>(value),
                           span.Buffer(),
                           0);
    }
}

base::Span base::ethernet::EthernetFrame::Payload() const
{
    if (HasVlanTag())
    {
        return base::Span{_span.Slice(18, FrameSize() - 18)};
    }
    else
    {
        return base::Span{_span.Slice(14, FrameSize() - 14)};
    }
}

void base::ethernet::EthernetFrame::SetPayload(base::Span const &value)
{
    if (HasVlanTag())
    {
        base::Span span{_span.Slice(18, _span.Size() - 18)};
        span.CopyFrom(value);
        if (value.Size() < 46)
        {
            span.Slice(value.Size(), 46 - value.Size()).FillWithZero();
            _frame_size = 18 + 46;
        }
        else
        {
            _frame_size = 18 + value.Size();
        }
    }
    else
    {
        base::Span span{_span.Slice(14, _span.Size() - 14)};
        span.CopyFrom(value);
        if (value.Size() < 46)
        {
            span.Slice(value.Size(), 46 - value.Size()).FillWithZero();
            _frame_size = 14 + 46;
        }
        else
        {
            _frame_size = 14 + value.Size();
        }
    }
}

int base::ethernet::EthernetFrame::FrameSize() const
{
    if (HasVlanTag())
    {
        if (_frame_size < 64)
        {
            return 64;
        }
        else
        {
            return _frame_size;
        }
    }
    else
    {
        if (_frame_size < 60)
        {
            return 60;
        }
        else
        {
            return _frame_size;
        }
    }
}
