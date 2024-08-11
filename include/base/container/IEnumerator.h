#pragma once
#include <memory>

namespace base
{
    /// @brief 迭代器接口
    /// @tparam ItemType
    template <typename ItemType>
    class IEnumerator
    {
    public:
        virtual ~IEnumerator() = default;

        virtual ItemType &CurrentValue() = 0;
        virtual bool MoveNext() = 0;
        virtual void Reset() = 0;
    };
} // namespace base
