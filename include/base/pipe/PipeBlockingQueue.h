#pragma once
#include "base/container/HysteresisBlockingQueue.h"
#include "base/IDisposable.h"
#include "base/pipe/IConsumer.h"
#include "base/pipe/ISource.h"
#include <atomic>

namespace base
{
	/// @brief 管道队列
	/// @tparam T
	template <typename T>
	class PipeBlockingQueue final :
		public base::IConsumer<T>,
		public base::ISource<T>,
		public base::IDisposable
	{
	private:
		base::HysteresisBlockingQueue<T> _queue{10};
		std::atomic_bool _disposed = false;

	public:
		~PipeBlockingQueue()
		{
			Dispose();
		}

		/// @brief 释放队列
		/// @note 释放后队列会被清空。所以如果想要取消阻塞，但又希望能够读出残留的数据，进行
		/// 收尾，调用 Flush 方法而不是本方法。
		virtual void Dispose() override
		{
			if (_disposed)
			{
				return;
			}

			_disposed = true;
			_queue.Dispose();
		}

		/// @brief 送入数据。
		/// @note 冲洗后调用本方法会引发异常。
		/// @param data
		virtual void SendData(T &data) override
		{
			_queue.Enqueue(data);
		}

		/// @brief 冲洗队列。
		/// @note 冲洗后读取数据不会再被阻塞。
		/// @note 冲洗后送入数据会引发异常。
		virtual void Flush() override
		{
			_queue.Flush();
		}

		/// @brief 读取数据。
		/// @param data
		/// @return 读取成功返回 0，失败返回负数的错误代码。
		virtual int ReadData(T &data) override
		{
			try
			{
				data = _queue.Dequeue();
				return 0;
			}
			catch (std::exception &e)
			{
				return -1;
			}
		}
	};
} // namespace base
