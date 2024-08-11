#include "Json.h"

std::string base::IJsonSerializable::ToString()
{
    return ToJson().dump(4);
}
