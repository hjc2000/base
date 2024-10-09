#pragma once
#include <array>
#include <base/container/iterator/IEnumerable.h>
#include <stdexcept>

namespace base
{
    /// @brief 数组
    /// @tparam ItemType
    /// @tparam Count
    template <typename ItemType, int Count>
    class Array :
        public base::IEnumerable<ItemType>
    {
    private:
        std::array<ItemType, Count> _arr{};

#pragma region 迭代器

        class Enumerator :
            public base::IEnumerator<ItemType>
        {
        private:
            int _index = 0;
            bool _first_move = true;
            std::array<ItemType, Count> &_arr;

        public:
            Enumerator(std::array<ItemType, Count> &arr)
                : _arr(arr)
            {
                Reset();
            }

            /// @brief 获取当前值的引用
            /// @return
            ItemType &CurrentValue() override
            {
                return _arr[_index];
            }

            /// @brief 迭代器前进到下一个值
            /// @return
            bool MoveNext() override
            {
                if (_first_move)
                {
                    _first_move = false;
                }
                else
                {
                    _index++;
                }

                if (_index < 0 || _index >= Count)
                {
                    return false;
                }

                return true;
            }

            /// @brief 将迭代器重置到容器开始的位置。
            /// @note 开始位置是第一个元素前。也就是说重置后，要调用一次 MoveNext 才能获取到第一个值。
            void Reset() override
            {
                _first_move = true;
                _index = 0;
            }
        };

#pragma endregion

    public:
        Array() = default;

        Array(Array const &o)
        {
            *this = o;
        }

        /// @brief 将初始化列表的数据拷贝过来。
        /// @param list
        Array(std::initializer_list<ItemType> const &list)
        {
            if (list.size() > Count)
            {
                throw std::out_of_range{"数组太小了，无法放下初始化列表"};
            }

            int i = 0;
            for (auto &item : list)
            {
                _arr[i++] = item;
            }
        }

        /// @brief 将裸数组的元素拷贝过来。
        /// @param buffer
        /// @param offset
        /// @param count
        Array(ItemType const *buffer, int offset, int count)
        {
            CopyFrom(buffer, offset, count);
        }

        /// @brief 将 o 的数据拷贝过来。
        /// @param o
        Array(std::array<ItemType, Count> const &o)
        {
            _arr = o;
        }

        Array &operator=(Array const &o)
        {
            _arr = o._arr;
            return *this;
        }

        ItemType &operator[](int index)
        {
            if (index < 0 || index >= Count)
            {
                throw std::out_of_range{"index 超出范围。"};
            }

            return _arr[index];
        }

        /// @brief 获取迭代器
        /// @return
        std::shared_ptr<IEnumerator<ItemType>> GetEnumerator() override
        {
            return std::shared_ptr<IEnumerator<ItemType>>{
                new Enumerator{_arr},
            };
        }

        /// @brief 将裸数组的元素拷贝过来。
        /// @param buffer
        /// @param offset
        /// @param count
        void CopyFrom(ItemType const *buffer, int offset, int count)
        {
            if (count > Count)
            {
                throw std::out_of_range{"数组放不下，CopyFrom 失败"};
            }

            std::copy(buffer + offset, buffer + offset + count, _arr.data());
        }
    };
} // namespace base
