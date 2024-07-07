#pragma once
#include <base/pipe/IPipeSource.h>
#include <base/task/CancellationToken.h>

namespace base
{
	/// @brief 泵接口
	/// @tparam T 要被泵送的数据类型
	template <typename T>
	class IPump
		: public base::IPipeSource<T>
	{
	public:
		virtual ~IPump() = default;

		/// @brief 将数据从源中取出，泵送给所有消费者
		/// @param cancellation_token
		virtual void PumpDataToConsumers(std::shared_ptr<base::CancellationToken> cancellation_token) = 0;
	};
} // namespace base
