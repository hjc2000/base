#pragma once
#include "base/bit/AutoBitConverter.h"
#include "base/container/Range.h"
#include "base/net/ethernet/LengthOrTypeEnum.h"
#include "base/net/Mac.h"
#include "base/stream/PayloadReader.h"
#include "base/stream/ReadOnlySpan.h"
#include "base/stream/Span.h"
#include "base/string/define.h"
#include "base/string/Json.h"
#include <cstdint>
#include <stdexcept>

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
		base::PayloadReader _payload_reader;

		///
		/// @brief 载荷数据。
		///
		/// @note 字节数的取值范围：[46, 1500].
		///
		/// @note 巨型帧可以超过 1500 字节。但是需要网络设备支持，否则会导致无法传输。
		///
		/// @return
		///
		base::ReadOnlySpan Payload() const
		{
			if (HasVlanTag())
			{
				return _span[base::Range{18, _span.Size()}];
			}

			return _span[base::Range{14, _span.Size()}];
		}

	public:
		///
		/// @brief 引用 span 指向的内存段，在此位置解析以太网帧。
		///
		/// @param span 储存着以太网帧的内存段。
		/// 	@note 传进来的内存段不要包括以太网帧尾部的 4 个字节的校验和。
		///
		EthernetFrameReader(base::ReadOnlySpan const &span)
			: _span{span},
			  _payload_reader{Payload()}
		{
			if (span.Size() < 60)
			{
				throw std::invalid_argument{CODE_POS_STR + "内存段过小，以太网帧至少有 60 字节。（不包括校验和）"};
			}
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
		/// @brief 是否具有 802.1Q标签。
		///
		/// @return
		///
		bool HasVlanTag() const
		{
			uint16_t u16_type_or_length = base::big_endian_remote_converter.FromBytes<uint16_t>(_span[base::Range{12, 14}]);
			base::ethernet::LengthOrTypeEnum type_or_length = static_cast<base::ethernet::LengthOrTypeEnum>(u16_type_or_length);
			return type_or_length == base::ethernet::LengthOrTypeEnum::VlanTag;
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
				uint16_t type_or_length = base::big_endian_remote_converter.FromBytes<uint16_t>(_span[base::Range{16, 18}]);
				return static_cast<base::ethernet::LengthOrTypeEnum>(type_or_length);
			}

			uint16_t type_or_length = base::big_endian_remote_converter.FromBytes<uint16_t>(_span[base::Range{12, 14}]);
			return static_cast<base::ethernet::LengthOrTypeEnum>(type_or_length);
		}

		///
		/// @brief 读取载荷数据。
		///
		/// @param span
		///
		void ReadPayload(base::Span const &span)
		{
			_payload_reader.ReadPayload(span);
		}

		///
		/// @brief 读取载荷数据。
		///
		/// @param remote_endian
		///
		/// @return
		///
		template <typename ReturnType>
		ReturnType ReadPayload(std::endian remote_endian)
		{
			return _payload_reader.ReadPayload<ReturnType>(remote_endian);
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
