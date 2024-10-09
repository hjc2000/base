#pragma once
#include <base/container/IDictionary.h>

namespace base
{
    template <typename KeyType, typename ValueType>
    class Dictionary :
        public base::IDictionary<KeyType, ValueType>
    {
    private:
        std::map<KeyType, ValueType> _map{};

    public:
        /// @brief 获取元素个数。
        /// @return
        virtual int Count() const = 0;

        /// @brief 查找元素。
        /// @param key 键
        /// @return 指针。找到了返回元素的指针，找不到返回空指针。
        virtual ValueType *Find(KeyType key) = 0;

        /// @brief 移除一个元素。
        /// @param key 键
        /// @return 移除成功返回 true，元素不存在返回 false。
        virtual bool Remove(KeyType key) = 0;

        /// @brief 设置一个元素。本来不存在，会添加；本来就存在了，会覆盖。
        /// @param key
        /// @param item
        virtual void Set(KeyType key, ValueType const &item) = 0;

        /// @brief 获取迭代器
        /// @return
        virtual std::shared_ptr<IEnumerator<std::pair<KeyType const, ValueType>>> GetEnumerator() = 0;
    };
} // namespace base
