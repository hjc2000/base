#pragma once
#include "base/container/List.h"
#include "base/delegate/Delegate.h"
#include "base/pipe/IPipeSource.h"
#include "base/pipe/IPump.h"
#include "base/pipe/ISource.h"
#include "base/task/CancellationToken.h"
#include <stdexcept>

namespace base
{
	///
	/// @brief 实现一个普通的泵
	///
	/// @tparam T
	///
	template <typename T>
	class Pump final :
		public base::IPump,
		public base::IPipeSource<T>
	{
	private:
		std::shared_ptr<base::ISource<T>> _source;
		base::List<std::shared_ptr<base::IConsumer<T>>> _consumer_list;
		base::Delegate<T &> _before_sending_data_to_consumers_event;

	public:
		Pump(std::shared_ptr<base::ISource<T>> source)
		{
			if (source == nullptr)
			{
				throw std::invalid_argument{"source 不能为空指针"};
			}

			_source = source;
		}

		///
		/// @brief 消费者列表
		///
		/// @return
		///
		virtual base::IList<std::shared_ptr<base::IConsumer<T>>> &ConsumerList() override
		{
			return _consumer_list;
		}

		///
		/// @brief 在每次将数据送给所有消费者时会触发此事件
		///
		/// @warning 没有线程的环境中，禁止在开始泵送数据后订阅和取消订阅事件。
		///
		/// @return
		///
		base::IEvent<T &> &BeforeSendingDataToConsumersEvent()
		{
			return _before_sending_data_to_consumers_event;
		}

		///
		/// @brief 将数据从源中取出，泵送给每一个消费者
		///
		/// @param cancellation_token
		///
		virtual void PumpDataToConsumers(std::shared_ptr<base::CancellationToken> cancellation_token) override
		{
			T data{};

			while (true)
			{
				base::throw_if_cancellation_is_requested(cancellation_token);

				bool result = _source->ReadData(data);
				if (!result)
				{
					base::IPipeSource<T>::FlushEachConsumer();
					return;
				}

				// 触发回调。允许在每次将数据送给消费者之前通过事件回调修改数据
				_before_sending_data_to_consumers_event(data);
				base::IPipeSource<T>::SendDataToEachConsumer(data);
			}
		}
	};

} // namespace base
