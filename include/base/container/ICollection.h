#pragma once
#include <base/container/IEnumerable.h>

namespace base
{
    /// @brief 集合接口。
    /// @note 集合被迭代的仅仅是元素，而不是键值对。这点与字典不同。
    /// @tparam KeyType
    /// @tparam ItemType
    template <typename KeyType, typename ItemType>
    class ICollection :
        public base::IEnumerable<ItemType>
    {
    public:
        /// @brief 获取元素个数。
        /// @return
        virtual int Count() const = 0;

        /// @brief 查找元素。
        /// @param key 键
        /// @param out 指针。找到了此指针会被修改为指向该元素。找不到则赋值为空指针。
        virtual void Find(KeyType key, ItemType *&out) = 0;

        /// @brief 放入一个元素。本来不存在，会添加；本来就存在了，会覆盖。
        /// @param key
        /// @param item
        virtual void Put(KeyType key, ItemType const &item) = 0;

        virtual std::shared_ptr<IEnumerator<ItemType>> GetEnumerator() = 0;

#pragma region 扩展

        /// @brief 获取元素。找不到会抛出异常。
        /// @param key
        /// @return
        ItemType &Get(KeyType key)
        {
            ItemType *p = nullptr;
            Find(p);
            if (p == nullptr)
            {
                throw std::runtime_error{"找不到元素"};
            }

            return *p;
        }

        /// @brief 获取元素。找不到会抛出异常。
        /// @param key
        /// @return
        ItemType const &Get(KeyType key) const
        {
            return const_cast<ICollection<KeyType, ItemType> *>(this)->Get(key);
        }

#pragma endregion
    };
} // namespace base
