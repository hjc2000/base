#pragma once
#ifndef HAS_THREAD
#define HAS_THREAD 0
#endif

#include <base/container/iterator/IEnumerable.h>
#include <base/container/iterator/StdContainerEnumerator.h>
#include <memory>

namespace base
{
    // C++ 可迭代容器要满足的条件。
    template <typename T>
    concept IsIterable = requires(T &c) {
        c.begin();
        c.end();
    };

    /// @brief 将 std 容器包装为 IEnumerable
    /// @tparam ItemType 被迭代元素的类型
    /// @tparam ContainerType 容器类型
    template <typename ItemType, IsIterable ContainerType>
    class StdContainerEnumerable final :
        public IEnumerable<ItemType>
    {
    private:
        std::shared_ptr<ContainerType> _container;

    public:
        /// @brief 将 std 容器包装为 IEnumerable
        /// @param container
        StdContainerEnumerable(std::shared_ptr<ContainerType> container)
        {
            _container = container;
        }

        /// @brief 获取迭代器
        /// @return
        std::shared_ptr<IEnumerator<ItemType>> GetEnumerator() override
        {
            return std::shared_ptr<IEnumerator<ItemType>>{
                new StdContainerEnumerator<ItemType, decltype(_container->begin())>{
                    _container->begin(),
                    _container->end(),
                },
            };
        }
    };

#if HAS_THREAD
    void TestStdContainerEnumerable();
#endif
} // namespace base
