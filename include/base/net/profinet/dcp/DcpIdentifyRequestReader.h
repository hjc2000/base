#pragma once
#include "base/net/profinet/dcp/DcpServiceIdEnum.h"
#include "base/net/profinet/dcp/DcpServiceTypeEnum.h"
#include "base/net/profinet/fid-pdu/FidApduReader.h"
#include "base/string/define.h"
#include "base/string/Json.h"
#include "base/string/ToHexString.h"
#include "DcpHeaderReader.h"
#include "DcpTlvReader.h"

namespace base::profinet
{
	class DcpHeaderReader;
	class DcpTlvReader;

	///
	/// @brief DCP Identify 请求帧读者。
	///
	///
	class DcpIdentifyRequestReader :
		public base::IJsonSerializable
	{
	private:
		base::profinet::FidApduReader _fid_pdu_reader;
		base::ReadOnlySpan _this_span;

		///
		/// @brief 这里使用了动态内存分配，会导致速度较慢。但是 DCP 对实时性要求不高，
		/// 而且 DCP 并不会经常进行，只在配置的时候进行一次就结束了，所以用动态内存分配
		/// 也没什么大问题。
		///
		std::shared_ptr<base::profinet::DcpHeaderReader> _header_reader;
		std::shared_ptr<base::profinet::DcpTlvReader> _tlv_reader;

	public:
		///
		/// @brief 构造函数。
		///
		/// @param span 整个以太网帧的内存片段。
		///
		DcpIdentifyRequestReader(base::ReadOnlySpan const &span)
			: _fid_pdu_reader(span)
		{
			_this_span = _fid_pdu_reader.Payload();
			if (_this_span.Size() < base::profinet::DcpHeaderReader::HeaderSize())
			{
				// DCP 头部要 10 字节，这里连 10 字节都没有。
				throw std::invalid_argument{CODE_POS_STR + "传入的帧中不含有合法的 DCP 头部。"};
			}

			_header_reader = std::shared_ptr<base::profinet::DcpHeaderReader>{new base::profinet::DcpHeaderReader{
				_this_span,
			}};

			{
				base::ReadOnlySpan tlv_span = _this_span.Slice(base::Range{
					base::profinet::DcpHeaderReader::HeaderSize(),
					_this_span.Size(),
				});

				_tlv_reader = std::shared_ptr<base::profinet::DcpTlvReader>{new base::profinet::DcpTlvReader{
					tlv_span,
				}};
			}
		}

		base::profinet::DcpServiceIdEnum ServiceId() const
		{
			return _header_reader->ServiceId();
		}

		base::profinet::DcpServiceTypeEnum ServiceType() const
		{
			return _header_reader->ServiceType();
		}

		uint32_t Xid() const
		{
			return _header_reader->Xid();
		}

		/// @brief 响应延迟。
		/// @return
		uint16_t ResponseDelay() const;

		/// @brief Blocks 的有效数据的长度，包括填充字节。
		/// @note 填充是为了 2 字节对齐，每一个 Block 都必须 2 字节对齐，如果没有对齐，
		/// 尾部需要填充 1 字节。
		/// @return
		uint16_t DataLength() const;

		///
		/// @brief 是否具有站点名称块。
		///
		/// @return true 有站点名称块。
		/// @return false 无站点名称块。
		///
		bool HasNameOfStationBlock() const;

		///
		/// @brief 站点名称。
		///
		/// @note 只有 HasNameOfStationBlock 属性为 true 时本属性才有效。
		/// HasNameOfStationBlock 为 false 时访问本属性会抛出异常。
		///
		/// @return std::string
		///
		std::string NameOfStation() const;

		///
		/// @brief 序列化为 json
		///
		/// @return
		///
		virtual base::Json ToJson() const override
		{
			base::Json root{
				{"ServiceId", base::to_string(ServiceId())},
				{"ServiceType", base::to_string(ServiceType())},
				{"Xid", base::ToHexString(Xid())},
				{"ResponseDelay", base::ToHexString(ResponseDelay())},
				{"DataLength", DataLength()},
			};

			base::Json blocks;

			if (HasNameOfStationBlock())
			{
				blocks["NameOfStation"] = NameOfStation();
			}

			root["Blocks"] = blocks;
			return root;
		}
	};

#if HAS_THREAD
	namespace test
	{
		void TestDcpIdentifyRequestReader();
	} // namespace test
#endif // HAS_THREAD

} // namespace base::profinet
