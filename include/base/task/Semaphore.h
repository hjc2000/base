#pragma once
#include "base/IDisposable.h"
#include "base/task/IMutex.h"
#include "IBaseSemaphore.h"
#include "IMutex.h"
#include <atomic>
#include <cstdint>
#include <memory>

namespace base
{
	class Semaphore :
		public base::IDisposable
	{
	private:
		std::shared_ptr<base::IBaseSemaphore> _base_semaphore;
		std::shared_ptr<base::IMutex> _lock = base::CreateIMutex();
		std::atomic_bool _disposed = false;
		int32_t _acquire_count = 0;

		Semaphore(Semaphore const &o) = delete;
		Semaphore &operator=(Semaphore const &o) = delete;
		Semaphore(Semaphore const &&o) = delete;
		Semaphore &operator=(Semaphore const &&o) = delete;

	public:
		Semaphore(int32_t initial_count);

		///
		/// @brief 释放本对象的资源。
		///
		/// @note 释放后信号量将不再具有阻塞的能力。再次尝试获取信号量将引发异常。
		///
		virtual void Dispose() override;

		///
		/// @brief 释放信号量。
		///
		/// @param count 要释放的数量。
		///
		void Release(int32_t count);

		///
		/// @brief 释放所有等待的线程。
		///
		///
		void ReleaseAll();

		///
		/// @brief 在中断中释放信号量。
		///
		/// @param count
		///
		void ReleaseFromISR(int32_t count);

		///
		/// @brief 在中断中释放所有等待的线程。
		///
		///
		void ReleaseAllFromISR();

		///
		/// @brief 获取信号量。无限等待，永不超时。
		///
		///
		void Acquire();

		///
		/// @brief 尝试获取信号量。超时后会失败，并返回 false，成功获取信号量后将
		/// 返回 true.
		///
		/// @param timeout 超时时间。
		///
		/// @return true 获取信号量成功。
		/// @return false 获取信号量失败。
		///
		bool TryAcquire(base::Seconds const &timeout);

		///
		/// @brief 释放 1 个信号量。
		///
		///
		void Release();

		///
		/// @brief 在中断中释放一个信号量。
		///
		///
		void ReleaseFromISR();

		///
		/// @brief 当前正在等待获取信号量的线程数。
		///
		/// @return int32_t
		///
		int32_t AcquireCount() const
		{
			return _acquire_count;
		}
	};
} // namespace base
