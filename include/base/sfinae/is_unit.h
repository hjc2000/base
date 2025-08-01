#pragma once

namespace base
{
	namespace unit
	{
		template <typename TSelf>
		class IUnit;
	}

	///
	/// @brief 概念。检查 T 是不是单位。
	///
	///
	template <typename T>
	concept is_unit = requires(T t) {
		requires(std::is_base_of_v<base::unit::IUnit<T>, T>);
	};

} // namespace base
