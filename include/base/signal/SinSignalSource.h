#pragma once
#include <base/signal/ISignalSource.h>
#include <base/signal/PeriodicSamplingClock.h>

namespace base
{
	/// @brief 正弦信号源 y = sin(w * t)
	/// @note 使用步骤：
	/// 	@li 构造
	/// 	@li 设置采样间隔
	/// 	@li 打开
	/// 	@li 开始采样
	class SinSignalSource final
		: public base::ISignalSource<double>
	{
	private:
		base::Fraction _sample_interval{1, 10};
		PeriodicSamplingClock _sample_clock;
		bool _opened = false;

	public:
		/// @brief
		/// @param sin_periodic 正弦信号的最小正周期
		SinSignalSource(base::Fraction sin_periodic);

		/// @brief 采样间隔。单位：秒。
		/// @return
		base::Fraction SampleInterval() const override;

		/// @brief 设置采样间隔。单位：秒。
		/// @param value
		void SetSampleInterval(base::Fraction value) override;

		/// @brief 打开采样器。
		/// @note 打开后不能更改属性。
		void Open() override;

		/// @brief 采样一次。
		/// @note 调用者不需要延时，每次采样都会自动将内部维护的时间递增构造函数
		/// 传进来的 sample_interval。
		///
		/// @return 采样值。
		double Sample() override;
	};
}
