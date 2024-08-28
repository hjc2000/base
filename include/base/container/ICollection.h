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
        /// @return 指针。找到了返回元素的指针，找不到返回空指针。
        virtual ItemType *Find(KeyType key) = 0;

        /// @brief 放入一个元素。本来不存在，会添加；本来就存在了，会覆盖。
        /// @param key
        /// @param item
        virtual void Put(KeyType key, ItemType const &item) = 0;

        /// @brief 移除一个元素。
        /// @param key 键
        /// @return 移除成功返回 true，元素不存在返回 false。
        virtual bool Remove(KeyType key) = 0;

        virtual std::shared_ptr<IEnumerator<ItemType>> GetEnumerator() = 0;

#pragma region 扩展

        /// @brief 获取元素。找不到会抛出异常。
        /// @param key
        /// @return
        ItemType &Get(KeyType key)
        {
            ItemType *p = Find(key);
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
