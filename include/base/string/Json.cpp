#include "Json.h"

std::string base::IJsonSerializable::ToString() const
{
	return ToJson().dump(4);
}
