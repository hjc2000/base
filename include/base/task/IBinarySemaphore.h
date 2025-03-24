#pragma once
#include "base/unit/Seconds.h"
#include <memory>

namespace base
{
	///
	/// @brief 二进制信号量接口
	///
	class IBinarySemaphore
	{
	public:
		///
		/// @brief 释放信号量。
		///
		virtual void Release() = 0;

		///
		/// @brief 在中断中释放信号量。
		///
		virtual void ReleaseFromISR() = 0;

		///
		/// @brief 获取信号量。无限等待，永不超时。
		///
		virtual void Acquire() = 0;

		///
		/// @brief 尝试获取信号量。超时后会失败，并返回 false，成功获取信号量后将
		/// 返回 true.
		/// @param timeout 超时时间。
		/// @return
		///
		virtual bool TryAcquire(base::Seconds const &timeout) = 0;
	};

	///
	/// @brief 创建一个二进制信号量。
	///
	/// @param initial_release 传入 true 则二进制信号量初始时被释放，既可以直接获取一次不被阻塞。
	/// 传入 false 阻塞二进制信号量初始时不被释放，直接进行一次获取将被阻塞。
	///
	/// @return std::shared_ptr<base::IBinarySemaphore>
	///
	std::shared_ptr<base::IBinarySemaphore> CreateIBinarySemaphore(bool initial_release);

} // namespace base
