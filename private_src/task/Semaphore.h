#pragma once
#include <base/task/ISemaphore.h>
#include <semaphore>

namespace base
{
	class Semaphore :
		public base::ISemaphore
	{
	public:
		/// @brief 释放信号量。
		/// @param count 要释放的数量。
		virtual void Release(int count) = 0;

		/// @brief 获取信号量。无限等待，永不超时。
		virtual void Acquire() = 0;

		/// @brief 尝试获取信号量。超时后会失败，并返回 false，成功获取信号量后将
		/// 返回 true.
		/// @param timeout 超时时间。
		/// @return
		virtual bool TryAcquire(base::Seconds const &timeout) = 0;
	};
} // namespace base
