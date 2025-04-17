#pragma once
#include "base/container/IDictionary.h"
#include "base/peripheral/led/parameter.h"

namespace base
{
	namespace led
	{
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
			virtual base::led::State State() const = 0;

			///
			/// @brief 设置 LED 灯的状态。
			///
			/// @param value
			///
			void SetState(base::led::State value)
			{
				if (value == base::led::State::On)
				{
					TurnOn();
				}
				else
				{
					TurnOff();
				}
			}

		}; // class IDigitalLed

		///
		/// @brief 数字 LED 灯集合。
		///
		/// @return
		///
		base::IDictionary<std::string, base::led::IDigitalLed *> const &DigitalLedCollection();

		/* #region 各种颜色的 LED */

		// 这里的 LED 灯有的话就实现这些函数，没有的话就不实现。

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
