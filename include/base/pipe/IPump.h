#pragma once
#ifndef HAS_THREAD
#define HAS_THREAD 0
#endif

#include <base/pipe/IPipeSource.h>
#include <base/task/CancellationToken.h>

#if HAS_THREAD
#include <iostream>
#include <thread>
#endif

namespace base
{
	/// @brief 泵接口
	/// @tparam T 要被泵送的数据类型
	class IPump
	{
	public:
		virtual ~IPump() = default;

		/// @brief 将数据从源中取出，泵送给所有消费者
		/// @param cancellation_token
		virtual void PumpDataToConsumers(std::shared_ptr<base::CancellationToken> cancellation_token) = 0;

#if HAS_THREAD
		/// @brief 启动后台线程，将数据从源中取出，泵送给每个消费者。
		/// @note 此调用不会阻塞，会立即返回。
		/// @param cancellation_token
		virtual void PumpDataToConsumersAsync(std::shared_ptr<base::CancellationToken> cancellation_token);
#endif
	};
} // namespace base
