#pragma once
#include <base/string/ICanToString.h>
#include <nlohmann/json.hpp>
#include <string>

namespace base
{
    using Json = nlohmann::json;
    using JsonTypeException = Json::type_error;

    /// @brief 继承此接口表示能将对象序列化为 json
    class IJsonSerializable :
        public ICanToString
    {
    public:
        virtual Json ToJson() const = 0;

        std::string ToString() const override;
    };
} // namespace base
