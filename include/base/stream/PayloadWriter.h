#pragma once
#include "base/stream/Span.h"

namespace base
{
	class PayloadWriter
	{
	private:
		base::Span _span{};

	public:
		PayloadWriter(base::Span const &span)
			: _span{span}
		{
		}
	};

} // namespace base
