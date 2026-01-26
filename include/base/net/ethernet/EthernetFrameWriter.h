#pragma once
#include "base/bit/AutoBitConverter.h"
#include "base/net/ethernet/LengthOrTypeEnum.h"
#include "base/net/Mac.h"
#include "base/stream/ReadOnlySpan.h"
#include <cstdint>

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
		int _valid_frame_size = 0;
		bool _has_vlan_tag = false;

	public:
		///
		/// @brief 构造函数。
		///
		/// @param span 引用的内存。
		/// 	@note 传进来的内存段不需要为以太网帧尾部的 4 个字节的校验和保留空间，
		/// 	本来没能力计算和写入校验和，会把尾部的所有空间都当成可以写入载荷的区域。
		///
		EthernetFrameWriter(base::Span const &span)
		{
			_span = span;
		}

		///
		/// @brief 写入目的 MAC 地址。
		///
		/// @param value
		///
		void WriteDestinationMac(base::Mac const &value)
		{
			base::Span span = _span.Slice(base::Range{0, 6});
			span.CopyFrom(value.Span());
			span.Reverse();
		}

		///
		/// @brief 写入源 MAC 地址。
		///
		/// @param value
		///
		void WriteSourceMac(base::Mac const &value)
		{
			base::Span span = _span.Slice(base::Range{6, 12});
			span.CopyFrom(value.Span());
			span.Reverse();
		}

		/* #region VLAN TAG */

		///
		/// @brief 写入 802.1Q标签。
		///
		/// @note 写入后会自动将是否具有 VLAN TAG 的标识置为 true.
		///
		/// @param value
		///
		void WriteVlanTag(base::ReadOnlySpan const &value)
		{
			base::Span span = _span.Slice(base::Range{12, 16});
			span.CopyFrom(value);
			_has_vlan_tag = true;
		}

		///
		/// @brief 将是否具有 VLAN TAG 的标识置为 false.
		///
		void ClearVlanTag()
		{
			_has_vlan_tag = false;
		}

		/* #endregion */

		///
		/// @brief 写入类型或长度。
		///
		/// @param value
		///
		void WriteTypeOrLength(base::ethernet::LengthOrTypeEnum value)
		{
			if (_has_vlan_tag)
			{
				base::big_endian_remote_converter.GetBytes(static_cast<uint16_t>(value),
														   _span.Slice(base::Range{16, 18}));
			}
			else
			{
				base::big_endian_remote_converter.GetBytes(static_cast<uint16_t>(value),
														   _span.Slice(base::Range{12, 14}));
			}
		}

		/* #region 载荷 */

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
		/// @note 这里返回的 Span 是构造函数中交给本对象的 Span 被填充以太网头部后的全部
		/// 剩余空间，并不是实际的有效载荷。本类是以太网帧类，无法识别出有效载荷的长度，这种
		/// 工作只能交给上层。
		///
		/// @return
		///
		base::Span Payload() const
		{
			if (_has_vlan_tag)
			{
				return _span.Slice(base::Range{18, _span.Size()});
			}
			else
			{
				return _span.Slice(base::Range{14, _span.Size()});
			}
		}

		///
		/// @brief 设置有效载荷的大小。
		///
		/// @param value 有效载荷的大小。
		/// 	@note 如果小于 46，会在有效载荷后面填充值为 0 的字节，使载荷达到 46 字节。
		///
		void SetValidPayloadSize(int32_t value)
		{
			if (_has_vlan_tag)
			{
				if (value < 46)
				{
					// 载荷不足 46 字节，需要填充值为 0 的字节，从而达到 46 字节。
					// 所以有效载荷的最后一个字节后到第 46 字节的这段内存要清零。
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
					// 载荷不足 46 字节，需要填充值为 0 的字节，从而达到 46 字节。
					// 所以有效载荷的最后一个字节后到第 46 字节的这段内存要清零。
					_span.Slice(base::Range{14 + value, 14 + 46}).FillWithZero();
					_valid_frame_size = 14 + 46;
				}
				else
				{
					_valid_frame_size = 14 + value;
				}
			}
		}

		/* #endregion */

		///
		/// @brief 从整个 span 中切割出有效的可以发送到以太网中的 span.
		///
		/// @note 切割范围：[0, FrameSize].
		///
		/// @return
		///
		base::ReadOnlySpan SpanForSending() const
		{
			return _span.Slice(base::Range{0, FrameSize()});
		}

		///
		/// @brief 帧大小。有 VLAN TAG 时至少是 64 字节，无 VLAN TAG 时至少是 60 字节。
		/// 载荷的填充字节也被计算在内。
		///
		/// @note 本属性受 SetValidPayloadSize 方法的影响。
		///
		/// @return
		///
		int32_t FrameSize() const
		{
			if (_has_vlan_tag)
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
	};

} // namespace base::ethernet
