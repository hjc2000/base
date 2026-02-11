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
		inline void Delay(base::unit::Nanosecond const &time)
		{
			std::chrono::nanoseconds ns = static_cast<std::chrono::nanoseconds>(time);
			Delay(ns);
		}

		///
		/// @brief 延时。
		///
		/// @param time
		///
		IMPLEMENTED
		inline void Delay(base::unit::Second const &time)
		{
			std::chrono::nanoseconds ns = static_cast<std::chrono::nanoseconds>(time);
			Delay(ns);
		}

	} // namespace task
} // namespace base
