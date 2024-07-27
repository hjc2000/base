#pragma once
#ifndef HAS_THREAD
#define HAS_THREAD 0
#endif

#if HAS_THREAD
#include <atomic>
#include <base/IDisposable.h>
#include <base/container/HysteresisBlockingQueue.h>
#include <base/pipe/IConsumer.h>
#include <base/pipe/ISource.h>
#include <stdexcept>

namespace base
{
	/// @brief 管道队列
	/// @tparam T
	template <typename T>
	class PipeBlockingQueue
		: public base::IConsumer<T>,
		  public base::ISource<T>,
		  public base::IDisposable
	{
	private:
		base::HysteresisBlockingQueue<T> _queue{10};
		std::atomic_bool _disposed = false;

	public:
		/// @brief 释放队列
		/// @note 释放后队列会被清空。所以如果想要取消阻塞，但又希望能够读出残留的数据，进行
		/// 收尾，调用 Flush 方法而不是本方法。
		void Dispose() override
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
		void SendData(T &data) override
		{
			_queue.Enqueue(data);
		}

		/// @brief 冲洗队列。
		/// @note 冲洗后读取数据不会再被阻塞。
		/// @note 冲洗后送入数据会引发异常。
		void Flush() override
		{
			_queue.Flush();
		}

		/// @brief 读取数据。
		/// @param data
		/// @return 读取成功返回 0，失败返回负数的错误代码。
		int ReadData(T &data) override
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
}
#endif // HAS_THREAD