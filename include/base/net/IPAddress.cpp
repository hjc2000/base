#include "IPAddress.h"
#include <base/string/ToHexString.h>
#include <stdexcept>

#pragma region 生命周期

base::IPAddress::IPAddress()
{
	_type = IPAddressType::IPV4;
	_span = base::Span{_ip_address_buffer.Buffer(), 4};
}

base::IPAddress::IPAddress(IPAddressType type)
{
	_type = type;
	if (_type == IPAddressType::IPV4)
	{
		_span = base::Span{_ip_address_buffer.Buffer(), 4};
	}
	else
	{
		_span = base::Span{_ip_address_buffer.Buffer(), 16};
	}
}

base::IPAddress::IPAddress(std::endian endian, base::Array<uint8_t, 4> const &ip_address_buffer)
{
	_type = IPAddressType::IPV4;
	_span = base::Span{_ip_address_buffer.Buffer(), 4};

	_span.CopyFrom(0,
				   ip_address_buffer.Buffer(),
				   0,
				   ip_address_buffer.Count());

	// 用小端序存放 IPV4 地址
	if (endian != std::endian::little)
	{
		_span.Reverse();
	}
}

base::IPAddress::IPAddress(std::endian endian, base::Array<uint8_t, 16> const &ip_address_buffer)
{
	_type = IPAddressType::IPV6;
	_span = base::Span{_ip_address_buffer.Buffer(), 16};

	_span.CopyFrom(0,
				   ip_address_buffer.Buffer(),
				   0,
				   ip_address_buffer.Count());

	// 用小端序存放 IPV6 地址
	if (endian != std::endian::little)
	{
		_span.Reverse();
	}
}

base::IPAddress::IPAddress(std::endian endian, std::initializer_list<uint8_t> const &list)
{
	if (list.size() == 4)
	{
		_type = IPAddressType::IPV4;
		_span = base::Span{_ip_address_buffer.Buffer(), 4};
		_span.CopyFrom(0, list);

		// 用小端序存放 IPV4 地址
		if (endian != std::endian::little)
		{
			_span.Reverse();
		}
	}
	else if (list.size() == 16)
	{
		_type = IPAddressType::IPV6;
		_span = base::Span{_ip_address_buffer.Buffer(), 16};
		_span.CopyFrom(0, list);

		// 用小端序存放 IPV6 地址
		if (endian != std::endian::little)
		{
			_span.Reverse();
		}
	}
	else
	{
		throw std::invalid_argument{"传入的初始化列表的尺寸不符合要求。"};
	}
}

base::IPAddress::IPAddress(std::endian endian, base::ReadOnlySpan const &span)
{
	if (span.Size() == 4)
	{
		_type = IPAddressType::IPV4;
		_span = base::Span{_ip_address_buffer.Buffer(), 4};
		_span.CopyFrom(span);

		// 用小端序存放 IPV4 地址
		if (endian != std::endian::little)
		{
			_span.Reverse();
		}
	}
	else if (span.Size() == 16)
	{
		_type = IPAddressType::IPV6;
		_span = base::Span{_ip_address_buffer.Buffer(), 16};
		_span.CopyFrom(span);

		// 用小端序存放 IPV6 地址
		if (endian != std::endian::little)
		{
			_span.Reverse();
		}
	}
	else
	{
		throw std::invalid_argument{"传入的 span 的尺寸不符合要求。"};
	}
}

base::IPAddress::IPAddress(IPAddress const &o)
{
	*this = o;
}

base::IPAddress &base::IPAddress::operator=(IPAddress const &o)
{
	_ip_address_buffer = o._ip_address_buffer;
	_span = base::Span{_ip_address_buffer.Buffer(), o._span.Size()};
	_type = o._type;
	return *this;
}

#pragma endregion

uint8_t &base::IPAddress::operator[](int index)
{
	if (index < 0 || index >= _span.Size())
	{
		throw std::out_of_range{"索引超出范围"};
	}

	return _span[index];
}

uint8_t const &base::IPAddress::operator[](int index) const
{
	if (index < 0 || index >= _span.Size())
	{
		throw std::out_of_range{"索引超出范围"};
	}

	return _span[index];
}

base::IPAddressType base::IPAddress::Type() const
{
	return _type;
}

std::string base::IPAddress::ToString() const
{
	std::string ret;

	base::ToHexStringOption option;
	option.width = 2;
	option.with_0x_prefix = false;

	if (_type == IPAddressType::IPV4)
	{
		bool first_loop = true;
		for (uint8_t num : _span)
		{
			if (first_loop)
			{
				first_loop = false;
			}
			else
			{
				ret = '.' + ret;
			}

			ret = std::to_string(num) + ret;
		}
	}
	else
	{
		int loop_times = 0;
		for (uint8_t num : _span)
		{
			if (loop_times > 0 && loop_times % 2 == 0)
			{
				ret = ':' + ret;
			}

			ret = base::ToHexString(num, option) + ret;
			loop_times++;
		}
	}

	return ret;
}

base::Span base::IPAddress::AsSpan()
{
	return _span;
}

base::ReadOnlySpan base::IPAddress::AsReadOnlySpan() const
{
	return _span;
}

base::Array<uint8_t, 16> const &base::IPAddress::InternalArray() const
{
	return _ip_address_buffer;
}

base::Array<uint8_t, 16> &base::IPAddress::InternalArray()
{
	return _ip_address_buffer;
}

#pragma region 测试

#if HAS_THREAD
#include <iostream>

void base::TestIpAddress()
{
	{
		base::IPAddress ip{
			std::endian::big,
			{
				192,
				168,
				1,
				1,
			},
		};

		std::cout << ip << std::endl;
	}

	{
		base::IPAddress ip{
			std::endian::big,
			{
				0x20, 0x01, // 2001
				0x0d, 0xb8, // 0db8
				0x85, 0xa3, // 85a3
				0x00, 0x00, // 0000
				0x00, 0x00, // 0000
				0x8a, 0x2e, // 8a2e
				0x03, 0x70, // 0370
				0x73, 0x34  // 7334
			},
		};

		std::cout << ip << std::endl;
	}
}
#endif // HAS_THREAD

#pragma endregion
