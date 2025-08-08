#pragma once
#include "base/stream/Stream.h"

namespace base
{
	class IStreamSerializable
	{
	public:
		///
		/// @brief 将对象序列化写入流中。
		///
		/// @param stream
		///
		virtual void SerializeIntoStream(base::Stream &stream) = 0;
	};

} // namespace base
