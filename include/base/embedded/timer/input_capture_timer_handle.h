#pragma once
#include <chrono>
#include <cstdint>
#include <memory>

namespace base
{
	namespace input_capture_timer
	{
		class input_capture_timer_handle;

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
		/// @brief 配置捕获通道。
		///
		/// @param self
		/// @param edge
		/// @param input_prescaler 对要被捕获的输入信号进行预分频，然后再送入捕获通道。
		///
		void configure_channel(base::input_capture_timer::input_capture_timer_handle &self,
							   base::input_capture_timer::CaptureEdge edge,
							   uint32_t input_prescaler);

		///
		/// @brief 输入捕获定时器的底层初始化回调。
		///
		/// @param id
		///
		void msp_initialize_callback(uint32_t id);

	} // namespace input_capture_timer
} // namespace base
