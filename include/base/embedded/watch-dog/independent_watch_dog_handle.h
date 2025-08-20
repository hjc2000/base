#pragma once
#include <chrono>
#include <cstdint>
#include <memory>

namespace base
{
	namespace independent_watch_dog
	{
		///
		/// @brief 独立看门狗句柄。
		///
		class independent_watch_dog_handle;

		///
		/// @brief 打开独立看门狗。
		///
		/// @param id
		/// @return
		///
		std::shared_ptr<base::independent_watch_dog::independent_watch_dog_handle> open(uint32_t id);

		///
		/// @brief 初始化独立看门狗。
		///
		/// @param self
		/// @param timeout
		///
		void initialize(base::independent_watch_dog::independent_watch_dog_handle &self,
						std::chrono::milliseconds const &timeout);

		///
		/// @brief 喂狗。
		///
		/// @param self
		///
		void feed(base::independent_watch_dog::independent_watch_dog_handle &self);

		///
		/// @brief 看门狗超时时间。
		///
		/// @param self
		/// @return
		///
		std::chrono::milliseconds timeout(base::independent_watch_dog::independent_watch_dog_handle &self);

	} // namespace independent_watch_dog
} // namespace base
