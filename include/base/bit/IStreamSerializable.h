#pragma once
#include "base/stream/Stream.h"
#include <stdexcept>

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

	///
	/// @brief 序列化到流中失败。
	///
	///
	class StreamSerializeException :
		public std::runtime_error
	{
	public:
		StreamSerializeException()
			: std::runtime_error(__func__)
		{
		}

		StreamSerializeException(std::string const &message)
			: std::runtime_error(std::string{__func__} + ": " + message)
		{
		}
	};

} // namespace base
