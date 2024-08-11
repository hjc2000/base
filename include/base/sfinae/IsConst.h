#pragma once

namespace base
{
    template <typename Type>
    struct IsConst
    {
        static consteval bool Value()
        {
            return false;
        }
    };

    template <typename Type>
    struct IsConst<Type const>
    {
        static consteval bool Value()
        {
            return true;
        }
    };

    template <typename T>
    consteval bool IsConstType()
    {
        return IsConst<T>::Value();
    }
} // namespace base
