#pragma once
#include <base/container/IEnumerable.h>

namespace base
{
    /// @brief 字典接口。
    /// @tparam KeyType
    /// @tparam ItemType
    template <typename KeyType, typename ItemType>
    class IDictionary :
        public base::IEnumerable<ItemType>
    {
    public:
        virtual int Count() const = 0;

        virtual void Find(KeyType key, ItemType *&out) = 0;

        ItemType &Get(KeyType key)
        {
            ItemType *p = nullptr;
            Find(p);
            if (p = nullptr)
            {
                throw std::runtime_error{"找不到元素"};
            }

            return *p;
        }

        ItemType const &Get(KeyType key) const
        {
            return const_cast<IDictionary<KeyType, ItemType> *>(this)->Get(key);
        }

        virtual void Put(KeyType key, ItemType const &item) = 0;

        virtual std::shared_ptr<IEnumerator<ItemType>> GetEnumerator() = 0;
    };
} // namespace base
