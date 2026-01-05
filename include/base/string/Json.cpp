#include "Json.h"

std::string base::IJsonSerializable::ToString() const
{
	return ToJson().dump(4);
}

void base::IJsonDeserializable::FromJsonString(std::string const &json_string)
{
	FromJson(Json::parse(json_string));
}
