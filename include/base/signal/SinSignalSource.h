#pragma once
#include "base/math/Fraction.h"
#include <base/signal/ISignalSource.h>
#include <base/signal/PeriodicSamplingClock.h>

namespace base
{
	/**
	 * @brief 正弦信号源 y = sin(w * t)
	 *
	 * @note 使用步骤：
	 *		@li 构造
	 *		@li 设置采样间隔
	 *		@li 打开
	 *		@li 开始采样
	 */
	class SinSignalSource final :
		public base::ISignalSource<double>
	{
	private:
		base::Seconds _sample_interval{base::Fraction{1, 10}};
		PeriodicSamplingClock _sample_clock;
		bool _opened = false;

	public:
		/**
		 * @brief
		 *
		 * @param sin_periodic 正弦信号的最小正周期
		 */
		SinSignalSource(base::Seconds sin_periodic);

	public:
		/**
		 * @brief 采样间隔。
		 *
		 * @return base::Seconds
		 */
		virtual base::Seconds SampleInterval() const override;

		/**
		 * @brief 打开采样器。
		 *
		 * @param sample_interval
		 */
		virtual void Open(base::Seconds const &sample_interval) override;

		/**
		 * @brief 采样一次。
		 *
		 * @note 此调用会阻塞，直到时间距离上一次采样过去了 SampleInterval
		 *
		 * @return SignalType 采样值。
		 */
		virtual double Sample() override;
	};
} // namespace base
