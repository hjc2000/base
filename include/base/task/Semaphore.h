#pragma once
#include "base/define.h"
#include "base/IDisposable.h"
#include "base/string/define.h"
#include "base_semaphore_handle.h"
#include "Mutex.h"
#include <atomic>
#include <cstdint>
#include <memory>

namespace base
{
	///
	/// @brief 信号量。
	///
	///
	class Semaphore :
		public base::IDisposable
	{
	private:
		DELETE_COPY_AND_MOVE(Semaphore)

		std::shared_ptr<base::task::base_semaphore_handle> _base_semaphore_handle;
		base::task::Mutex _lock{};
		std::atomic_bool _disposed = false;
		int32_t volatile _acquire_count = 0;

	public:
		Semaphore(int32_t initial_count)
		{
			_base_semaphore_handle = base::task::create_base_semaphore(initial_count);
		}

		///
		/// @brief 释放本对象的资源。
		///
		/// @note 释放后信号量将不再具有阻塞的能力。再次尝试获取信号量将引发异常。
		///
		virtual void Dispose() override
		{
			if (_disposed)
			{
				return;
			}

			_disposed = true;
			ReleaseAll();
		}

		/* #region 释放信号量 */

		///
		/// @brief 释放信号量。
		///
		/// @param count 要释放的数量。
		///
		void Release(int32_t count)
		{
			base::task::release(*_base_semaphore_handle, count);
		}

		///
		/// @brief 释放 1 个信号量。
		///
		///
		void Release()
		{
			Release(1);
		}

		///
		/// @brief 在中断中释放信号量。
		///
		/// @param count
		///
		void ReleaseFromISR(int32_t count)
		{
			base::task::release_from_isr(*_base_semaphore_handle, count);
		}

		///
		/// @brief 在中断中释放一个信号量。
		///
		///
		void ReleaseFromISR()
		{
			ReleaseFromISR(1);
		}

		///
		/// @brief 释放所有等待的线程。
		///
		///
		void ReleaseAll()
		{
			base::task::MutexGuard g{_lock};
			if (_acquire_count > 0)
			{
				base::task::release(*_base_semaphore_handle, _acquire_count);
			}
		}

		///
		/// @brief 在中断中释放所有等待的线程。
		///
		///
		void ReleaseAllFromISR()
		{
			// 中断中不竞争互斥锁。
			// base::task::MutexGuard g{_lock};
			if (_acquire_count > 0)
			{
				base::task::release_from_isr(*_base_semaphore_handle, _acquire_count);
			}
		}

		/* #endregion */

		/* #region 获取信号量 */

		///
		/// @brief 获取信号量。无限等待，永不超时。
		///
		///
		void Acquire()
		{
			{
				base::task::MutexGuard g{_lock};
				if (_disposed)
				{
					throw base::ObjectDisposedException{CODE_POS_STR + "已经释放，无法获取。"};
				}

				_acquire_count = _acquire_count + 1;
			}

			base::task::acquire(*_base_semaphore_handle);

			{
				base::task::MutexGuard g{_lock};
				_acquire_count = _acquire_count - 1;
				if (_disposed)
				{
					throw base::ObjectDisposedException{CODE_POS_STR + "已经释放，无法获取。"};
				}
			}
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
		bool TryAcquire(base::unit::Second const &timeout)
		{
			{
				base::task::MutexGuard g{_lock};
				if (_disposed)
				{
					throw base::ObjectDisposedException{CODE_POS_STR + "已经释放，无法获取。"};
				}

				_acquire_count = _acquire_count + 1;
			}

			bool result = base::task::try_acquire(*_base_semaphore_handle, timeout);

			{
				base::task::MutexGuard g{_lock};
				_acquire_count = _acquire_count - 1;
				if (_disposed)
				{
					throw base::ObjectDisposedException{CODE_POS_STR + "已经释放，无法获取。"};
				}
			}

			return result;
		}

		/* #endregion */

		///
		/// @brief 当前正在等待获取信号量的线程数。
		///
		/// @return int32_t
		///
		int32_t AcquireCount() const
		{
			return _acquire_count;
		}
	};
} // namespace base
