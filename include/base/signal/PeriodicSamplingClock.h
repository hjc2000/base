#pragma once
#include <base/math/Fraction.h>
#include <stdint.h>

namespace base
{
	/// @brief 周期采样时钟。
	/// @note 时间大于一个周期时会自动减去整数倍的周期，调整到一个周期以内。
	class PeriodicSamplingClock
	{
	private:
		base::Fraction _period{};
		base::Fraction _time{};

		/// @brief 将 _time 调整到 1 个最小正周期以内。
		void AdjustTime();

	public:
		/// @brief 时钟的周期。
		/// @param period
		PeriodicSamplingClock(base::Fraction period);

		PeriodicSamplingClock &operator+=(base::Fraction value);
		PeriodicSamplingClock &operator-=(base::Fraction value);
		PeriodicSamplingClock &operator*=(base::Fraction value);
		PeriodicSamplingClock &operator/=(base::Fraction value);

		/// @brief 本时钟的周期
		/// @return
		base::Fraction Period() const;

		/// @brief 时间
		/// @return
		base::Fraction Time() const;

		/// @brief 将本时钟强制转换为分数。
		/// @note 此分数的意义是时间，即相当于调用 Time 方法。
		explicit operator base::Fraction() const;
	};
} // namespace base
