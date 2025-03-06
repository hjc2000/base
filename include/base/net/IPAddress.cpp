#include "IPAddress.h"
#include <base/string/define.h>
#include <base/string/ToHexString.h>
#include <stdexcept>

base::IPAddress::Context::Context(base::IPAddressType type)
{
	_type = type;
}

base::Span base::IPAddress::Context::Span()
{
	if (_type == base::IPAddressType::IPV4)
	{
		return base::Span{_ip_address_buffer.Buffer(), 4};
	}

	return base::Span{_ip_address_buffer.Buffer(), 16};
}

base::ReadOnlySpan base::IPAddress::Context::Span() const
{
	if (_type == base::IPAddressType::IPV4)
	{
		return base::ReadOnlySpan{_ip_address_buffer.Buffer(), 4};
	}

	return base::ReadOnlySpan{_ip_address_buffer.Buffer(), 16};
}

base::IPAddressType base::IPAddress::Context::IPAddressType() const
{
	return _type;
}

base::IPAddress::IPAddress(base::IPAddressType type)
{
	_context = Context{type};
}

base::IPAddress::IPAddress(std::endian endian, base::Array<uint8_t, 4> const &ip_address_buffer)
{
	_context = Context{base::IPAddressType::IPV4};
	_context.Span().CopyFrom(ip_address_buffer.Span());

	// 用小端序存放 IPV4 地址
	if (endian != std::endian::little)
	{
		_context.Span().Reverse();
	}
}

base::IPAddress::IPAddress(std::endian endian, base::Array<uint8_t, 16> const &ip_address_buffer)
{
	_context = Context{base::IPAddressType::IPV6};
	_context.Span().CopyFrom(ip_address_buffer.Span());

	// 用小端序存放 IPV6 地址
	if (endian != std::endian::little)
	{
		_context.Span().Reverse();
	}
}

base::IPAddress::IPAddress(std::endian endian, std::initializer_list<uint8_t> const &list)
{
	if (list.size() == 4)
	{
		_context = Context{base::IPAddressType::IPV4};
		_context.Span().CopyFrom(list);

		// 用小端序存放 IPV4 地址
		if (endian != std::endian::little)
		{
			_context.Span().Reverse();
		}
	}
	else if (list.size() == 16)
	{
		_context = Context{base::IPAddressType::IPV6};
		_context.Span().CopyFrom(list);

		// 用小端序存放 IPV6 地址
		if (endian != std::endian::little)
		{
			_context.Span().Reverse();
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
		_context = Context{base::IPAddressType::IPV4};
		_context.Span().CopyFrom(span);

		// 用小端序存放 IPV4 地址
		if (endian != std::endian::little)
		{
			_context.Span().Reverse();
		}
	}
	else if (span.Size() == 16)
	{
		_context = Context{base::IPAddressType::IPV6};
		_context.Span().CopyFrom(span);

		// 用小端序存放 IPV6 地址
		if (endian != std::endian::little)
		{
			_context.Span().Reverse();
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

		_context = Context{base::IPAddressType::IPV4};
		for (int32_t i = 0; i < 4; i++)
		{
			std::string str_to_be_converted = sub_string_list[i].StdString();
			_context.Span()[i] = std::stoi(str_to_be_converted);
		}

		// 字符串是大端序表示的，所以要翻转。
		_context.Span().Reverse();
	}
	else if (ip_str.Contains(':'))
	{
		// 是 IPV6 地址
		base::List<base::String> sub_string_list = ip_str.Split(':', split_options);
		if (sub_string_list.Count() != 8)
		{
			throw std::invalid_argument{"非法的 IPV6 地址字符串。"};
		}

		_context = Context{base::IPAddressType::IPV6};

		/**
		 * IPV6 地址类似：2001:0db8:85a3:0000:0000:8a2e:0370:7334
		 * 是是用冒号分隔的 8 个 16 进制数。每个 16 进制数都是 uint16_t 可以装下的。
		 */
		uint16_t *ipv6_element_buffer = reinterpret_cast<uint16_t *>(_context.Span().Buffer());

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
				std::reverse(&_context.Span()[i * 2], &_context.Span()[i * 2] + sizeof(uint16_t));
			}
		}

		// 字符串是大端序表示的，所以要翻转。
		_context.Span().Reverse();
	}
	else
	{
		throw std::invalid_argument{"必须是点分 10 进制的 IPV4 地址或冒号分 16 进制的 IPV6 地址"};
	}
}

uint8_t &base::IPAddress::operator[](int index)
{
	if (index < 0 || index >= _context.Span().Size())
	{
		throw std::out_of_range{CODE_POS_STR + "索引超出范围"};
	}

	return _context.Span()[index];
}

uint8_t const &base::IPAddress::operator[](int index) const
{
	if (index < 0 || index >= _context.Span().Size())
	{
		throw std::out_of_range{CODE_POS_STR + "索引超出范围"};
	}

	return _context.Span()[index];
}

base::IPAddressType base::IPAddress::Type() const
{
	return _context.IPAddressType();
}

std::string base::IPAddress::ToString() const
{
	std::string ret;

	base::ToHexStringOption option;
	option.width = 2;
	option.with_0x_prefix = false;

	if (_context.IPAddressType() == base::IPAddressType::IPV4)
	{
		bool first_loop = true;
		for (uint8_t num : _context.Span())
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
		for (uint8_t num : _context.Span())
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

base::Span base::IPAddress::Span()
{
	return _context.Span();
}

base::ReadOnlySpan base::IPAddress::Span() const
{
	return _context.Span();
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
