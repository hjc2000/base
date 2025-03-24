#pragma once
#include <chrono>

namespace base
{
	///
	/// @brief 延时。
	///
	/// @param time
	///
	void Delay(std::chrono::seconds const &time);

	///
	/// @brief 延时。
	///
	/// @param time
	///
	void Delay(std::chrono::milliseconds const &time);

	///
	/// @brief 延时。
	///
	/// @param time
	///
	void Delay(std::chrono::microseconds const &time);

	///
	/// @brief 延时。
	///
	/// @param time
	///
	void Delay(std::chrono::nanoseconds const &time);

} // namespace base
