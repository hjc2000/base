#pragma once
#include "base/bit/AutoBitConverter.h"
#include "base/net/ethernet/LengthOrTypeEnum.h"
#include "base/net/Mac.h"
#include "base/stream/ReadOnlySpan.h"
#include "base/string/Json.h"

namespace base::ethernet
{
	///
	/// @brief 以太网帧读者。
	///
	class EthernetFrameReader :
		public base::IJsonSerializable
	{
	private:
		base::ReadOnlySpan _span;

	public:
		///
		/// @brief 引用 span 指向的内存段，在此位置解析以太网帧。
		///
		/// @param span
		///
		EthernetFrameReader(base::ReadOnlySpan const &span)
		{
			_span = span;
		}

		///
		/// @brief 目的 MAC 地址。
		///
		/// @return
		///
		base::Mac DestinationMac() const
		{
			base::Mac ret{
				std::endian::big,
				_span[base::Range{0, 6}],
			};

			return ret;
		}

		///
		/// @brief 源 MAC 地址。
		///
		/// @return
		///
		base::Mac SourceMac() const
		{
			base::Mac ret{
				std::endian::big,
				_span[base::Range{6, 12}],
			};

			return ret;
		}

		///
		/// @brief 802.1Q标签。大小：4 字节。
		///
		/// @return
		///
		base::ReadOnlySpan VlanTag() const
		{
			if (HasVlanTag())
			{
				return base::ReadOnlySpan{_span[base::Range{12, 16}]};
			}

			throw std::runtime_error{"本以太网帧不具备 VlanTag."};
		}

		///
		/// @brief 是否具有 802.1Q标签。
		///
		/// @return
		///
		bool HasVlanTag() const
		{
			uint16_t foo = base::big_endian_remote_converter.FromBytes<uint16_t>(_span[base::Range{12, 14}]);
			base::ethernet::LengthOrTypeEnum type_or_length = static_cast<base::ethernet::LengthOrTypeEnum>(foo);
			return type_or_length == base::ethernet::LengthOrTypeEnum::VlanTag;
		}

		///
		/// @brief 类型或长度。
		///
		/// @note 整型值小于等于 1500，则表示长度，大于 1500 则表示帧类型。当含义是帧类型时，
		/// 这个值是用来给上层的处理程序看的，让上层的处理程序决定将以太网帧送往哪个协议处理程序。
		///
		/// @note 1500 的 16 进制：0x05dc.
		///
		/// @note 下面这几个值都大于 1500：
		/// 	@li 0x0800：表示 IPv4 数据包。
		/// 	@li 0x0806：表示 ARP 请求。
		/// 	@li 0x86DD：表示 IPv6 数据包。
		///
		/// @return
		///
		base::ethernet::LengthOrTypeEnum TypeOrLength() const
		{
			if (HasVlanTag())
			{
				uint16_t type_or_length = base::big_endian_remote_converter.FromBytes<uint16_t>(_span.Slice(base::Range{16, 18}));
				return static_cast<base::ethernet::LengthOrTypeEnum>(type_or_length);
			}
			else
			{
				uint16_t type_or_length = base::big_endian_remote_converter.FromBytes<uint16_t>(_span.Slice(base::Range{12, 14}));
				return static_cast<base::ethernet::LengthOrTypeEnum>(type_or_length);
			}
		}

		///
		/// @brief 载荷数据。
		///
		/// @note 字节数的取值范围：[46, 1500].
		///
		/// @note 巨型帧可以超过 1500 字节。但是需要网络设备支持，否则会导致无法传输。
		///
		/// @note 如果不满 46 字节，需要后面填充 0，使其达到 46 字节。
		///
		/// @note 因为可能会有填充，所以需要靠 TypeOrLength 属性来识别出有效字节数。
		///
		/// @note 这里返回的 ReadOnlySpan 是构造函数中交给本对象的 ReadOnlySpan
		/// 去除以太网头部后的全部剩余空间，并不是实际的有效载荷。本类是以太网帧类，
		/// 无法识别出有效载荷的长度，这种工作只能交给上层。
		///
		/// @return
		///
		base::ReadOnlySpan Payload() const
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

		///
		/// @brief 序列化为 json
		///
		/// @return
		///
		base::Json ToJson() const override
		{
			base::Json root{
				{"目的 MAC 地址", DestinationMac().ToString()},
				{"源 MAC 地址", SourceMac().ToString()},
				{"TypeOrLength", base::to_string(TypeOrLength())},
				{"是否具有 VlangTag", HasVlanTag()},
			};

			return root;
		}
	};

} // namespace base::ethernet
