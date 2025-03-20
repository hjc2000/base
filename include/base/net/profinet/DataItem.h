#pragma once
#include "base/net/profinet/DataObjectElement.h"
#include "base/stream/Span.h"

namespace base
{
	namespace profinet
	{
		class DataItem
		{
		private:
			base::Span _span;

		public:
			DataItem() = default;
			DataItem(base::Span const &span);

			base::Span const &Span() const;

			uint8_t Iocs() const;
			void SetIocs(uint8_t value);

			base::profinet::DataObjectElement DataObjectElement() const;
			void SetDataObjectElement(base::profinet::DataObjectElement const &value);
		};
	} // namespace profinet
} // namespace base
