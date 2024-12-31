#include "EthernetFrameWriter.h"

base::ethernet::EthernetFrameWriter::EthernetFrameWriter(base::Span const &span)
{
	_span = span;
}

base::Mac base::ethernet::EthernetFrameWriter::DestinationMac() const
{
	return base::Mac{std::endian::big, _span.Slice(base::Range{0, 6})};
}

void base::ethernet::EthernetFrameWriter::SetDestinationMac(base::Mac const &value)
{
	base::Span span = _span.Slice(base::Range{0, 6});
	span.CopyFrom(value.AsReadOnlySpan());
	span.Reverse();
}

base::Mac base::ethernet::EthernetFrameWriter::SourceMac() const
{
	return base::Mac{std::endian::big, _span.Slice(base::Range{6, 12})};
}

void base::ethernet::EthernetFrameWriter::SetSourceMac(base::Mac const &value)
{
	base::Span span = _span.Slice(base::Range{6, 12});
	span.CopyFrom(value.AsReadOnlySpan());
	span.Reverse();
}

base::Span base::ethernet::EthernetFrameWriter::VlanTag() const
{
	if (HasVlanTag())
	{
		return base::Span{_span.Slice(base::Range{12, 16})};
	}

	throw std::runtime_error{"本以太网帧不具备 VlanTag."};
}

void base::ethernet::EthernetFrameWriter::SetVlanTag(base::Span const &value)
{
	base::Span span = _span.Slice(base::Range{12, 16});
	span.CopyFrom(value);
}

bool base::ethernet::EthernetFrameWriter::HasVlanTag() const
{
	uint16_t foo = _converter.ToUInt16(_span.Slice(base::Range{12, 14}));
	base::ethernet::LengthOrTypeEnum type_or_length = static_cast<base::ethernet::LengthOrTypeEnum>(foo);
	return type_or_length == base::ethernet::LengthOrTypeEnum::VlanTag;
}

void base::ethernet::EthernetFrameWriter::ClearVlanTag()
{
	if (HasVlanTag())
	{
		base::Span span = _span.Slice(base::Range{12, 16});
		span.FillWithZero();
	}
}

base::ethernet::LengthOrTypeEnum base::ethernet::EthernetFrameWriter::TypeOrLength() const
{
	if (HasVlanTag())
	{
		uint16_t type_or_length = _converter.ToUInt16(_span.Slice(base::Range{16, 18}));
		return static_cast<base::ethernet::LengthOrTypeEnum>(type_or_length);
	}
	else
	{
		uint16_t type_or_length = _converter.ToUInt16(_span.Slice(base::Range{12, 14}));
		return static_cast<base::ethernet::LengthOrTypeEnum>(type_or_length);
	}
}

void base::ethernet::EthernetFrameWriter::SetTypeOrLength(LengthOrTypeEnum value)
{
	if (HasVlanTag())
	{
		_converter.GetBytes(static_cast<uint16_t>(value), _span.Slice(base::Range{16, 18}));
	}
	else
	{
		_converter.GetBytes(static_cast<uint16_t>(value), _span.Slice(base::Range{12, 14}));
	}
}

base::Span base::ethernet::EthernetFrameWriter::Payload() const
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

void base::ethernet::EthernetFrameWriter::SetValidPayloadSize(int32_t value)
{
	if (HasVlanTag())
	{
		if (value < 46)
		{
			/**
			 * 载荷不足 46 字节，需要填充值为 0 的字节，从而达到 46 字节。
			 * 所以有效载荷的最后一个字节后到第 46 字节的这段内存要清零。
			 */
			_span.Slice(base::Range{18 + value, 18 + 46}).FillWithZero();
			_valid_frame_size = 18 + 46;
		}
		else
		{
			_valid_frame_size = 18 + value;
		}
	}
	else
	{
		if (value < 46)
		{
			/**
			 * 载荷不足 46 字节，需要填充值为 0 的字节，从而达到 46 字节。
			 * 所以有效载荷的最后一个字节后到第 46 字节的这段内存要清零。
			 */
			_span.Slice(base::Range{14 + value, 14 + 46}).FillWithZero();
			_valid_frame_size = 14 + 46;
		}
		else
		{
			_valid_frame_size = 14 + value;
		}
	}
}

base::Span base::ethernet::EthernetFrameWriter::ValidDataSpan() const
{
	return _span.Slice(base::Range{0, FrameSize()});
}

int base::ethernet::EthernetFrameWriter::FrameSize() const
{
	if (HasVlanTag())
	{
		if (_valid_frame_size < 64)
		{
			return 64;
		}
		else
		{
			return _valid_frame_size;
		}
	}
	else
	{
		if (_valid_frame_size < 60)
		{
			return 60;
		}
		else
		{
			return _valid_frame_size;
		}
	}
}
