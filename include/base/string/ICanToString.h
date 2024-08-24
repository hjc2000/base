#pragma once
#include <string>

namespace base
{
    class ICanToString
    {
    public:
        virtual std::string ToString() = 0;
    };
} // namespace base
