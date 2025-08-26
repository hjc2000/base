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

			void Initialize(std::chrono::nanoseconds const &period)
			{
				base::input_capture_timer::initialize(*_handle, period);
			}

			uint32_t CounterPeriod() const
			{
				return base::input_capture_timer::counter_period(*_handle);
			}

			void ConfigureChannel(uint32_t channel_id,
								  base::input_capture_timer::CaptureEdge edge,
								  uint32_t input_prescaler)
			{
				base::input_capture_timer::configure_channel(*_handle,
															 channel_id,
															 edge,
															 input_prescaler);
			}

			std::chrono::nanoseconds Period() const
			{
				return base::input_capture_timer::period(*_handle);
			}

			void SetPeriod(std::chrono::nanoseconds const &value)
			{
				base::input_capture_timer::set_period(*_handle, value);
			}

			void SetPeriodElapsedCallback(std::function<void()> const &callback)
			{
				base::input_capture_timer::set_period_elapsed_callback(*_handle, callback);
			}

			void SetCaptureCompleteCallback(std::function<void(base::input_capture_timer::CaptureCompleteEventArgs const &)> const &callback)
			{
				base::input_capture_timer::set_capture_complete_callback(*_handle, callback);
			}

			void Start(uint32_t channel_id)
			{
				base::input_capture_timer::start(*_handle, channel_id);
			}

			void StartAllChannels()
			{
				base::input_capture_timer::start_all_channels(*_handle);
			}

			void Stop(uint32_t channel_id)
			{
				base::input_capture_timer::stop(*_handle, channel_id);
			}

			void StopAllChannels()
			{
				base::input_capture_timer::stop_all_channels(*_handle);
			}
		};

	} // namespace input_capture_timer
} // namespace base
