#pragma once

namespace bsae
{
	///
	/// @brief 一个概念，表示 InType 能被显示转换为 OutType.
	///
	/// @note 概念的返回值是 bool 值，可以配合 std::enable_if_t 使用。
	///
	template <typename InType, typename OutType>
	concept explicitly_convertible_to = requires(InType t) {
		{ static_cast<OutType>(t) } -> std::same_as<OutType>;
	};
} // namespace bsae
