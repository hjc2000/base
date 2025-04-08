#pragma once
#include "base/container/IDictionary.h"

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

		///
		/// @brief 数字 LED 灯集合。
		///
		/// @return
		///
		base::IDictionary<std::string, base::led::IDigitalLed *> const &DigitalLedCollection();

		/* #region 各种颜色的 LED */

		///
		/// @brief 红色 LED.
		///
		/// @return base::led::IDigitalLed&
		///
		base::led::IDigitalLed &RedDigitalLed();

		///
		/// @brief 绿色 LED.
		///
		/// @return base::led::IDigitalLed&
		///
		base::led::IDigitalLed &GreenDigitalLed();

		///
		/// @brief 蓝色 LED.
		///
		/// @return base::led::IDigitalLed&
		///
		base::led::IDigitalLed &BlueDigitalLed();

		/* #endregion */

	} // namespace led
} // namespace base
