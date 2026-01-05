#pragma once
#include "base/time/TimePointSinceEpoch.h"
#include "base/time/TimeSpan.h"
#include "base/time/UtcHourOffset.h"
#include <chrono>
#include <filesystem>
#include <string>
#include <type_traits>

namespace base
{
	/* #region 类型别名 */
	using ns_time_point = std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds>;
	using us_time_point = std::chrono::time_point<std::chrono::system_clock, std::chrono::microseconds>;
	using ms_time_point = std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds>;
	using s_time_point = std::chrono::time_point<std::chrono::system_clock, std::chrono::seconds>;
	using file_clock_time_point = decltype(std::filesystem::directory_entry{}.last_write_time());

	using ns_zoned_time = std::chrono::zoned_time<std::chrono::nanoseconds>;
	using us_zoned_time = std::chrono::zoned_time<std::chrono::microseconds>;
	using ms_zoned_time = std::chrono::zoned_time<std::chrono::milliseconds>;
	using s_zoned_time = std::chrono::zoned_time<std::chrono::seconds>;
	/* #endregion */

#if HAS_THREAD

	/* #region 转换为 base::TimePointSinceEpoch */

	inline base::TimePointSinceEpoch ToTimePointSinceEpoch(ns_time_point const &value)
	{
		return base::TimePointSinceEpoch{value.time_since_epoch()};
	}

	inline base::TimePointSinceEpoch ToTimePointSinceEpoch(us_time_point const &value)
	{
		return base::TimePointSinceEpoch{value.time_since_epoch()};
	}

	inline base::TimePointSinceEpoch ToTimePointSinceEpoch(ms_time_point const &value)
	{
		return base::TimePointSinceEpoch{value.time_since_epoch()};
	}

	inline base::TimePointSinceEpoch ToTimePointSinceEpoch(s_time_point const &value)
	{
		return base::TimePointSinceEpoch{value.time_since_epoch()};
	}

	inline base::TimePointSinceEpoch ToTimePointSinceEpoch(file_clock_time_point const &value)
	{
		std::chrono::nanoseconds time_since_epoch = value.time_since_epoch();

		// 文件时钟不准，并不是当前的 epoch 时间，而是与 epoch 时间之间有一个固定的偏移量。
		// 获取这个偏移量，然后将文件时钟的时间戳加上偏移量就得到了文件时钟时间戳对应的 epoch 时间戳。
		auto delta = std::chrono::system_clock::now().time_since_epoch() -
					 std::filesystem::file_time_type::clock::now().time_since_epoch();

		time_since_epoch += delta;
		return base::TimePointSinceEpoch{time_since_epoch};
	}

	/* #endregion */

	/* #region 转换为 std::chrono::time_point */

	template <typename ReturnType>
		requires(std::is_same_v<ReturnType, base::ns_time_point>)
	constexpr ReturnType Convert(base::TimePointSinceEpoch const &value)
	{
		return ns_time_point{static_cast<std::chrono::nanoseconds>(value)};
	}

	template <typename ReturnType>
		requires(std::is_same_v<ReturnType, base::us_time_point>)
	constexpr ReturnType Convert(base::TimePointSinceEpoch const &value)
	{
		return us_time_point{static_cast<std::chrono::microseconds>(value)};
	}

	template <typename ReturnType>
		requires(std::is_same_v<ReturnType, base::ms_time_point>)
	constexpr ReturnType Convert(base::TimePointSinceEpoch const &value)
	{
		return ms_time_point{static_cast<std::chrono::milliseconds>(value)};
	}

	template <typename ReturnType>
		requires(std::is_same_v<ReturnType, base::s_time_point>)
	constexpr ReturnType Convert(base::TimePointSinceEpoch const &value)
	{
		return s_time_point{static_cast<std::chrono::seconds>(value)};
	}

	template <typename ReturnType>
		requires(std::is_same_v<ReturnType, base::file_clock_time_point>)
	constexpr ReturnType Convert(base::TimePointSinceEpoch const &value)
	{
		// 文件时钟不准，并不是当前的 epoch 时间，而是与 epoch 时间之间有一个固定的偏移量。
		// 获取这个偏移量，然后将 _time_since_epoch 减去这个偏移量就得到了对应的文件时钟时间戳。
		auto offset = std::chrono::system_clock::now().time_since_epoch() -
					  std::filesystem::file_time_type::clock::now().time_since_epoch();

		return file_clock_time_point{static_cast<std::chrono::nanoseconds>(value) - offset};
	}

	/* #endregion */

	/* #region 转换为 std::chrono::zoned_time */

	///
	/// @brief 将 value 转换为 UTC + 0 区域时间。
	///
	/// @param value
	///
	/// @return
	///
	template <typename ReturnType>
		requires(std::is_same_v<ReturnType, base::ns_zoned_time>)
	constexpr ReturnType Convert(base::TimePointSinceEpoch const &value)
	{
		auto time_point = Convert<base::ns_time_point>(value);
		return ns_zoned_time{"UTC", time_point};
	}

