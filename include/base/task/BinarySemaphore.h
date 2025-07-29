#pragma once
#include "binary_semaphore_handle.h"
#include <memory>

namespace base
{
	namespace task
	{
		///
		/// @brief 二进制信号量。
		///
		///
		class BinarySemaphore
		{
		private:
			std::shared_ptr<base::task::binary_semaphore_handle> _handle;

		public:
			///
			/// @brief 构造二进制信号量。
			///
			/// @param initial_release 二进制信号量初始时是否已经处于已释放的状态。
			/// 传入 true 表示已释放，传入 false 表示未释放。
			///
			BinarySemaphore(bool initial_release);

			///
			/// @brief 释放信号量。
			///
			void Release()
			{
				base::task::release(*_handle);
			}

			///
			/// @brief 从中断中释放二进制信号量。
			///
			///
			void ReleaseFromIsr()
			{
				base::task::release_from_isr(*_handle);
			}

			///
			/// @brief 获取信号量。无限等待，永不超时。
			///
			void Acquire()
			{
				base::task::acquire(*_handle);
			}

			///
			/// @brief 尝试获取信号量。超时后会失败，并返回 false，成功获取信号量后将
			/// 返回 true.
			/// @param timeout 超时时间。
			/// @return
			///
			bool TryAcquire(base::unit::Second const &timeout)
			{
				return base::task::try_acquire(*_handle, timeout);
			}
		};

	} // namespace task
} // namespace base
