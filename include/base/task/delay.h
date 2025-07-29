#pragma once
#include "base/define.h"
#include "base/unit/Nanosecond.h"
#include "base/unit/Second.h"
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
		void Delay(base::unit::Nanosecond const &time);

		///
		/// @brief 延时。
		///
		/// @param time
		///
		IMPLEMENTED
		void Delay(base::unit::Second const &time);

	} // namespace task
} // namespace base
