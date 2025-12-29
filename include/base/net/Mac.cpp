#include "Mac.h" // IWYU pragma: keep

base::Mac::operator uint64_t() const
{
	/* _mac_buffer 中的数据此时被当作远程字节序，也是小端序。转换成整型，需要根据本机字节序
	 * 决定是否需要翻转。
	 */
	uint64_t value = base::little_endian_remote_converter.FromBytes<uint64_t>(
		base::ReadOnlySpan{
			_mac_buffer.Buffer(),
			_mac_buffer.Count(),
		});

	return value;
}

std::string base::Mac::ToString() const
{
	std::string ret{};
	bool first_loop = true;

	base::ToHexStringOptions option{};
	option.with_0x_prefix = false;
	option.width = 2;

	for (uint8_t value : _mac_buffer)
	{
		if (first_loop)
		{
			first_loop = false;
			ret = base::ToHexString(value, option);
		}
		else
		{
			ret = base::ToHexString(value, option) + '-' + ret;
		}
	}

	return ret;
}

base::ReadOnlySpan base::Mac::Span() const
{
	return base::ReadOnlySpan{_mac_buffer.Buffer(), _mac_buffer.Count()};
}

base::Span base::Mac::Span()
{
	return base::Span{_mac_buffer.Buffer(), _mac_buffer.Count()};
}

uint8_t &base::Mac::operator[](int index)
{
	return _mac_buffer[index];
}

uint8_t const &base::Mac::operator[](int index) const
{
	return _mac_buffer[index];
}

base::Array<uint8_t, 3> base::Mac::Oui() const
{
	return base::Array<uint8_t, 3>{_mac_buffer.Span().Slice(base::Range{3, 6})};
}

void base::Mac::SetOui(base::Array<uint8_t, 3> const &value)
{
	_mac_buffer.Span().Slice(base::Range{3, 6}).CopyFrom(value.Span());
}

bool base::Mac::IsMulticastAddress() const
{
	// 最高字节的最低位为 1 则是多播地址，为 0 则是单播地址。
	return _mac_buffer[5] & 0x01;
}
