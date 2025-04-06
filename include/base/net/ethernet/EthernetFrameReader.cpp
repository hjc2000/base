#include "EthernetFrameReader.h"

base::ethernet::EthernetFrameReader::EthernetFrameReader(base::ReadOnlySpan const &span)
{
	_span = span;
}

base::Mac base::ethernet::EthernetFrameReader::DestinationMac() const
{
	return base::Mac{std::endian::big, _span.Slice(base::Range{0, 6})};
}

base::Mac base::ethernet::EthernetFrameReader::SourceMac() const
{
	return base::Mac{std::endian::big, _span.Slice(base::Range{6, 12})};
}

base::ReadOnlySpan base::ethernet::EthernetFrameReader::VlanTag() const
{
	if (HasVlanTag())
	{
		return base::ReadOnlySpan{_span.Slice(base::Range{12, 16})};
	}

	throw std::runtime_error{"本以太网帧不具备 VlanTag."};
}

bool base::ethernet::EthernetFrameReader::HasVlanTag() const
{
	uint16_t foo = _converter.FromBytes<uint16_t>(_span.Slice(base::Range{12, 14}));
	base::ethernet::LengthOrTypeEnum type_or_length = static_cast<base::ethernet::LengthOrTypeEnum>(foo);
	return type_or_length == base::ethernet::LengthOrTypeEnum::VlanTag;
}

base::ethernet::LengthOrTypeEnum base::ethernet::EthernetFrameReader::TypeOrLength() const
{
	if (HasVlanTag())
	{
		uint16_t type_or_length = _converter.FromBytes<uint16_t>(_span.Slice(base::Range{16, 18}));
		return static_cast<base::ethernet::LengthOrTypeEnum>(type_or_length);
	}
	else
	{
		uint16_t type_or_length = _converter.FromBytes<uint16_t>(_span.Slice(base::Range{12, 14}));
		return static_cast<base::ethernet::LengthOrTypeEnum>(type_or_length);
	}
}

base::ReadOnlySpan base::ethernet::EthernetFrameReader::Payload() const
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

base::Json base::ethernet::EthernetFrameReader::ToJson() const
{
	base::Json root{
		{"目的 MAC 地址", DestinationMac().ToString()},
		{"源 MAC 地址", SourceMac().ToString()},
		{"TypeOrLength", std::to_string(TypeOrLength())},
		{"是否具有 VlangTag", HasVlanTag()},
	};

	return root;
}
