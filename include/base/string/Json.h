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
        /// @brief 序列化为 json
        /// @return
        virtual Json ToJson() const = 0;

        /// @brief 利用序列化出的 Json 对象，将本对象转化为 json 字符串。
        /// @return
        std::string ToString() const override;
    };
} // namespace base
