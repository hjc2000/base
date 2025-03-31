#include "IBaseSemaphore.h"
#include "base/string/define.h"
#include <cstdint>
#include <memory>
#include <semaphore>

#if HAS_THREAD

namespace
{
	class BaseSemaphore :
		public base::IBaseSemaphore
	{
	private:
		std::counting_semaphore<INT32_MAX> _semaphore{0};

	public:
		BaseSemaphore(int32_t initial_count)
			: _semaphore(initial_count)
		{
		}

		///
		/// @brief 释放信号量。
		///
		/// @param count 要释放的数量。
		///
		virtual void Release(int32_t count) override
		{
			if (count <= 0)
			{
				throw std::invalid_argument{CODE_POS_STR + "count 不能 <= 0."};
			}

			_semaphore.release(count);
		}

		///
		/// @brief 在中断中释放信号量。
		///
		/// @param count
		///
		virtual void ReleaseFromISR(int32_t count) override
		{
			Release(count);
		}

		///
		/// @brief 获取信号量。无限等待，永不超时。
		///
		///
		virtual void Acquire() override
		{
			_semaphore.acquire();
		}

		///
		/// @brief 尝试获取信号量。超时后会失败，并返回 false，成功获取信号量后将
		/// 返回 true.
		///
		/// @param timeout 超时时间。
		///
		/// @return true 获取信号量成功。
		/// @return false 获取信号量失败。
		///
		virtual bool TryAcquire(base::Seconds const &timeout) override
		{
			if (timeout < 0)
			{
				throw std::invalid_argument{CODE_POS_STR + "超时时间不能 <= 0."};
			}

			bool result = _semaphore.try_acquire_for(static_cast<std::chrono::milliseconds>(timeout));
			return result;
		}
	};
} // namespace

std::shared_ptr<base::IBaseSemaphore> base::CreateBaseSemaphore(int32_t initial_count)
{
	return std::shared_ptr<BaseSemaphore>{new BaseSemaphore{initial_count}};
}

#endif // HAS_THREAD
