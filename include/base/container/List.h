#pragma once
#include <algorithm>
#include <base/container/IList.h>
#include <stdexcept>
#include <vector>

namespace base
{
    template <typename ItemType>
    class List final :
        public base::IList<ItemType>
    {
    private:
        std::vector<ItemType> _vector;

    public:
        List() = default;

        List(List<ItemType> const &o)
        {
            _vector = o._vector;
        }

        List(std::vector<ItemType> const &o)
        {
            _vector = o;
        }

        List(std::initializer_list<ItemType> const &list)
        {
            *this = list;
        }

        List<ItemType> &operator=(List<ItemType> const &value)
        {
            _vector = value._vector;
            return *this;
        }

        List<ItemType> &operator=(std::vector<ItemType> const &value)
        {
            _vector = value;
            return *this;
        }

        List<ItemType> &operator=(std::initializer_list<ItemType> const &list)
        {
            Add(list);
            return *this;
        }

        using IList<ItemType>::Add;

        void Add(ItemType const &item) override
        {
            _vector.push_back(item);
        }

        void Insert(int const index, ItemType const &item) override
        {
            if (index < 0 || index > int(_vector.size()))
            {
                throw std::out_of_range{"索引超出范围"};
            }

            _vector.insert(_vector.begin() + index, item);
        }

        bool Remove(ItemType const &item) override
        {
            auto it = std::find(_vector.begin(), _vector.end(), item);
            if (it != _vector.end())
            {
                _vector.erase(it);
                return true; // 返回 true 表示成功找到并删除了元素
            }

            return false; // 如果没有找到元素，返回 false
        }

        void RemoveAt(int const index) override
        {
            if (index < 0 || index >= (int)_vector.size())
            {
                throw std::out_of_range{"索引超出范围"};
            }

            _vector.erase(_vector.begin() + index);
        }

        int IndexOf(ItemType const &item) const override
        {
            auto it = std::find(_vector.begin(), _vector.end(), item);
            if (it != _vector.end())
            {
                return (int)std::distance(_vector.begin(), it); // 返回元素的索引
            }

            return -1; // 如果没有找到元素，返回 -1
        }

        bool Contains(ItemType const &item) const override
        {
            return std::find(_vector.begin(), _vector.end(), item) != _vector.end();
        }

        void Clear() override
        {
            _vector.clear();
        }

        int Count() const override
        {
            return (int)_vector.size();
        }

        ItemType &operator[](int const index) override
        {
            if (index < 0 || index >= int(_vector.size()))
            {
                throw std::out_of_range{"索引超出范围"};
            }

            return _vector[index];
        }

        ItemType const &operator[](int const index) const override
        {
            if (index < 0 || index >= int(_vector.size()))
            {
                throw std::out_of_range{"索引超出范围"};
            }

            return _vector[index];
        }

        /// @brief 将本列表内的元素拷贝到向量中。
        /// @return
        std::vector<ItemType> ToVector()
        {
            // 直接返回，利用 vector 的拷贝构造函数。
            return _vector;
        }

        /// @brief 转发到 std::vector 的相等判断逻辑。
        /// @param another
        /// @return
        bool operator==(List<ItemType> const &another) const
        {
            return _vector == another._vector;
        }
    };
} // namespace base
