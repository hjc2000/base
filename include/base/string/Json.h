#pragma once
#include <base/string/ICanToString.h>
#include <nlohmann/json.hpp>
#include <string>

namespace base
{
	using Json = nlohmann::json;
	using JsonTypeException = Json::type_error;

	class IJsonSerializable
		: public ICanToString
	{
	public:
		virtual ~IJsonSerializable() = default;

		virtual Json ToJson() = 0;

		std::string ToString() override;
	};
}
