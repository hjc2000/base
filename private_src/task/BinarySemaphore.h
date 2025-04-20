#pragma once
#include "base/string/define.h"
#include "base/task/IBinarySemaphore.h"
#include "base/unit/Nanoseconds.h"
#include "base/unit/Seconds.h"
#include <chrono>
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
		BinarySemaphore(bool initial_release)
			: _bs(initial_release)
		{
		}

		///
		/// @brief 释放信号量。
		///
		virtual void Release() override
		{
			_bs.release();
		}

		///
		/// @brief 在中断中释放信号量。
		///
		virtual void ReleaseFromISR() override
		{
			Release();
		}

		///
		/// @brief 获取信号量。无限等待，永不超时。
		///
		virtual void Acquire() override
		{
			_bs.acquire();
		}

		///
		/// @brief 尝试获取信号量。超时后会失败，并返回 false，成功获取信号量后将
		/// 返回 true.
		/// @param timeout 超时时间。
		/// @return
		///
		virtual bool TryAcquire(base::Seconds const &timeout) override
		{
			if (timeout < base::Seconds{0})
			{
				throw std::invalid_argument{CODE_POS_STR + "超时时间不能 <= 0."};
			}

			return _bs.try_acquire_for(static_cast<std::chrono::nanoseconds>(timeout));
		}
	};
} // namespace base

#endif // HAS_THREAD
