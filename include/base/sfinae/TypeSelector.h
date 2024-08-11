#pragma once

namespace base
{
    template <bool Value, typename TrueType, typename FalseType>
    struct TypeSelector
    {
        using Type = FalseType;
    };

    template <typename TrueType, typename FalseType>
    struct TypeSelector<true, TrueType, FalseType>
    {
        using Type = TrueType;
    };

    template <typename TrueType, typename FalseType>
    struct TypeSelector<false, TrueType, FalseType>
    {
        using Type = FalseType;
    };
} // namespace base
