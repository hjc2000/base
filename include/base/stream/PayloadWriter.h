#pragma once
#include "base/bit/AutoBitConverter.h"
#include "base/stream/Span.h"
#include <cstdint>

namespace base
{
	class PayloadWriter
	{
	private:
		base::Span _span{};
		int64_t _position = 0;

	public:
		PayloadWriter(base::Span const &span)
			: _span{span}
		{
		}

		int64_t Position() const
		{
			return _position;
		}

		void ResetPosition()
		{
			_position = 0;
		}

		///
		/// @brief 写入载荷。
		///
		/// @param span
		///
		void WritePayload(base::ReadOnlySpan const &span)
		{
			base::Range range{
				_position,
				_position + span.Size(),
			};

			base::Span span_to_write = _span[range];
			span_to_write.CopyFrom(span);

			_position += span_to_write.Size();
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
				_position,
				_position + static_cast<int64_t>(sizeof(ValueType)),
			};

			base::Span span_to_write = _span[range];

			base::AutoBitConverter conveter{remote_endian};
			conveter.GetBytes(value, span_to_write);

			_position += span_to_write.Size();
		}
	};

} // namespace base
