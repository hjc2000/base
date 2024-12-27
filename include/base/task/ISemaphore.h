#pragma once
#include <base/IDisposable.h>
#include <base/unit/Seconds.h>
#include <memory>

namespace base
{
	class ISemaphore :
		public base::IDisposable
	{
	public:
		/// @brief 释放本对象的资源。
		/// @note 释放后信号量将不再具有阻塞的能力。再次尝试获取信号量将引发异常。
		virtual void Dispose() = 0;

		/// @brief 释放信号量。
		/// @param count 要释放的数量。
		virtual void Release(int32_t count) = 0;

		/// @brief 获取信号量。无限等待，永不超时。
		virtual void Acquire() = 0;

		/// @brief 尝试获取信号量。超时后会失败，并返回 false，成功获取信号量后将
		/// 返回 true.
		/// @param timeout 超时时间。
		/// @return
		virtual bool TryAcquire(base::Seconds const &timeout) = 0;
	};
} // namespace base

namespace base
{
	namespace di
	{
		/// @brief 创建一个信号量。
		/// @param initial_count 信号量的初始计数。
		/// @return
		std::shared_ptr<base::ISemaphore> CreateSemaphore(int32_t initial_count);
	} // namespace di
} // namespace base