	///
	/// @brief 将 value 转换为 UTC + offset 区域时间。
	///
	/// @param offset 你所在的区域的时间相对于 UTC 的偏移量。
	/// @param value 被转换的时间点。
	///
	/// @return
	///
	template <typename ReturnType>
		requires(std::is_same_v<ReturnType, base::ns_zoned_time>)
	constexpr ReturnType Convert(base::UtcHourOffset const &offset,
								 base::TimePointSinceEpoch const &value)
	{
		base::TimePointSinceEpoch utc8 = value;
		utc8 += offset.Value() * base::TimeSpan{std::chrono::seconds{60 * 60}};
		return Convert<base::ns_zoned_time>(utc8);
	}

	///
	/// @brief 将 value 转换为 UTC + 0 区域时间。
	///
	/// @param value
	///
	/// @return
	///
	template <typename ReturnType>
		requires(std::is_same_v<ReturnType, base::us_zoned_time>)
	constexpr ReturnType Convert(base::TimePointSinceEpoch const &value)
	{
		auto time_point = base::Convert<base::us_time_point>(value);
		return us_zoned_time{"UTC", time_point};
	}

	///
	/// @brief 将 value 转换为 UTC + offset 区域时间。
	///
	/// @param offset 你所在的区域的时间相对于 UTC 的偏移量。
	/// @param value 被转换的时间点。
	///
	/// @return
	///
	template <typename ReturnType>
		requires(std::is_same_v<ReturnType, base::us_zoned_time>)
	constexpr ReturnType Convert(base::UtcHourOffset const &offset,
								 base::TimePointSinceEpoch const &value)
	{
		base::TimePointSinceEpoch utc8 = value;
		utc8 += offset.Value() * base::TimeSpan{std::chrono::seconds{60 * 60}};
		return Convert<base::us_zoned_time>(utc8);
	}

	///
	/// @brief 将 value 转换为 UTC + 0 区域时间。
	///
	/// @param value
	///
	/// @return
	///
	template <typename ReturnType>
		requires(std::is_same_v<ReturnType, base::ms_zoned_time>)
	constexpr ReturnType Convert(base::TimePointSinceEpoch const &value)
	{
		auto time_point = Convert<base::ms_time_point>(value);
		return ms_zoned_time{"UTC", time_point};
	}

	///
	/// @brief 将 value 转换为 UTC + offset 区域时间。
	///
	/// @param offset 你所在的区域的时间相对于 UTC 的偏移量。
	/// @param value 被转换的时间点。
	///
	/// @return
	///
	template <typename ReturnType>
		requires(std::is_same_v<ReturnType, base::ms_zoned_time>)
	constexpr ReturnType Convert(base::UtcHourOffset const &offset,
								 base::TimePointSinceEpoch const &value)
	{
		base::TimePointSinceEpoch utc8 = value;
		utc8 += offset.Value() * base::TimeSpan{std::chrono::seconds{60 * 60}};
		return Convert<base::ms_zoned_time>(utc8);
	}

	///
	/// @brief 将 value 转换为 UTC + 0 区域时间。
	///
	/// @param value
	///
	/// @return
	///
	template <typename ReturnType>
		requires(std::is_same_v<ReturnType, base::s_zoned_time>)
	constexpr ReturnType Convert(base::TimePointSinceEpoch const &value)
	{
		auto time_point = Convert<base::s_time_point>(value);
		return s_zoned_time{"UTC", time_point};
	}

	///
	/// @brief 将 value 转换为 UTC + offset 区域时间。
	///
	/// @param offset 你所在的区域的时间相对于 UTC 的偏移量。
	/// @param value 被转换的时间点。
	///
	/// @return
	///
	template <typename ReturnType>
		requires(std::is_same_v<ReturnType, base::s_zoned_time>)
	constexpr ReturnType Convert(base::UtcHourOffset const &offset,
								 base::TimePointSinceEpoch const &value)
	{
		base::TimePointSinceEpoch utc8 = value;
		utc8 += offset.Value() * base::TimeSpan{std::chrono::seconds{60 * 60}};
		return Convert<base::s_zoned_time>(utc8);
	}

	/* #endregion */

	template <typename ReturnType>
		requires(std::is_same_v<ReturnType, std::chrono::year_month_day>)
	constexpr ReturnType Convert(base::TimePointSinceEpoch const &value)
	{
		std::chrono::year_month_day ret{static_cast<std::chrono::local_days>(value)};
		return ret;
	}

	inline std::string to_string(base::ns_zoned_time const &value)
	{
		return std::format("{:%Y-%m-%d %H:%M:%S}", value);
	}

	inline std::string to_string(base::us_zoned_time const &value)
	{
		return std::format("{:%Y-%m-%d %H:%M:%S}", value);
	}

	inline std::string to_string(base::ms_zoned_time const &value)
	{
		return std::format("{:%Y-%m-%d %H:%M:%S}", value);
	}

	inline std::string to_string(base::s_zoned_time const &value)
	{
		return std::format("{:%Y-%m-%d %H:%M:%S}", value);
	}

	inline std::string to_string(base::TimePointSinceEpoch const &value)
	{
		return base::to_string(base::Convert<base::ns_zoned_time>(base::UtcHourOffset{8}, value));
	}

#endif // HAS_THREAD

} // namespace base
