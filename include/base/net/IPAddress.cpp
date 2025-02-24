#include "IPAddress.h"
#include <base/string/define.h>
#include <base/string/ToHexString.h>
#include <stdexcept>

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
	_span.CopyFrom(ip_address_buffer.AsReadOnlyArraySpan());

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
	_span.CopyFrom(ip_address_buffer.AsReadOnlyArraySpan());

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
		_span.CopyFrom(list);

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
		_span.CopyFrom(list);

		// 用小端序存放 IPV6 地址
		if (endian != std::endian::little)
		{
			_span.Reverse();
		}
	}
	else
	{
		throw std::invalid_argument{CODE_POS_STR + "传入的初始化列表的尺寸不符合要求。"};
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
		throw std::invalid_argument{CODE_POS_STR + "传入的 span 的尺寸不符合要求。"};
	}
}

base::IPAddress::IPAddress(base::String const &ip_str)
{
	base::StringSplitOptions split_options;
	split_options.trim_each_substring = true;
	split_options.remove_empty_substring = false;

	if (ip_str.Contains('.'))
	{
		// 是 IPV4 地址
		base::List<base::String> sub_string_list = ip_str.Split('.', split_options);
		if (sub_string_list.Count() != 4)
		{
			throw std::invalid_argument{"非法的 IPV4 地址字符串。"};
		}

		_type = IPAddressType::IPV4;
		_span = base::Span{_ip_address_buffer.Buffer(), 4};
		for (int32_t i = 0; i < 4; i++)
		{
			std::string str_to_be_converted = sub_string_list[i].StdString();
			_span[i] = std::stoi(str_to_be_converted);
		}

		// 字符串是大端序表示的，所以要翻转。
		_span.Reverse();
	}
	else if (ip_str.Contains(':'))
	{
		// 是 IPV6 地址
		base::List<base::String> sub_string_list = ip_str.Split(':', split_options);
		if (sub_string_list.Count() != 8)
		{
			throw std::invalid_argument{"非法的 IPV6 地址字符串。"};
		}

		_type = IPAddressType::IPV6;
		_span = base::Span{_ip_address_buffer.Buffer(), 16};

		/**
		 * IPV6 地址类似：2001:0db8:85a3:0000:0000:8a2e:0370:7334
		 * 是是用冒号分隔的 8 个 16 进制数。每个 16 进制数都是 uint16_t 可以装下的。
		 */
		uint16_t *ipv6_element_buffer = reinterpret_cast<uint16_t *>(_span.Buffer());

		for (int32_t i = 0; i < 8; i++)
		{
			std::string str_to_be_converted = sub_string_list[i].StdString();
			ipv6_element_buffer[i] = std::stoi(str_to_be_converted, nullptr, 16);
			if (std::endian::native == std::endian::little)
			{
				/**
				 * 如果本机是小端序，字符串转换成的数字是小端序的。
				 * 局部翻转成大端序，这样最后整个 _span 内的每个字节都是大端序。然后一起翻转一次，整个
				 * _span 就是小端序的了。
				 */
				std::reverse(&_span[i * 2], &_span[i * 2] + sizeof(uint16_t));
			}
		}

		// 字符串是大端序表示的，所以要翻转。
		_span.Reverse();
	}
	else
	{
		throw std::invalid_argument{"必须是点分 10 进制的 IPV4 地址或冒号分 16 进制的 IPV6 地址"};
	}
}

base::IPAddress::IPAddress(IPAddress const &o)
{
	*this = o;
}

base::IPAddress &base::IPAddress::operator=(IPAddress const &o)
{
	_ip_address_buffer = o._ip_address_buffer;
	_type = o._type;

	int size = 4;
	if (_type == base::IPAddressType::IPV6)
	{
		size = 16;
	}

	_span = base::Span{_ip_address_buffer.Buffer(), size};
	return *this;
}

uint8_t &base::IPAddress::operator[](int index)
{
	if (index < 0 || index >= _span.Size())
	{
		throw std::out_of_range{CODE_POS_STR + "索引超出范围"};
	}

	return _span[index];
}

uint8_t const &base::IPAddress::operator[](int index) const
{
	if (index < 0 || index >= _span.Size())
	{
		throw std::out_of_range{CODE_POS_STR + "索引超出范围"};
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
