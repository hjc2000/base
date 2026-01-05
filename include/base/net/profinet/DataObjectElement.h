#pragma once
#include "base/stream/Span.h"

namespace base
{
	namespace profinet
	{
		class DataObjectElement
		{
		private:
			base::Span _span;

		public:
			DataObjectElement() = default;
			DataObjectElement(base::Span const &span);

			base::Span const &Span() const;

			/// @brief 数据所在的内存段。
			/// @note 数据有好几种类型，并且可能是好几个数据连续排列在一起，这里只是提供这段内存，
			/// 不负责取出每一个数据。
			/// @return
			base::Span Data() const;
			void SetData(base::Span const &value);

			uint8_t Iops() const;
			void SetIops(uint8_t value);
		};
	} // namespace profinet
} // namespace base
