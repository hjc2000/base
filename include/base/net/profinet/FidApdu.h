#pragma once
#include <base/bit/AutoBitConverter.h>
#include <base/net/profinet/enum/FrameIdEnum.h>
#include <base/stream/Span.h>

namespace base
{
	namespace profinet
	{
		/// @brief 带有帧 ID 的应用层协议数据单元。
		class FidApdu
		{
		private:
			base::Span _span;
			base::AutoBitConverter _converter{std::endian::big};
			int _valid_frame_size = 0;

		public:
			FidApdu() = default;
			FidApdu(base::Span const &span);

			base::Span const &Span() const;

			/// @brief 装有全部有效数据的 span.
			/// @return
			base::Span ValidDataSpan() const;

			base::profinet::FrameIdEnum FrameId() const;
			void SetFrameId(base::profinet::FrameIdEnum value);

			/// @brief 载荷。
			/// @return
			base::Span Payload() const;

			/// @brief 设置载荷。
			/// @param value
			void SetPayload(base::ReadOnlySpan const &value);
		};
	} // namespace profinet
} // namespace base
