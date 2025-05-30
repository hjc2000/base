#pragma once
#include "base/unit/Seconds.h"

namespace base
{
	///
	/// @brief 周期采样时钟。
	///
	/// @note 时间大于一个周期时会自动减去整数倍的周期，调整到一个周期以内。
	///
	class PeriodicSamplingClock final
	{
	private:
		base::Seconds _period{};
		base::Seconds _current_time{};

		///
		/// @brief 将 _time 调整到 1 个最小正周期以内。
		///
		///
		void AdjustTime();

	public:
		///
		/// @brief 周期采样时钟。
		///
		/// @param period
		///
		PeriodicSamplingClock(base::Seconds period);

		PeriodicSamplingClock &operator+=(base::Seconds value);
		PeriodicSamplingClock &operator-=(base::Seconds value);

		///
		/// @brief 本时钟的周期。
		///
		/// @return base::Seconds
		///
		base::Seconds Period() const;

		///
		/// @brief 当前时间。
		///
		/// @return base::Seconds
		///
		base::Seconds CurrentTime() const;

		///
		/// @brief 相当于调用 CurrentTime 方法。
		///
		/// @return base::Seconds
		///
		explicit operator base::Seconds() const;
	};
} // namespace base
