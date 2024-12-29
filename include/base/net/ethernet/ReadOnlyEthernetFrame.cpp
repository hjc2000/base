#include "ReadOnlyEthernetFrame.h"

base::ethernet::ReadOnlyEthernetFrame::ReadOnlyEthernetFrame(base::ReadOnlySpan const &span)
{
	_span = span;
}

base::Mac base::ethernet::ReadOnlyEthernetFrame::DestinationMac() const
{
	return base::Mac{std::endian::big, _span.Slice(base::Range{0, 6})};
}

base::Mac base::ethernet::ReadOnlyEthernetFrame::SourceMac() const
{
	return base::Mac{std::endian::big, _span.Slice(base::Range{6, 12})};
}

base::ReadOnlySpan base::ethernet::ReadOnlyEthernetFrame::VlanTag() const
{
	if (HasVlanTag())
	{
		return base::ReadOnlySpan{_span.Slice(base::Range{12, 16})};
	}

	throw std::runtime_error{"本以太网帧不具备 VlanTag."};
}

bool base::ethernet::ReadOnlyEthernetFrame::HasVlanTag() const
{
	uint16_t foo = _converter.ToUInt16(_span.Slice(base::Range{12, 14}));
	base::ethernet::LengthTypeEnum type_or_length = static_cast<base::ethernet::LengthTypeEnum>(foo);
	return type_or_length == base::ethernet::LengthTypeEnum::VlanTag;
}

base::ethernet::LengthTypeEnum base::ethernet::ReadOnlyEthernetFrame::TypeOrLength() const
{
	if (HasVlanTag())
	{
		uint16_t type_or_length = _converter.ToUInt16(_span.Slice(base::Range{16, 18}));
		return static_cast<base::ethernet::LengthTypeEnum>(type_or_length);
	}
	else
	{
		uint16_t type_or_length = _converter.ToUInt16(_span.Slice(base::Range{12, 14}));
		return static_cast<base::ethernet::LengthTypeEnum>(type_or_length);
	}
}

base::ReadOnlySpan base::ethernet::ReadOnlyEthernetFrame::Payload() const
{
	if (HasVlanTag())
	{
		return _span.Slice(base::Range{18, _span.Size()});
	}
	else
	{
		return _span.Slice(base::Range{14, _span.Size()});
	}
}

base::Json base::ethernet::ReadOnlyEthernetFrame::ToJson() const
{
	base::Json root{
		{"目的 MAC 地址", DestinationMac().ToString()},
		{"源 MAC 地址", SourceMac().ToString()},
		{"TypeOrLength", base::ToString(TypeOrLength())},
		{"是否具有 VlangTag", HasVlanTag()},
	};

	return root;
}
