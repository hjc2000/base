#pragma once
#include "base/define.h"
#include "base/embedded/led/parameter.h"
#include "base/math/Fraction.h"
#include "base/ui/Color.h"
#include <cstdint>
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
		/// @return
		///
		std::shared_ptr<base::led::led_handle> open(uint32_t led_id);

		///
		/// @brief 根据 LED 的颜色打开 LED.
		///
		/// @param color
		/// @return
		///
		std::shared_ptr<base::led::led_handle> open(base::ui::Color color);

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

		/* #region LED 灯属性 */

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

		///
		/// @brief 获取 LED 灯得分亮度。
		///
		/// @param h
		/// @return 是个分数，表示当前亮度是额定亮度的多少倍。
		///
		base::Fraction brightness(base::led::led_handle &h);

		///
		/// @brief 设置亮度。
		///
		/// @param h
		/// @param value 是个分数，表示亮度是额定亮度的多少倍。
		///
		void set_brightness(base::led::led_handle &h, base::Fraction const &value);

		/* #endregion */

		///
		/// @brief 点亮错误 LED.
		///
		/// @note 发生错误时可以调用本函数，点亮一个表示错误的 LED 灯。
		/// 这个 LED 灯对象可以借助 GlobalLedBar 来保存。
		///
		void turn_on_error_led();

	} // namespace led
} // namespace base
