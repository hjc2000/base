#pragma once
#include "base/string/define.h"
#include "base/task/Mutex.h"
#include "gpio_parameter.h"
#include <array>
#include <bitset>
#include <cstdint>

namespace base
{
	namespace gpio
	{
		///
		/// @brief GPIO 引脚使用状态管理器。
		///
		///
		template <uint32_t PortQuantity, uint32_t PinQuantityPerPort>
		class GpioPinUsageStateManager
		{
		private:
			inline static std::array<std::bitset<PinQuantityPerPort>, PortQuantity> _states{};
			inline static base::task::Mutex _lock{};

			base::gpio::PortEnum _port{};
			uint32_t _pin{};

		public:
			GpioPinUsageStateManager(base::gpio::PortEnum port, uint32_t pin)
				: _port(port),
				  _pin(pin)
			{
				if (static_cast<uint32_t>(port) >= PortQuantity)
				{
					throw std::invalid_argument{CODE_POS_STR + "端口号超出范围。"};
				}

				if (static_cast<uint32_t>(pin) >= PinQuantityPerPort)
				{
					throw std::invalid_argument{CODE_POS_STR + "引脚号超出范围。"};
				}

				base::task::MutexGuard g{_lock};

				// 这里只能在加锁的情况下检查，不能使用 2 不检查锁定来加速。因为 bitset 的位
				// 不是原子的，多线程读写会冲突。
				if (_states[static_cast<int>(port)][pin])
				{
					throw std::runtime_error{CODE_POS_STR + PinName(port, pin) + "已经占用了，无法再次占用。"};
				}

				_states[static_cast<int>(port)][pin] = true;
			}

			~GpioPinUsageStateManager()
			{
				base::task::MutexGuard g{_lock};
				_states[static_cast<int>(_port)][_pin] = false;
			}
		};

	} // namespace gpio
} // namespace base
