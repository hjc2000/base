#pragma once
#include "base/bit/AutoBitConverter.h"
#include "base/container/Range.h"
#include "base/net/ethernet/LengthOrTypeEnum.h"
#include "base/net/Mac.h"
#include "base/stream/PayloadWriter.h"
#include "base/stream/ReadOnlySpan.h"
#include "base/stream/Span.h"
#include "base/string/define.h"
#include <algorithm>
#include <bit>
#include <cstdint>
#include <stdexcept>

namespace base::ethernet
{
	///
	/// @brief 以太网帧作者。
	///
	/// @note 这里的属性最好是从上到下按顺序设置。特别是从 VlanTag 开始，因为 VlanTag 有没有设置
	/// 将会影响到后续属性放置到内存中的位置。也不要在添加或删除了 VlanTag 属性后继续尝试读取 VlanTag
	/// 后面的属性，因为偏移量变了，会读取到错误的结果。
	///
	class EthernetFrameWriter
	{
	private:
		base::Span _span;
		bool _has_vlan_tag = false;
		base::PayloadWriter _payload_writer;
		int32_t _payload_writting_position = 0;

		base::Span Payload() const
		{
			if (_has_vlan_tag)
			{
				return _span[base::Range{18, _span.Size()}];
			}

			return _span[base::Range{14, _span.Size()}];
		}

		///
		/// @brief 整个以太网帧的大小，不包括校验和。
		///
		/// @note 整个以太网帧的最小长度限制是 60 字节（不包括校验和），不管有没有
		/// VLAN TAG 都是 60 字节的限制。
		///
		/// @return
		///
		int32_t FrameSize() const
		{
			if (_has_vlan_tag)
			{
				return std::max<int32_t>(_payload_writting_position + 18, 60);
			}

			return std::max<int32_t>(_payload_writting_position + 14, 60);
		}

	public:
		///
		/// @brief 构造函数。
		///
		/// @param span 引用的内存。
		/// 	@note 传进来的内存段不需要为以太网帧尾部的 4 个字节的校验和保留空间，
		/// 	本来没能力计算和写入校验和，会把尾部的所有空间都当成可以写入载荷的区域。
		///
		EthernetFrameWriter(base::Span const &span)
			: _span{span},
			  _payload_writer{_span[base::Range{14, _span.Size()}]}
		{
			if (span.Size() < 60)
			{
				throw std::invalid_argument{CODE_POS_STR + "内存段过小，以太网帧至少有 60 字节。（不包括校验和）"};
			}
		}

		///
		/// @brief 写入目的 MAC 地址。
		///
		/// @param value
		///
		void WriteDestinationMac(base::Mac const &value) const
		{
			base::Span span = _span[base::Range{0, 6}];
			span.CopyFrom(value.Span());
			span.Reverse();
		}

		///
		/// @brief 写入源 MAC 地址。
		///
		/// @param value
		///
		void WriteSourceMac(base::Mac const &value) const
		{
			base::Span span = _span[base::Range{6, 12}];
			span.CopyFrom(value.Span());
			span.Reverse();
		}

		///
		/// @brief 写入 802.1Q标签。
		///
		/// @note 写入后会自动将是否具有 VLAN TAG 的标识置为 true.
		///
		/// @param value
		///
		void WriteVlanTag(base::ReadOnlySpan const &value)
		{
			base::Span span = _span[base::Range{12, 16}];
			span.CopyFrom(value);
			_has_vlan_tag = true;
			_payload_writer = base::PayloadWriter{_span[base::Range{18, _span.Size()}]};
		}

		///
		/// @brief 写入类型或长度。
		///
		/// @param value
		///
		void WriteTypeOrLength(base::ethernet::LengthOrTypeEnum value) const
		{
			if (_has_vlan_tag)
			{
				base::big_endian_remote_converter.GetBytes(static_cast<uint16_t>(value),
														   _span[base::Range{16, 18}]);
			}
			else
			{
				base::big_endian_remote_converter.GetBytes(static_cast<uint16_t>(value),
														   _span[base::Range{12, 14}]);
			}
		}

		///
		/// @brief 写入载荷。
		///
		/// @param span
		///
		void WritePayload(base::ReadOnlySpan const &span)
		{
			base::Range range{
				_payload_writting_position,
				_payload_writting_position + span.Size(),
			};

			base::Span span_to_write = Payload()[range];
			span_to_write.CopyFrom(span);

			_payload_writting_position += span_to_write.Size();
		}

		///
		/// @brief 写入载荷。
		///
		/// @param value
		/// @param remote_endian
		///
		template <typename ValueType>
		void WritePayload(ValueType value, std::endian remote_endian)
		{
			base::Range range{
				_payload_writting_position,
				_payload_writting_position + static_cast<int64_t>(sizeof(ValueType)),
			};

			base::Span span_to_write = Payload()[range];

			base::AutoBitConverter conveter{remote_endian};
			conveter.GetBytes(value, span_to_write);

			_payload_writting_position += span_to_write.Size();
		}

		///
		/// @brief 从整个 span 中切割出有效的可以发送到以太网中的 span.
		///
		/// @note 不包括校验和。
		///
		/// @return
		///
		base::ReadOnlySpan SpanForSending() const
		{
			return _span[base::Range{0, FrameSize()}];
		}
	};

} // namespace base::ethernet
