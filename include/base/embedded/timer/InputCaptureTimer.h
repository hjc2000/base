#pragma once
#include "input_capture_timer_handle.h"
#include <cstdint>
#include <memory>

namespace base
{
	namespace input_capture_timer
	{
		class InputCaptureTimer
		{
		private:
			std::shared_ptr<base::input_capture_timer::input_capture_timer_handle> _handle;

		public:
			InputCaptureTimer(uint32_t id)
			{
				_handle = base::input_capture_timer::open(id);
			}

			///
			/// @brief 初始化定时器核心。
			///
			/// @param period
			///
			void Initialize(std::chrono::nanoseconds const &period)
			{
				base::input_capture_timer::initialize(*_handle, period);
			}

			///
			/// @brief 计数器一次单调计数的长度。
			///
			/// @note 初始化完定时器的核心后就可以读取本属性了。
			///
			/// @note 对于增计数模式，计数器从 0 计数到 counter_period - 1.
			/// @note 对于减计数模式，计数器从 counter_period - 1 计数到 0.
			/// @note 对于增减计数模式，计数器从 0 计数到 counter_period, 然后递减计数到 0.
			///
			/// @return
			///
			uint32_t CounterPeriod() const
			{
				return base::input_capture_timer::counter_period(*_handle);
			}

			///
			/// @brief 设置自动重装载寄存器的预装载值。定时时间到后，下一个计数周期进行更新。
			///
			/// @note 实现者应实现为高效的直接寄存器操作。
			///
			/// @param value
			///
			void SetCounterPeriodPreloadValue(uint32_t value)
			{
				base::input_capture_timer::set_counter_period_preload_value(*_handle, value);
			}

			///
			/// @brief 配置捕获通道。
			///
			/// @param channel_id
			/// @param edge
			///
			/// @param input_prescaler 对要被捕获的输入信号进行预分频，然后再送入捕获通道。
			/// 例如设置为 2, 则每 2 个输入信号的有效边缘触发一次捕获。
			///
			void ConfigureChannel(uint32_t channel_id,
								  base::input_capture_timer::CaptureEdge edge,
								  uint32_t input_prescaler)
			{
				base::input_capture_timer::configure_channel(*_handle,
															 channel_id,
															 edge,
															 input_prescaler);
			}

			///
			/// @brief 定时时间。
			///
			/// @return
			///
			std::chrono::nanoseconds Period() const
			{
				return base::input_capture_timer::period(*_handle);
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
				base::input_capture_timer::set_period(*_handle, value);
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
				base::input_capture_timer::set_period_elapsed_callback(*_handle, callback);
			}

			///
			/// @brief 设置捕获完成回调。
			///
			/// @param callback
			///
			void SetCaptureCompleteCallback(std::function<void(base::input_capture_timer::CaptureCompleteEventArgs const &)> const &callback)
			{
				base::input_capture_timer::set_capture_complete_callback(*_handle, callback);
			}

			///
			/// @brief 启动核心的定时器计数器。
			///
			void Start()
			{
				base::input_capture_timer::start(*_handle);
			}

			///
			/// @brief 停止核心的定时器计数器。
			///
			///
			void Stop()
			{
				base::input_capture_timer::stop(*_handle);
			}

			///
			/// @brief 启动定时器的指定的捕获输入通道。
			///
			/// @param channel_id
			///
			void StartChannel(uint32_t channel_id)
			{
				base::input_capture_timer::start_channel(*_handle, channel_id);
			}

			///
			/// @brief 启动定时器的所有捕获输入通道。
			///
			void StartAllChannels()
			{
				base::input_capture_timer::start_all_channels(*_handle);
			}

			///
			/// @brief 停止定时器的指定的捕获输入通道。
			///
			/// @param channel_id
			///
			void StopChannel(uint32_t channel_id)
			{
				base::input_capture_timer::stop_channel(*_handle, channel_id);
			}

			///
			/// @brief 停止定时器的所有的捕获输入通道。
			///
			void StopAllChannels()
			{
				base::input_capture_timer::stop_all_channels(*_handle);
			}
		};

	} // namespace input_capture_timer
} // namespace base
