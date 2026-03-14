#pragma once
#include "base/stream/Stream.h"

namespace base::string::encoding
{
	class Utf16LeWriter
	{
	private:
		base::Stream &_stream;

	public:
		Utf16LeWriter(base::Stream &stream)
			: _stream{stream}
		{
		}
	};

} // namespace base::string::encoding
