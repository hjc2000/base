#pragma once
#include "base/define.h"
#include "base/unit/Nanoseconds.h"
#include "base/unit/Seconds.h"
#include <chrono>

namespace base
{
	namespace task
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

		///
		/// @brief 延时。
		///
		/// @param time
		///
		IMPLEMENTED
		void Delay(base::Nanoseconds const &time);

		///
		/// @brief 延时。
		///
		/// @param time
		///
		IMPLEMENTED
		void Delay(base::Seconds const &time);

	} // namespace task
} // namespace base
