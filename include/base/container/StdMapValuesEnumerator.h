#pragma once
#include <base/container/IEnumerable.h>
#include <map>

namespace base
{
    /// @brief 用来迭代 std::map 中的值的迭代器。
    /// @tparam KeyType
    /// @tparam ItemType
    template <typename KeyType, typename ItemType>
    class StdMapValuesEnumerator final :
        public base::IEnumerator<ItemType>
    {
    private:
        std::map<KeyType, ItemType> *_map;
        decltype(_map->begin()) _current_it;
        bool _first_move = true;

    public:
        /// @brief 用来迭代 std::map 中的值的迭代器。
        /// @param map
        StdMapValuesEnumerator(std::map<KeyType, ItemType> *map)
        {
            _map = map;
            Reset();
        }

        ItemType &CurrentValue() override
        {
            return _current_it->second;
        }

        bool MoveNext() override
        {
            if (_first_move)
            {
                _first_move = false;
                _current_it = _map->begin();
            }
            else
            {
                _current_it++;
            }

            return _current_it != _map->end();
        }

        void Reset() override
        {
            _current_it = _map->begin();
        }
    };

} // namespace base
