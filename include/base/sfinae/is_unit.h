#pragma once
#include "type_traits.h"

namespace base
{
	namespace unit
	{
		template <typename TSelf>
		class IUnit;

		///
		/// @brief 概念。检查 T 是不是单位。
		///
		template <typename T>
		concept is_unit = requires(T t) {
			requires(base::is_real_base_of<base::unit::IUnit<T>, T>);
		};

	} // namespace unit

	namespace int64_unit
	{
		template <typename TSelf>
		class IUnit;

		///
		/// @brief 概念。检查 T 是不是单位。
		///
		template <typename T>
		concept is_unit = requires(T t) {
			requires(base::is_real_base_of<base::unit::IUnit<T>, T>);
		};

	} // namespace int64_unit

} // namespace base
