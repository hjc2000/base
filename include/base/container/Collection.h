#pragma once
#include <base/container/ICollection.h>
#include <base/container/iterator/StdMapValuesEnumerable.h>
#include <map>

namespace base
{
    template <typename KeyType, typename ItemType>
    class Collection :
        public base::ICollection<KeyType, ItemType>
    {
    private:
        std::map<KeyType, ItemType> _map;

    public:
        Collection() = default;

        Collection(Collection const &o)
        {
            *this = o;
        }

        Collection(std::map<KeyType, ItemType> const &o)
        {
            *this = o;
        }

        Collection(std::initializer_list<std::pair<KeyType, ItemType>> const &list)
        {
            for (auto pair : list)
            {
                _map.insert(pair);
            }
        }

        Collection &operator=(Collection const &o)
        {
            _map = o._map;
            return *this;
        }

        /// @brief 获取元素个数。
        /// @return
        int Count() const override
        {
            return _map.size();
        }

        /// @brief 查找元素。
        /// @param key 键
        /// @return 指针。找到了返回元素的指针，找不到返回空指针。
        ItemType *Find(KeyType key) override
        {
            auto it = _map.find(key);
            if (it == _map.end())
            {
                return nullptr;
            }

            return &it->second;
        }

        /// @brief 放入一个元素。本来不存在，会添加；本来就存在了，会覆盖。
        /// @param key
        /// @param item
        void Put(KeyType key, ItemType const &item) override
        {
            _map.insert(std::pair{key, item});
        }

        /// @brief 移除一个元素。
        /// @param key 键
        /// @return 移除成功返回 true，元素不存在返回 false。
        bool Remove(KeyType key) override
        {
            auto it = _map.find(key);
            if (it == _map.end())
            {
                return false;
            }

            _map.erase(it);
            return true;
        }

        std::shared_ptr<IEnumerator<ItemType>> GetEnumerator() override
        {
            return std::shared_ptr<base::IEnumerator<ItemType>>{
                new base::StdMapValuesEnumerator<KeyType, ItemType>{
                    &_map,
                },
            };
        }
    };
} // namespace base
