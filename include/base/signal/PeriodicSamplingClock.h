#pragma once
#include "base/unit/Second.h"

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
		base::unit::Second _period{};
		base::unit::Second _current_time{};

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
		PeriodicSamplingClock(base::unit::Second period);

		PeriodicSamplingClock &operator+=(base::unit::Second value);
		PeriodicSamplingClock &operator-=(base::unit::Second value);

		///
		/// @brief 本时钟的周期。
		///
		/// @return base::unit::Second
		///
		base::unit::Second Period() const;

		///
		/// @brief 当前时间。
		///
		/// @return base::unit::Second
		///
		base::unit::Second CurrentTime() const;

		///
		/// @brief 相当于调用 CurrentTime 方法。
		///
		/// @return base::unit::Second
		///
		explicit operator base::unit::Second() const;
	};
} // namespace base
