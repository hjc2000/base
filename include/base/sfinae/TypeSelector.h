#pragma once

namespace base
{
	///
	/// @brief 类型选择器
	///
	/// @note 通过偏特化，当 Value 为不同的值时，让其中的 Type 成为 TrueType 或 FalseType 的别名。
	///
	template <bool Value, typename TrueType, typename FalseType>
	struct TypeSelector
	{
		using Type = FalseType;
	};

	///
	/// @brief 类型选择器。
	///
	/// @note Value 的值为 true 的偏特化版本。
	///
	template <typename TrueType, typename FalseType>
	struct TypeSelector<true, TrueType, FalseType>
	{
		using Type = TrueType;
	};

	///
	/// @brief 类型选择器
	///
	/// @note Value 的值为 false 的偏特化版本。
	///
	template <typename TrueType, typename FalseType>
	struct TypeSelector<false, TrueType, FalseType>
	{
		using Type = FalseType;
	};
} // namespace base
