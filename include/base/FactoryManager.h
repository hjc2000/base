#pragma once
#ifndef HAS_THREAD
#define HAS_THREAD 0
#endif

#include <memory>

#if HAS_THREAD
#include <mutex>
#endif

namespace base
{
    /// @brief 工厂管理者
    /// @tparam FactoryType 工厂类
    template <typename FactoryType>
    class FactoryManager
    {
    private:
        std::shared_ptr<FactoryType> _costom_factory = nullptr;

#if HAS_THREAD
        std::mutex _lock;
#endif

    public:
        virtual ~FactoryManager() = default;

        /// @brief 设置了自定义工厂后就会返回自定义工厂，否则返回默认工厂。
        /// @return
        std::shared_ptr<FactoryType> Factory()
        {
#if HAS_THREAD
            std::lock_guard l{_lock};
#endif

            if (_costom_factory)
            {
                return _costom_factory;
            }

            return DefaultFactory();
        }

        void SetCustomFactory(std::shared_ptr<FactoryType> o)
        {
#if HAS_THREAD
            std::lock_guard l{_lock};
#endif

            _costom_factory = o;
        }

        virtual std::shared_ptr<FactoryType> DefaultFactory() = 0;
    };
} // namespace base
