#pragma once
#include <memory>

namespace base
{
    /// @brief C# 风格的迭代器接口
    /// @tparam ItemType
    template <typename ItemType>
    class IEnumerator
    {
    public:
        /// @brief 获取当前值的引用
        /// @return
        virtual ItemType &CurrentValue() = 0;

        /// @brief 迭代器前进到下一个值
        /// @return
        virtual bool MoveNext() = 0;

        /// @brief 将迭代器重置到容器开始的位置。
        /// @note 开始位置是第一个元素前。也就是说重置后，要调用一次 MoveNext 才能获取到第一个值。
        virtual void Reset() = 0;
    };
} // namespace base
