#pragma once
#include "base/container/iterator/IEnumerable.h"
#include "base/container/List.h"
#include "base/define.h"
#include "base/embedded/led/Led.h"
#include "base/string/define.h"
#include <array>
#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <vector>

namespace base
{
	namespace led
	{
		///
		/// @brief 灯条。
		///
		///
		class LedBar
		{
		private:
			DELETE_COPY_AND_MOVE(LedBar)

			base::List<base::led::Led> _leds{};

		public:
			LedBar() = default;

			/* #region Add */

			void Add(base::IEnumerable<base::led::Led> const &leds)
			{
				_leds.Add(leds);
			}

			void Add(base::IEnumerable<base::led::Led const> const &leds)
			{
				_leds.Add(leds);
			}

			void Add(std::vector<base::led::Led> const &leds)
			{
				_leds.Add(leds);
			}

			template <int32_t Count>
			void Add(std::array<base::led::Led, Count> const &leds)
			{
				_leds.Add(leds);
			}

			/* #endregion */

			///
			/// @brief 灯条中 LED 灯的数量。
			///
			/// @return
			///
			int32_t Count() const
			{
				return _leds.Count();
			}

			/* #region operator[] */

			base::led::Led &operator[](int32_t index)
			{
				try
				{
					return _leds[index];
				}
				catch (std::exception const &e)
				{
					throw std::runtime_error{CODE_POS_STR + e.what()};
				}
				catch (...)
				{
					throw std::runtime_error{CODE_POS_STR + "未知的异常。"};
				}
			}

			base::led::Led const &operator[](size_t index) const
			{
				try
				{
					return _leds[index];
				}
				catch (std::exception const &e)
				{
					throw std::runtime_error{CODE_POS_STR + e.what()};
				}
				catch (...)
				{
					throw std::runtime_error{CODE_POS_STR + "未知的异常。"};
				}
			}

			/* #endregion */
		};

		///
		/// @brief 全局的 LED 灯条。可以向这里添加 LED 灯。
		///
		/// @return
		///
		base::led::LedBar &led_bar();

	} // namespace led
} // namespace base
