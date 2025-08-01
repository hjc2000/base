#pragma once
#include <cstdint>
#include <type_traits>

namespace base
{
	template <typename T>
		requires(std::is_same_v<T, double>)
	constexpr int64_t floor(T value)
	{
		return static_cast<int64_t>(value);
	}

	template <typename T>
		requires(std::is_same_v<T, float>)
	constexpr int64_t floor(T value)
	{
		return static_cast<int64_t>(value);
	}

	template <typename T>
		requires(std::is_same_v<T, double>)
	constexpr int64_t ceil(T value)
	{
		int64_t int_part = static_cast<int64_t>(value);
		double fractional_part = value - static_cast<double>(int_part);
		if (fractional_part == 0.0)
		{
			return int_part;
		}

		return int_part + 1;
	}

	template <typename T>
		requires(std::is_same_v<T, float>)
	constexpr int64_t ceil(T value)
	{
		int64_t int_part = static_cast<int64_t>(value);
		float fractional_part = value - static_cast<float>(int_part);
		if (fractional_part == 0.0f)
		{
			return int_part;
		}

		return int_part + 1;
	}

	///
	/// @brief 求绝对值。
	///
	/// @param value
	/// @return
	///
	template <typename T>
	constexpr T abs(T const &value)
	{
		if (value < T{})
		{
			return -value;
		}

		return value;
	}

	///
	/// @brief 降低分辨率。
	///
	/// @return 降低分辨率后的值。
	///
	template <typename T>
		requires(std::is_integral_v<T>)
	constexpr T reduce_resolution(T value, T resolution)
	{
		return value / resolution * resolution;
	}

	///
	/// @brief 降低分辨率。
	///
	/// @return 降低分辨率后的值。
	///
	template <typename T>
		requires(std::is_floating_point_v<T>)
	constexpr T reduce_resolution(T value, T resolution)
	{
		return base::floor(value / resolution) * resolution;
	}

} // namespace base
