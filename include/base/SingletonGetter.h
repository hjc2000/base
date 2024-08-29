#pragma once
#include <base/Guard.h>
#include <base/LockGuard.h>
#include <memory>

namespace base
{
    template <typename SingletonType>
    class SingletonGetter :
        public base::ILock
    {
    private:
        inline static std::unique_ptr<SingletonType> _p;

    protected:
        virtual std::unique_ptr<SingletonType> Create() = 0;

    public:
        SingletonType &Instance()
        {
            if (_p != nullptr)
            {
                return *_p;
            }

            base::LockGuard l{*this};
            if (_p != nullptr)
            {
                return *_p;
            }

            _p = Create();
            return *_p;
        }
    };
} // namespace base
