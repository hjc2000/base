#pragma once
#include <base/container/IEnumerable.h>
#include <base/container/StdMapValuesEnumerator.h>
#include <map>

namespace base
{
    /// @brief 将 std::map 包装成可被迭代值的对象。
    /// @tparam KeyType
    /// @tparam ItemType
    template <typename KeyType, typename ItemType>
    class StdMapValuesEnumerable final :
        base::IEnumerable<ItemType>
    {
    private:
        std::shared_ptr<std::map<KeyType, ItemType>> _map;

    public:
        /// @brief 将 std::map 包装成可被迭代值的对象。
        /// @param map
        StdMapValuesEnumerable(std::shared_ptr<std::map<KeyType, ItemType>> map)
        {
            _map = map;
        }

        /// @brief 获取迭代器。
        /// @return
        std::shared_ptr<IEnumerator<ItemType>> GetEnumerator() override
        {
            return std::shared_ptr<IEnumerator<ItemType>>{
                new StdMapValuesEnumerator<KeyType, ItemType>{_map},
            };
        }
    };
} // namespace base
