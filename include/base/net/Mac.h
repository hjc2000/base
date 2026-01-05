#pragma once
#include "base/bit/AutoBitConverter.h"
#include "base/container/Array.h"
#include "base/stream/ReadOnlySpan.h"
#include "base/stream/Span.h"
#include "base/string/define.h"
#include "base/string/ICanToString.h"
#include "base/string/ToHexString.h"
#include <bit>
#include <cstdint>

namespace base
{
	///
	/// @brief MAC 地址
	/// @note 按照小端序存放。即书写 MAC 字符串时，最右边的，即最低字节，存放在本对象的低索引处；
	/// 字符串最左边的，即最高字节，存放在本对象的最高索引处。
	///
	class Mac :
		public base::ICanToString
	{
	private:
		base::Array<uint8_t, 6> _mac_buffer{};

	public:
		/* #region 构造函数 */

		///
		/// @brief 无参构造函数。构造出来的 MAC 地址是全 0.
		///
		Mac() = default;

		///
		/// @brief 构造函数。
		/// @param mac_buffer MAC 地址数组。该缓冲区内的 MAC 地址必须是按小端序存放。
		///
		Mac(base::Array<uint8_t, 6> const &mac_buffer)
		{
			_mac_buffer = mac_buffer;
		}

		///
		/// @brief 构造函数
		/// @param endian 你传入的 MAC 地址数组是大端序的还是小端序的
		/// @param mac_buffer MAC 地址数组。可以是大端序也可以是小端序，只要 endian 参数正确指明就行。
		///
		Mac(std::endian endian, base::Array<uint8_t, 6> const &mac_buffer)
		{
			_mac_buffer = mac_buffer;
			if (std::endian::little != endian)
			{
				// 保存到本数组中的 MAC 地址要是小端序，如果传进来的是大端序，需要翻转。
				_mac_buffer.Reverse();
			}
		}

		///
		/// @brief 从 ReadOnlySpan 中构造 MAC.
		///
		/// @param endian span 中的 MAC 地址的字节序。
		/// @param span 储存着 MAC 地址的内存。会将这段内存的数据拷贝过来。
		///
		Mac(std::endian endian, base::ReadOnlySpan const &span)
		{
			if (span.Size() != 6)
			{
				throw std::invalid_argument{CODE_POS_STR + "传进来的 span 的大小必须为 6 字节。"};
			}

			base::Span buffer{_mac_buffer.Buffer(), _mac_buffer.Count()};
			buffer.CopyFrom(span);

			if (std::endian::little != endian)
			{
				// 保存到本数组中的 MAC 地址要是小端序，如果传进来的是大端序，需要翻转。
				_mac_buffer.Reverse();
			}
		}

		/* #endregion */

		///
		/// @brief 获取本对象内部的用来储存 MAC 地址的数组。
		/// @return
		///
		base::Array<uint8_t, 6> const &InternalArray() const
		{
			return _mac_buffer;
		}

		///
		/// @brief 获取本对象内部的用来储存 MAC 地址的数组。
		///
		/// @return
		///
		base::Array<uint8_t, 6> &InternalArray()
		{
			return _mac_buffer;
		}

		///
		/// @brief 显示将本对象强制转换为 base::Array<uint8_t, 6>.
		/// 原理是将 MAC 地址拷贝到 base::Array<uint8_t, 6> 中。
		///
		explicit operator base::Array<uint8_t, 6>() const
		{
			return _mac_buffer;
		}

		///
		/// @brief 将 MAC 地址转换为无符号整型。
		///
		explicit operator uint64_t() const
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

		///
		/// @brief 转化为字符串
		///
		/// @return
		///
		std::string ToString() const override
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

		///
		/// @brief 获取引用着本对象内部缓冲区的 ReadOnlySpan.
		///
		/// @return
		///
		base::ReadOnlySpan Span() const
		{
			return base::ReadOnlySpan{_mac_buffer.Buffer(), _mac_buffer.Count()};
		}

		///
		/// @brief 获取引用着本对象内部缓冲区的 Span.
		///
		/// @return
		///
		base::Span Span()
		{
			return base::Span{_mac_buffer.Buffer(), _mac_buffer.Count()};
		}

		///
		/// @brief 访问 MAC 地址中指定索引的值。
		///
		/// @param index
		///
		/// @return
		///
		uint8_t &operator[](int index)
		{
			return _mac_buffer[index];
		}

		///
		/// @brief 访问 MAC 地址中指定索引的值。
		///
		/// @param index
		///
		/// @return
		///
		uint8_t const &operator[](int index) const
		{
			return _mac_buffer[index];
		}

		///
		/// @brief 获取 MAC 地址中的 OUI.
		/// @return
		///
		base::Array<uint8_t, 3> Oui() const
		{
			return base::Array<uint8_t, 3>{_mac_buffer.Span().Slice(base::Range{3, 6})};
		}

		///
		/// @brief 设置 OUI.
		/// @param value
		///
		void SetOui(base::Array<uint8_t, 3> const &value)
		{
			_mac_buffer.Span().Slice(base::Range{3, 6}).CopyFrom(value.Span());
		}

		///
		/// @brief 本地址是否是多播地址。
		///
		/// @note 最高字节的最低位为 1 则是多播地址，为 0 则是单播地址。
		///
		/// @return 是多播地址返回 true，不是则返回 false.
		///
		bool IsMulticastAddress() const
		{
			// 最高字节的最低位为 1 则是多播地址，为 0 则是单播地址。
			return _mac_buffer[5] & 0x01;
		}
	};

} // namespace base
