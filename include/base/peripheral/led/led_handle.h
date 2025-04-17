#pragma once
#include "base/define.h"
#include "base/peripheral/led/parameter.h"
#include "base/ui/Color.h"
#include <memory>

namespace base
{
	namespace led
	{
		class led_handle;

		/* #region open */

		///
		/// @brief 根据 LED 的 ID 打开 LED.
		///
		/// @param led_id
		/// @return std::shared_ptr<led_handle>
		///
		std::shared_ptr<led_handle> open(int led_id);

		///
		/// @brief 根据 LED 的颜色打开 LED.
		///
		/// @param color
		/// @return std::shared_ptr<led_handle>
		///
		std::shared_ptr<led_handle> open(base::ui::Color color);

		/* #endregion */

		/* #region 控制 LED 开关 */

		///
		/// @brief 打开 LED.
		///
		/// @param h
		///
		void turn_on(base::led::led_handle &h);

		///
		/// @brief 关闭 LED.
		///
		/// @param h
		///
		void turn_off(base::led::led_handle &h);

		///
		/// @brief 翻转 LED.
		///
		/// @param h
		///
		void toggle(base::led::led_handle &h);

		/* #endregion */

		///
		/// @brief 获取 LED 灯的状态。
		///
		/// @param h
		/// @return base::led::State
		///
		base::led::State state(base::led::led_handle &h);

		///
		/// @brief 设置 LED 灯的状态。
		///
		/// @param h
		/// @param value
		///
		IMPLEMENTED
		void set_state(base::led::led_handle &h, base::led::State value);

	} // namespace led
} // namespace base
