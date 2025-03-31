#pragma once

namespace base
{
	namespace led
	{
		///
		/// @brief LED 灯的状态。
		///
		///
		enum class State
		{
			On,
			Off,
		};

		///
		/// @brief 数字 LED。只能开或关，无法调节亮度。
		///
		class IDigitalLed
		{
		public:
			///
			/// @brief 打开 LED.
			///
			///
			virtual void TurnOn() = 0;

			///
			/// @brief 关闭 LED.
			///
			///
			virtual void TurnOff() = 0;

			///
			/// @brief 翻转 LED.
			///
			///
			virtual void Toggle() = 0;

			///
			/// @brief LED 灯的状态。
			///
			/// @return base::led::State
			///
			virtual base::led::State State() = 0;

		}; // class IDigitalLed

	} // namespace led
} // namespace base
