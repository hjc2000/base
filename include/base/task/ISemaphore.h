#pragma once
#include <base/IDisposable.h>
#include <base/unit/Seconds.h>
#include <memory>

namespace base
{
	/**
	 * @brief 可以被 Dispose 的信号量。Dispose 之后信号量不再具有阻塞能力。
	 *
	 */
	class ISemaphore :
		public base::IDisposable
	{
	public:
		/**
		 * @brief 释放本对象的资源。
		 *
		 * @note 释放后信号量将不再具有阻塞的能力。再次尝试获取信号量将引发异常。
		 */
		virtual void Dispose() = 0;

		/**
		 * @brief 释放信号量。
		 *
		 * @param count 要释放的数量。
		 */
		virtual void Release(int32_t count) = 0;

		/**
		 * @brief 释放 1 个信号量。
		 *
		 */
		void Release();

		/**
		 * @brief 释放所有等待者。
		 *
		 * @note 此方法会发生误触，例如无时间间隔连续一直调用会因为被释放的线程没来得及递减计数
		 * 而导致以为还有那么多线程被阻塞，进而导致重复释放。
		 */
		virtual void ReleaseAllAcquire() = 0;

		/**
		 * @brief 获取信号量。无限等待，永不超时。
		 *
		 */
		virtual void Acquire() = 0;

		/**
		 * @brief 尝试获取信号量。超时后会失败，并返回 false，成功获取信号量后将
		 * 返回 true.
		 *
		 * @param timeout 超时时间。
		 * @return true 获取信号量成功。
		 * @return false 获取信号量失败。
		 */
		virtual bool TryAcquire(base::Seconds const &timeout) = 0;
	};
} // namespace base

namespace base
{
	///
	/// @brief 创建一个信号量。
	///
	/// @param initial_count 信号量的初始计数。
	/// @return std::shared_ptr<base::ISemaphore>
	///
	std::shared_ptr<base::ISemaphore> CreateISemaphore(int32_t initial_count);

} // namespace base
