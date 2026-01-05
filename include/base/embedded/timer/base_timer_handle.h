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
		/// @note 此函数要实现为能够在定时时间到的回调中被调用，因此实现者需要避免会出现
		/// 死锁的实现方式。
		///
		/// @param self
		/// @param value
		///
		void set_period(base::base_timer::base_timer_handle &self,
						std::chrono::nanoseconds const &value);

		///
		/// @brief 设置定时时间到的回调。
		///
		/// @note 单片机平台直接实现为在中断中回调，不要太早使用线程和信号量进行封装。
		/// 到时候在这个基础上设计一个包装类，包装直接使用中断进行回调的定时器，使用信号量
		/// 释放被阻塞的任务去执行定时任务。
		///
		/// @warning 实现者实现时需要注意在修改回调函数的时候禁用定时器中断。
		///
		/// @param self
		/// @param callback
		///
		void set_period_elapsed_callback(base::base_timer::base_timer_handle &self,
										 std::function<void()> const &callback);

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
