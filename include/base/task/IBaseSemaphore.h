#pragma once
#include "base/unit/Seconds.h"
#include <cstdint>
#include <memory>

namespace base
{
	///
	/// @brief 基础功能的信号量接口。
	///
	///
	class IBaseSemaphore
	{
	public:
		///
		/// @brief 释放信号量。
		///
		/// @param count 要释放的数量。
		///
		virtual void Release(int32_t count) = 0;

		///
		/// @brief 在中断中释放信号量。
		///
		/// @param count
		///
		virtual void ReleaseFromISR(int32_t count) = 0;

		///
		/// @brief 获取信号量。无限等待，永不超时。
		///
		///
		virtual void Acquire() = 0;

		///
		/// @brief 尝试获取信号量。超时后会失败，并返回 false，成功获取信号量后将
		/// 返回 true.
		///
		/// @param timeout 超时时间。
		///
		/// @return true 获取信号量成功。
		/// @return false 获取信号量失败。
		///
		virtual bool TryAcquire(base::Seconds const &timeout) = 0;
	};

	///
	/// @brief 创建一个基础信号量。
	///
	/// @param initial_count 信号量的初始计数。
	///
	/// @return std::shared_ptr<base::IBaseSemaphore>
	///
	std::shared_ptr<base::IBaseSemaphore> CreateBaseSemaphore(int32_t initial_count);

} // namespace base
