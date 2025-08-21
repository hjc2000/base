#pragma once
#include <chrono>
#include <cstdint>
#include <functional>
#include <memory>

namespace base
{
	namespace base_timer
	{
		class base_timer_handle;

		///
		/// @brief 打开定时器。
		///
		/// @param id
		/// @return
		///
		std::shared_ptr<base::base_timer::base_timer_handle> open(uint32_t id);

		///
		/// @brief 初始化定时器。
		///
		/// @param self
		/// @param period
		///
		void initialize(base::base_timer::base_timer_handle &self,
						std::chrono::nanoseconds const &period);

		///
		/// @brief 定时时间。
		///
		/// @param self
		/// @return
		///
		std::chrono::nanoseconds period(base::base_timer::base_timer_handle &self);

		///
		/// @brief 设置定时时间。
		///
		/// @note 允许运行时实时修改定时时间。
		///
		/// @param self
		/// @param period
		///
		void set_period(base::base_timer::base_timer_handle &self,
						std::chrono::nanoseconds const &period);

		///
		/// @brief 设置定时时间到的回调。
		///
		/// @warning 实现者实现时需要注意在修改回调函数的时候禁用定时器中断。
		///
		/// @param self
		/// @param callback
		///
		void set_period_elapsed_callback(base::base_timer::base_timer_handle &self,
										 std::function<void()> callback);

		///
		/// @brief 启动定时器。
		///
		/// @param self
		///
		void start(base::base_timer::base_timer_handle &self);

		///
		/// @brief 停止定时器。
		///
		/// @param self
		///
		void stop(base::base_timer::base_timer_handle &self);

	} // namespace base_timer
} // namespace base
