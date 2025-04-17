#pragma once
#include "base/container/iterator/IEnumerable.h"
#include "base/container/List.h"
#include "base/define.h"
#include "base/peripheral/led/Led.h"
#include "base/string/define.h"
#include <cstddef>
#include <cstdint>
#include <stdexcept>

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

			void Add(base::IEnumerable<base::led::Led> const &leds)
			{
				_leds.Add(leds);
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
	} // namespace led
} // namespace base
