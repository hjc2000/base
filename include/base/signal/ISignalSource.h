#pragma once
#include "base/unit/Second.h"

namespace base
{
	///
	/// @brief 信号源接口。
	///
	/// @tparam SignalType 信号值的类型。
	///
	template <typename SignalType>
	class ISignalSource
	{
	public:
		///
		/// @brief 采样间隔。
		///
		/// @return base::unit::Second
		///
		virtual base::unit::Second SampleInterval() const = 0;

		///
		/// @brief 打开采样器。
		///
		/// @param sample_interval
		///
		virtual void Open(base::unit::Second const &sample_interval) = 0;

		///
		/// @brief 采样一次。
		///
		/// @note 此调用会阻塞，直到时间距离上一次采样过去了 SampleInterval.
		///
		/// @return SignalType 采样值。
		///
		virtual SignalType Sample() = 0;
	};
} // namespace base
