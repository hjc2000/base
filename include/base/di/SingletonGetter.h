#pragma once
#include <base/Guard.h>
#include <base/LockGuard.h>
#include <memory>

namespace base
{
    /// @brief 单例获取器。
    /// @tparam SingletonType
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
        /// @brief 获取单例的引用
        /// @return
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
            if (_p == nullptr)
            {
                throw std::runtime_error{"禁止将 Create 函数实现为返回空指针。"};
            }

            return *_p;
        }

        /// @brief 重载解引用运算符，用来获取单例的引用。
        /// @return
        SingletonType &operator*()
        {
            return Instance();
        }

        /// @brief 重载指针式的成员访问运算符，用来访问单例对象的成员。
        /// @return
        SingletonType *operator->()
        {
            return &Instance();
        }
    };
} // namespace base
