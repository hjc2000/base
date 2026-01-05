#pragma once
#include <chrono>
#include <cstdint>
#include <functional>
#include <memory>

namespace base
{
	namespace input_capture_timer
	{
		class input_capture_timer_handle;

		/* #region 参数类 */

		enum CaptureEdge
		{
			///
			/// @brief 上升沿捕获。
			///
			RisingEdge,

			///
			/// @brief 下降沿捕获。
			///
			FallenEdge,

			///
			/// @brief 上升沿和下降沿都捕获。
			///
			BothEdge,
		};

		class CaptureCompleteEventArgs
		{
		private:
			uint32_t _capture_value{};

		public:
			constexpr CaptureCompleteEventArgs() = default;

			constexpr CaptureCompleteEventArgs(uint32_t capture_value)
			{
				_capture_value = capture_value;
			}

			constexpr uint32_t CaptureValue() const
			{
				return _capture_value;
			}

			constexpr void SetCaptureValue(uint32_t value)
			{
				_capture_value = value;
			}
		};

		/* #endregion */

		std::shared_ptr<base::input_capture_timer::input_capture_timer_handle> open(uint32_t id);

		///
		/// @brief 初始化定时器核心。
		///
		/// @param self
		/// @param period
		///
		void initialize(base::input_capture_timer::input_capture_timer_handle &self,
						std::chrono::nanoseconds const &period);

		///
		/// @brief 计数器一次单调计数的长度。
		///
		/// @note 初始化完定时器的核心后就可以读取本属性了。
		///
		/// @note 对于增计数模式，计数器从 0 计数到 counter_period - 1.
		/// @note 对于减计数模式，计数器从 counter_period - 1 计数到 0.
		/// @note 对于增减计数模式，计数器从 0 计数到 counter_period, 然后递减计数到 0.
		///
		/// @param self
		/// @return
		///
		uint32_t counter_period(base::input_capture_timer::input_capture_timer_handle &self);

		///
		/// @brief 设置自动重装载寄存器的预装载值。定时时间到后，下一个计数周期进行更新。
		///
		/// @note 实现者应实现为高效的直接寄存器操作。
		///
		/// @param self
		/// @param value
		///
		void set_counter_period_preload_value(base::input_capture_timer::input_capture_timer_handle &self, uint32_t value);

		///
		/// @brief 配置捕获通道。
		///
		/// @param self
		/// @param channel_id
		/// @param edge
		///
		/// @param input_prescaler 对要被捕获的输入信号进行预分频，然后再送入捕获通道。
		/// 例如设置为 2, 则每 2 个输入信号的有效边缘触发一次捕获。
		///
		void configure_channel(base::input_capture_timer::input_capture_timer_handle &self,
							   uint32_t channel_id,
							   base::input_capture_timer::CaptureEdge edge,
							   uint32_t input_prescaler);

		///
		/// @brief 定时时间。
		///
		/// @param self
		/// @return
		///
		std::chrono::nanoseconds period(base::input_capture_timer::input_capture_timer_handle &self);

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
		void set_period(base::input_capture_timer::input_capture_timer_handle &self,
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
		void set_period_elapsed_callback(base::input_capture_timer::input_capture_timer_handle &self,
										 std::function<void()> const &callback);

		///
		/// @brief 设置捕获完成回调。
		///
		/// @param self
		/// @param callback
		///
		void set_capture_complete_callback(base::input_capture_timer::input_capture_timer_handle &self,
										   std::function<void(base::input_capture_timer::CaptureCompleteEventArgs const &)> const &callback);

		///
		/// @brief 启动核心的定时器计数器。
		///
		/// @param self
		///
		void start(base::input_capture_timer::input_capture_timer_handle &self);

		///
		/// @brief 停止核心的定时器计数器。
		///
		/// @param self
		///
		void stop(base::input_capture_timer::input_capture_timer_handle &self);

		///
		/// @brief 启动定时器的指定的捕获输入通道。
		///
		/// @param self
		/// @param channel_id
		///
		void start_channel(base::input_capture_timer::input_capture_timer_handle &self, uint32_t channel_id);

		///
		/// @brief 启动定时器的所有捕获输入通道。
		///
		/// @param self
		///
		void start_all_channels(base::input_capture_timer::input_capture_timer_handle &self);

		///
		/// @brief 停止定时器的指定的捕获输入通道。
		///
		/// @param self
		/// @param channel_id
		///
		void stop_channel(base::input_capture_timer::input_capture_timer_handle &self, uint32_t channel_id);

		///
		/// @brief 停止定时器的所有的捕获输入通道。
		///
		/// @param self
		///
		void stop_all_channels(base::input_capture_timer::input_capture_timer_handle &self);

		///
		/// @brief 输入捕获定时器的底层初始化回调。
		///
		/// @param id
		///
		void msp_initialize_callback(uint32_t id);

	} // namespace input_capture_timer
} // namespace base
