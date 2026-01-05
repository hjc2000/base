#pragma once
#include "base/string/ICanToString.h"
#include "nlohmann/json.hpp"
#include <string>

namespace base
{
	using Json = nlohmann::json;
	using JsonTypeException = Json::type_error;

	///
	/// @brief 继承此接口表示能将对象序列化为 json
	///
	///
	class IJsonSerializable :
		public ICanToString
	{
	public:
		///
		/// @brief 序列化为 json
		///
		/// @return
		///
		virtual base::Json ToJson() const = 0;

		///
		/// @brief 利用序列化出的 Json 对象，将本对象转化为 json 字符串。
		///
		/// @return
		///
		std::string ToString() const override;

		///
		/// @brief 强制转换为 Json 对象。
		///
		/// @return
		///
		operator base::Json() const
		{
			return ToJson();
		}
	};

	///
	/// @brief 继承此接口表示能从 json 反序列化。
	///
	///
	class IJsonDeserializable
	{
	public:
		///
		/// @brief 从 json 对象中反序列化。
		///
		/// @param json
		///
		virtual void FromJson(Json const &json) = 0;

		///
		/// @brief 从 json 字符串中反序列化。
		///
		/// @param json_string
		///
		void FromJsonString(std::string const &json_string);
	};

} // namespace base
