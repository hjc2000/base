#pragma once
#include <base/container/iterator/IEnumerator.h>

namespace base
{
    // C++ 迭代器类要满足的要求。
    template <typename T>
    concept IsIterator = requires(T &c) {
        c++;
        c == c;
        *c;
    };

    /// @brief 将 std 容器的迭代器包装为 IEnumerator。
    /// @tparam ItemType 被迭代元素的类型。
    /// @tparam IteratorType 迭代器类型。
    template <typename ItemType, IsIterator IteratorType>
    class StdContainerEnumerator final :
        public base::IEnumerator<ItemType>
    {
    private:
        IteratorType _current_iterator;
        IteratorType _begin_iterator;
        IteratorType _end_iterator;
        bool _is_first_move = true;

    public:
        /// @brief 将 std 容器的迭代器包装为 IEnumerator。
        /// @param begin_iterator
        /// @param end_iterator
        StdContainerEnumerator(IteratorType begin_iterator, IteratorType end_iterator)
        {
            _current_iterator = begin_iterator;
            _begin_iterator = begin_iterator;
            _end_iterator = end_iterator;
        }

        /// @brief 当前值
        /// @return
        ItemType &CurrentValue() override
        {
            return *_current_iterator;
        }

        /// @brief 移动到下一个值
        /// @return
        bool MoveNext() override
        {
            if (_is_first_move)
            {
                _is_first_move = false;
            }
            else
            {
                _current_iterator++;
            }

            if (_current_iterator == _end_iterator)
            {
                // 移动到下一个元素失败
                return false;
            }

            // 移动到下一个元素成功
            return true;
        }

        /// @brief 将迭代器重置到第一个元素的位置。
        void Reset() override
        {
            _is_first_move = true;
            _current_iterator = _begin_iterator;
        }
    };
} // namespace base
