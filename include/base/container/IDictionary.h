#pragma once
#include <base/container/IReadOnlyDictionary.h>

namespace base
{
    /// @brief 字典接口。
    /// @tparam KeyType
    /// @tparam ItemType
    template <typename KeyType, typename ItemType>
    class IDictionary :
        public IReadOnlyDictionary<KeyType, ItemType>
    {
    public:
        virtual int Count() const = 0;

        ItemType Get(KeyType key) const override
        {
            return GetReference();
        }

        virtual ItemType &GetReference(KeyType key) = 0;

        virtual void Add(KeyType key, ItemType const &item) = 0;

        virtual std::shared_ptr<IEnumerator<ItemType>> GetEnumerator() = 0;
    };
} // namespace base
