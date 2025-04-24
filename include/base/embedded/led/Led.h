#pragma once
#include "base/embedded/led/led_handle.h"
#include <memory>

namespace base
{
	namespace led
	{
		class Led
		{
		private:
			std::shared_ptr<base::led::led_handle> _handle;

		public:
			/* #region 构造函数 */

			Led(uint32_t led_id)
			{
				_handle = base::led::open(led_id);
			}

			Led(base::ui::Color color)
			{
				_handle = base::led::open(color);
			}

			/* #endregion */

			/* #region 控制 LED 开关 */

			///
			/// @brief 打开 LED.
			///
			///
			void TurnOn()
			{
				base::led::turn_on(*_handle);
			}

			///
			/// @brief 关闭 LED.
			///
			///
			void TurnOff()
			{
				base::led::turn_off(*_handle);
			}

			///
			/// @brief 翻转 LED.
			///
			///
			void Toggle()
			{
				base::led::toggle(*_handle);
			}

			/* #endregion */

			/* #region LED 灯属性 */

			///
			/// @brief 获取 LED 灯的状态。
			///
			/// @return base::led::State
			///
			base::led::State State() const
			{
				return base::led::state(*_handle);
			}

			///
			/// @brief 设置 LED 灯的状态。
			///
			/// @param value
			///
			void SetState(base::led::State value)
			{
				base::led::set_state(*_handle, value);
			}

			///
			/// @brief 获取 LED 灯得分亮度。
			///
			/// @return 是个分数，表示当前亮度是额定亮度的多少倍。
			///
			base::Fraction Brightness() const
			{
				return base::led::brightness(*_handle);
			}

			///
			/// @brief 设置亮度。
			///
			/// @param value 是个分数，表示亮度是额定亮度的多少倍。
			///
			void SetBrightness(base::Fraction const &value)
			{
				base::led::set_brightness(*_handle, value);
			}

			/* #endregion */
		};
	} // namespace led
} // namespace base
