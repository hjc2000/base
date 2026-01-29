#pragma once
#include "base/bit/AutoBitConverter.h"
#include "base/stream/ReadOnlySpan.h"
#include "base/stream/Span.h"
#include <cstdint>

namespace base
{
	class PayloadReader
	{
	private:
		base::ReadOnlySpan _span{};
		int64_t _position = 0;

	public:
		PayloadReader(base::ReadOnlySpan const &span)
			: _span{span}
		{
		}

		///
		/// @brief 读取载荷数据。
		///
		/// @param span
		///
		void ReadPayload(base::Span const &span)
		{
			base::Range range_to_read{
				_position,
				_position + span.Size(),
			};

			base::ReadOnlySpan span_to_read = _span[range_to_read];
			span.CopyFrom(span_to_read);
			_position += span_to_read.Size();
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
			base::Range range_to_read{
				_position,
				_position + static_cast<int64_t>(sizeof(ReturnType)),
			};

			base::ReadOnlySpan span_to_read = _span[range_to_read];

			base::AutoBitConverter conveter{remote_endian};
			ReturnType ret = conveter.FromBytes<ReturnType>(span_to_read);

			_position += span_to_read.Size();
			return ret;
		}
	};

} // namespace base
