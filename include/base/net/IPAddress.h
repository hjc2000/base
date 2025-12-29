#pragma once
#include "base/container/Array.h"
#include "base/stream/ReadOnlySpan.h"
#include "base/stream/Span.h"
#include "base/string/define.h"
#include "base/string/ICanToString.h"
#include "base/string/String.h"
#include "base/string/ToHexString.h"
#include <array>
#include <bit>
#include <stdexcept>

namespace base
{
	///
	/// @brief IP 地址类型。
	///
	enum class IPAddressType
	{
		IPV4,
		IPV6,
	};

	///
	/// @brief IP 地址。兼容 IPV4 和 IPV6.
	///
	class IPAddress :
		public base::ICanToString
	{
	private:
		/* #region Context */

		class Context
		{
		private:
			std::array<uint8_t, 16> _ip_address_buffer;
			base::IPAddressType _type = base::IPAddressType::IPV4;

		public:
			Context() = default;

			Context(base::IPAddressType type)
			{
				_type = type;
			}

			base::Span Span()
			{
				if (_type == base::IPAddressType::IPV4)
				{
					return base::Span{_ip_address_buffer.data(), 4};
				}

				return base::Span{_ip_address_buffer.data(), 16};
			}

			base::ReadOnlySpan Span() const
			{
				if (_type == base::IPAddressType::IPV4)
				{
					return base::ReadOnlySpan{_ip_address_buffer.data(), 4};
				}

				return base::ReadOnlySpan{_ip_address_buffer.data(), 16};
			}

			base::IPAddressType IPAddressType() const
			{
				return _type;
			}
		};

		///
		/// @brief 上下文。
		///
		Context _context;

		/* #endregion */

	public:
		/* #region 构造函数 */

		///
		/// @brief 构造一个未指定的 IP 地址。此时表现为 IPV4 的 0.0.0.0.
		///
		IPAddress() = default;

		///
		/// @brief 构造一个未指定的 IP 地址。此时可以指定期望的 IP 地址版本。
		/// 无论是对 IPV4 还是 IPV6，构造出来的地址的所有字节都是 0.
		///
		/// @param type
		///
		IPAddress(IPAddressType type)
		{
			_context = Context{type};
		}

		///
		/// @brief 构造一个 IPV4 地址。
		///
		/// @param endian ip_address_buffer 中 IP 地址的字节序。
		/// @param ip_address_buffer 存放着 IPV4 地址的缓冲区。
		///
		IPAddress(std::endian endian, base::Array<uint8_t, 4> const &ip_address_buffer)
		{
			_context = Context{base::IPAddressType::IPV4};
			_context.Span().CopyFrom(ip_address_buffer.Span());

			// 用小端序存放 IPV4 地址
			if (endian != std::endian::little)
			{
				_context.Span().Reverse();
			}
		}

		///
		/// @brief 构造一个 IPV6 地址。
		///
		/// @param endian ip_address_buffer 中 IP 地址的字节序。
		/// @param ip_address_buffer 存放着 IPV6 地址的缓冲区。
		///
		IPAddress(std::endian endian, base::Array<uint8_t, 16> const &ip_address_buffer)
		{
			_context = Context{base::IPAddressType::IPV6};
			_context.Span().CopyFrom(ip_address_buffer.Span());

			// 用小端序存放 IPV6 地址
			if (endian != std::endian::little)
			{
				_context.Span().Reverse();
			}
		}

		///
		/// @brief 构造一个 IP 地址。
		///
		/// @note 是 IPV4 还是 IPV6 取决于初始化列表的大小。初始化列表如果是 4 字节，则构造出来
		/// 是 IPV4 地址，如果是 16 字节，则构造出来是 IPV6 地址。如果都不是，则会抛出异常。
		///
		/// @param endian 初始化列表中的 IP 地址的字节序。
		/// @param list 储存着 IP 地址的初始化列表。
		///
		IPAddress(std::endian endian, std::initializer_list<uint8_t> const &list)
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

		///
		/// @brief 从 ReadOnlySpan 构造 IP 地址。
		///
		/// @param endian span 中 IP 地址的字节序。
		///
		/// @param span 储存着 IP 地址的一段内存。
		/// 	@note 构造时不是引用这段内存，而是将这段内存中的数据拷贝过来。
		///
		IPAddress(std::endian endian, base::ReadOnlySpan const &span)
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

		///
		/// @brief 用标准的表示 IP 地址的字符串构造。
		///
		/// @note 会根据字符串格式来识别是 IPV4 地址还是 IPV6 地址。
		/// @note IPV6 地址字符串暂不支持缩写。
		///
		/// @param ip_str
		///
		IPAddress(base::String const &ip_str)
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

		/* #endregion */

		uint8_t &operator[](int index)
		{
			if (index < 0 || index >= _context.Span().Size())
			{
				throw std::out_of_range{CODE_POS_STR + "索引超出范围"};
			}

			return _context.Span()[index];
		}

		uint8_t const &operator[](int index) const
		{
			if (index < 0 || index >= _context.Span().Size())
			{
				throw std::out_of_range{CODE_POS_STR + "索引超出范围"};
			}

			return _context.Span()[index];
		}

		///
		/// @brief IP 地址的类型。
		///
		/// @return
		///
		IPAddressType Type() const
		{
			return _context.IPAddressType();
		}

		///
		/// @brief 转化为字符串。
		///
		/// @return
		///
		std::string ToString() const override
		{
			std::string ret;

			base::ToHexStringOptions option;
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

		///
		/// @brief 获取引用着本对象缓冲区的 Span.
		///
		/// @return
		///
		base::Span Span()
		{
			return _context.Span();
		}

		///
		/// @brief 获取引用着本对象缓冲区的 ReadOnlySpan.
		///
		/// @return
		///
		base::ReadOnlySpan Span() const
		{
			return _context.Span();
		}
	};

} // namespace base
