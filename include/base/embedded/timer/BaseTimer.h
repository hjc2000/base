#pragma once
#include "base_timer_handle.h"
#include <cstdint>
#include <memory>

namespace base
{
	namespace base_timer
	{
		class BaseTimer
		{
		private:
			std::shared_ptr<base::base_timer::base_timer_handle> _handle;

		public:
			BaseTimer(uint32_t id)
			{
				_handle = base::base_timer::open(id);
			}

			///
			/// @brief 初始化定时器。
			///
			/// @param period
			///
			void Initialize(std::chrono::nanoseconds const &period)
			{
				base::base_timer::initialize(*_handle, period);
			}

			///
			/// @brief 定时时间。
			///
			/// @return
			///
			std::chrono::nanoseconds Period()
			{
				return base::base_timer::period(*_handle);
			}

			///
			/// @brief 设置定时时间。
			///
			/// @note 允许运行时实时修改定时时间。
			///
			/// @note 此函数要实现为能够在定时时间到的回调中被调用，因此实现者需要避免会出现
			/// 死锁的实现方式。
			///
			/// @param value
			///
			void SetPeriod(std::chrono::nanoseconds const &value)
			{
				base::base_timer::set_period(*_handle, value);
			}

			///
			/// @brief 设置定时时间到的回调。
			///
			/// @note 单片机平台直接实现为在中断中回调，不要太早使用线程和信号量进行封装。
			/// 到时候在这个基础上设计一个包装类，包装直接使用中断进行回调的定时器，使用信号量
			/// 释放被阻塞的任务去执行定时任务。
			///
			/// @warning 实现者实现时需要注意在修改回调函数的时候禁用定时器中断。
			///
			/// @param callback
			///
			void SetPeriodElapsedCallback(std::function<void()> const &callback)
			{
				base::base_timer::set_period_elapsed_callback(*_handle, callback);
			}

			///
			/// @brief 启动定时器。
			///
			/// @param self
			///
			void Start()
			{
				base::base_timer::start(*_handle);
			}

			///
			/// @brief 停止定时器。
			///
			/// @param self
			///
			void Stop()
			{
				base::base_timer::stop(*_handle);
			}
		};

	} // namespace base_timer
} // namespace base
