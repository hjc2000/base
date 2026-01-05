#pragma once
#include "base/stream/Stream.h"
#include <stdexcept>
#include <string>

namespace base
{
	///
	/// @brief 可以序列化到流中，也可以从流中反序列化。
	///
	///
	class IStreamSerializable
	{
	public:
		///
		/// @brief 将对象序列化写入流中。
		///
		/// @param stream
		///
		virtual void SerializeIntoStream(base::Stream &stream) const = 0;

		///
		/// @brief 从流中反序列化得到对象。
		///
		/// @note 对象要先无参默认构造，然后再调用此方法进行反序列化，重新初始化对象的各个字段。
		///
		/// @param stream
		///
		virtual void DeserializeFromStream(base::Stream &stream) = 0;
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

	///
	/// @brief 从流中反序列化得到对象发生异常。
	///
	/// @note 发生此异常后，反序列化到一半的对象很可能处于无效状态，需要丢弃。
	///
	class StreamDeserializeException :
		public std::runtime_error
	{
	public:
		StreamDeserializeException()
			: std::runtime_error(__func__)
		{
		}

		StreamDeserializeException(std::string const &message)
			: std::runtime_error(std::string{__func__} + ": " + message)
		{
		}
	};

} // namespace base
