#pragma once
#include "base/unit/Second.h"
#include <memory>

namespace base
{
	namespace task
	{
		///
		/// @brief 二进制信号量句柄。
		///
		///
		class binary_semaphore_handle;

		///
		/// @brief 创建一个二进制信号量。
		///
		/// @param initial_release 二进制信号量初始时是否已经处于已释放的状态。
		/// 传入 true 表示已释放，传入 false 表示未释放。
		///
		/// @return
		///
		std::shared_ptr<base::task::binary_semaphore_handle> create_binary_semaphore(bool initial_release);

		///
		/// @brief 释放二进制信号量。
		///
		/// @param h
		///
		void release(base::task::binary_semaphore_handle &h);

		///
		/// @brief 从中断中释放二进制信号量。
		///
		/// @param h
		///
		void release_from_isr(base::task::binary_semaphore_handle &h);

		///
		/// @brief 获取二进制信号量。
		///
		/// @param h
		///
		void acquire(base::task::binary_semaphore_handle &h);

		///
		/// @brief 尝试获取二进制信号量。
		///
		/// @param h
		/// @param timeout
		///
		bool try_acquire(base::task::binary_semaphore_handle &h, base::unit::Second const &timeout);

	} // namespace task
} // namespace base
