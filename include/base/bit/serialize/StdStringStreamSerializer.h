#pragma once
#include "base/bit/serialize/IStreamSerializable.h"
#include <string>

namespace base
{
	class StdStringStreamSerializer :
		public base::IStreamSerializable
	{
	private:
		std::string *_string{};

	public:
		StdStringStreamSerializer() = default;

		StdStringStreamSerializer(std::string &string)
		{
			_string = &string;
		}

		///
		/// @brief 将对象序列化写入流中。
		///
		/// @param stream
		///
		virtual void SerializeIntoStream(base::Stream &stream) const override;

		///
		/// @brief 从流中反序列化得到对象。
		///
		/// @note 对象要先无参默认构造，然后再调用此方法进行反序列化，重新初始化对象的各个字段。
		///
		/// @param stream
		///
		virtual void DeserializeFromStream(base::Stream &stream) override;
	};

} // namespace base
