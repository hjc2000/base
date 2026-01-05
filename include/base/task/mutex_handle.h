#pragma once
#include <memory>

namespace base
{
	namespace task
	{
		class mutex_handle;

		///
		/// @brief 创建一个互斥锁。
		///
		/// @return
		///
		std::shared_ptr<base::task::mutex_handle> create_mutex();

		///
		/// @brief 加锁。
		///
		/// @param h
		///
		void lock(base::task::mutex_handle &h);

		///
		/// @brief 解锁。
		///
		/// @param h
		///
		void unlock(base::task::mutex_handle &h);

	} // namespace task
} // namespace base
