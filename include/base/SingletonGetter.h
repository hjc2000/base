#pragma once
#include <base/Guard.h>
#include <base/LockGuard.h>
#include <memory>

namespace base
{
    template <typename SingletonType>
    class SingletonGetter :
        protected base::ILock
    {
    private:
        inline static std::unique_ptr<SingletonType> _p;

    protected:
        virtual std::unique_ptr<SingletonType> Create() = 0;
        virtual void Lock() = 0;
        virtual void Unlock() = 0;

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

        SingletonType &operator*()
        {
            return Instance();
        }

        SingletonType *operator->()
        {
            return &Instance();
        }
    };
} // namespace base
