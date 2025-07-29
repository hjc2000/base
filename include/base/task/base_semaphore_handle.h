#pragma once
#include "base/unit/Second.h"
#include <cstdint>
#include <memory>

namespace base
{
	namespace task
	{
		class base_semaphore_handle;

		///
		/// @brief 创造一个基础信号量。
		///
		/// @param initial_count
		/// @return
		///
		std::shared_ptr<base::task::base_semaphore_handle> create_base_semaphore(int32_t initial_count);

		///
		/// @brief 释放信号量。
		///
		/// @param h
		/// @param count 释放的个数。
		///
		void release(base::task::base_semaphore_handle &h, int32_t count);

		///
		/// @brief 在中断中释放信号量。
		///
		/// @param h
		/// @param count 释放的个数。
		///
		void release_from_isr(base::task::base_semaphore_handle &h, int32_t count);

		///
		/// @brief 获取信号量。
		///
		/// @param h
		///
		void acquire(base::task::base_semaphore_handle &h);

		///
		/// @brief 尝试获取信号量。
		///
		/// @param h
		/// @param timeout
		///
		bool try_acquire(base::task::base_semaphore_handle &h, base::unit::Second const &timeout);

	} // namespace task
} // namespace base
