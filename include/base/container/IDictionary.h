#pragma once
#include <base/container/IEnumerable.h>

namespace base
{
    /// @brief 只读字典接口。
    /// @tparam KeyType
    /// @tparam ItemType
    template <typename KeyType, typename ItemType>
    class IReadOnlyDictionary :
        public base::IEnumerable<ItemType>
    {
    public:
        virtual int Count() const = 0;
        virtual ItemType Get(KeyType key) const = 0;
        virtual std::shared_ptr<IEnumerator<ItemType>> GetEnumerator() = 0;
    };

    /// @brief 字典接口。
    /// @tparam KeyType
    /// @tparam ItemType
    template <typename KeyType, typename ItemType>
    class IDictionary :
        public IReadOnlyDictionary<KeyType, ItemType>
    {
    public:
        virtual int Count() const = 0;
        virtual ItemType Get(KeyType key) const = 0;
        virtual void Put(KeyType key, ItemType const &item) = 0;
        virtual std::shared_ptr<IEnumerator<ItemType>> GetEnumerator() = 0;
    };
} // namespace base
