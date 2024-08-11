#pragma once

namespace base
{
    class IDisposable
    {
    public:
        virtual ~IDisposable() = default;
        virtual void Dispose() = 0;
    };
} // namespace base
