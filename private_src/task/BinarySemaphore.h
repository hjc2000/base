#pragma once
#include "base/task/IBinarySemaphore.h"
#include <semaphore>

#if HAS_THREAD

namespace base
{
	class BinarySemaphore :
		public base::IBinarySemaphore
	{
	private:
		std::binary_semaphore _bs;

	public:
		BinarySemaphore(bool initial_release);

		///
		/// @brief 释放信号量。
		///
		virtual void Release() override;

		///
		/// @brief 在中断中释放信号量。
		///
		virtual void ReleaseFromISR() override;

		///
		/// @brief 获取信号量。无限等待，永不超时。
		///
		virtual void Acquire() override;

		///
		/// @brief 尝试获取信号量。超时后会失败，并返回 false，成功获取信号量后将
		/// 返回 true.
		/// @param timeout 超时时间。
		/// @return
		///
		virtual bool TryAcquire(base::Seconds const &timeout) override;
	};
} // namespace base

#endif // HAS_THREAD
