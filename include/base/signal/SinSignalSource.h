#pragma once
#include "base/signal/ISignalSource.h"
#include "base/signal/PeriodicSamplingClock.h"

namespace base
{
	///
	/// @brief 正弦信号源 y = sin(w * t).
	///
	/// @note 使用步骤：
	/// 	@li 构造
	/// 	@li 设置采样间隔
	/// 	@li 打开
	/// 	@li 开始采样
	///
	class SinSignalSource final :
		public base::ISignalSource<double>
	{
	private:
		base::unit::Second _sample_interval{base::Fraction{1, 10}};
		PeriodicSamplingClock _sample_clock;
		bool _opened = false;

	public:
		///
		/// @brief 构造一个正弦信号源。
		///
		/// @param sin_periodic 正弦信号的最小正周期
		///
		SinSignalSource(base::unit::Second sin_periodic);

		///
		/// @brief 采样间隔。
		///
		/// @return base::unit::Second
		///
		virtual base::unit::Second SampleInterval() const override;

		///
		/// @brief 打开采样器。
		///
		/// @param sample_interval
		///
		virtual void Open(base::unit::Second const &sample_interval) override;

		///
		/// @brief 采样一次。
		///
		/// @note 此调用会阻塞，直到时间距离上一次采样过去了 SampleInterval.
		///
		/// @return double 采样值。
		///
		virtual double Sample() override;
	};
} // namespace base
