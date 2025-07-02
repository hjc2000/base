#pragma once
#include "base/profidrive/fault/FaultSituation.h"
#include "base/profidrive/telegram/TelegramInstance.h"
#include <bitset>
#include <cstdint>
#include <deque>

namespace base
{
	namespace profidrive
	{
		class FaultManager
		{
		private:
			static constexpr int32_t _fault_situation_queue_size = 8;

			///
			/// @brief 故障状况队列。
			///
			/// @note 出现新的故障状况则放入队列头部。
			///
			/// @note 队列头部的故障状况是当前正发生的故障状况，其他的都是历史。
			/// 当故障状况被确认后，则往头部放入一个空的故障状况，让刚才的头部故障状况成为
			/// 故障历史。
			///
			///
			std::deque<base::profidrive::FaultSituation> _fault_situation_queue{};

			std::bitset<128> _fault_bit_set{};

			///
			/// @brief 故障消息计数器。
			///
			/// @note 故障缓冲器每变化一次，就要递增本计数器。所以本计数器相当于故障缓冲器的
			/// 版本号。
			///
			/// @note 只能递增，不能递减。只能通过复位故障缓冲器来清 0.
			///
			/// @note fault message counter PNU944 (mandatory)
			///
			///
			uint16_t _fault_message_counter = 0;

			///
			/// @brief 故障状态计数器。
			///
			/// @note 自上一次复位故障缓冲器后发生的故障的总数。只递增，不会因为错误确认而递减。
			/// 只能通过复位来清 0.
			///
			///
			uint16_t _fault_situation_counter = 0;

			///
			/// @brief 当前的故障状况。
			///
			/// @return
			///
			base::profidrive::FaultSituation &CurrentFaultSituation()
			{
				return _fault_situation_queue.front();
			}

			void AddFaultSituationCounter()
			{
				if (_fault_situation_counter < UINT16_MAX)
				{
					_fault_situation_counter++;
				}
			}

			void AddFaultMessageCounter()
			{
				if (_fault_message_counter == UINT16_MAX)
				{
					// 达到最大值了，再加 1 就要溢出变成 0 了，但是又不允许变成 0, 所以要
					// 回绕到 1.
					_fault_message_counter = 1;
				}
				else
				{
					_fault_message_counter++;
				}
			}

		public:
			FaultManager()
			{
				ResetFaultBuffer();
			}

			static constexpr int32_t FaultSituationQueueSize()
			{
				return _fault_situation_queue_size;
			}

			uint16_t FaultMessageCounter() const
			{
				return _fault_message_counter;
			}

			uint16_t FaultSituationCounter() const
			{
				return _fault_situation_counter;
			}

			///
			/// @brief 重置整个故障缓冲器。
			///
			///
			void ResetFaultBuffer()
			{
				_fault_bit_set.reset();
				_fault_situation_queue.clear();

				for (int i = 0; i < _fault_situation_queue_size; i++)
				{
					_fault_situation_queue.push_front(base::profidrive::FaultSituation{});
				}

				_fault_message_counter = 0;
				_fault_situation_counter = 0;
				base::profidrive::received_telegram3.Set_ZSW1_Fault(false);
			}

			///
			/// @brief 向当前的故障状况中添加一条错误消息。
			///
			/// @param fault_number 故障号。
			/// 	@note 内部唯一地表示一个错误，相当于内部错误代码，但是是连续的整型，方便用来作为数组索引。
			///
			/// @param fault_value 故障值。
			/// 	@note 例如收到了非法参数，可以把这个非法参数作为故障值。
			/// 	@note 或者电压过高，可以把这个电压值作为故障值。
			///
			void AddFaultMessage(uint16_t fault_number, uint16_t fault_value);

			///
			/// @brief 确认当前的故障状况。
			///
			/// @note profidrive 无法单独确认一条故障消息，只能把当前故障状况全部确认，即把故障状况里的
			/// 所有故障消息都确认。确认后，如果某些故障还存在，可以在新的故障状况中继续添加故障消息。
			///
			/// @note PLC 通过 STW1 的故障确认位的上升沿请求进行故障确认。
			///
			///
			void AcknowledgeFaultSituation();

			///
			/// @brief 索引某个故障状况。
			///
			/// @param index
			/// @return
			///
			base ::profidrive::FaultSituation &operator[](int32_t index)
			{
				return _fault_situation_queue[index];
			}

			///
			/// @brief 索引某个故障状况。
			///
			/// @param index
			/// @return
			///
			base::profidrive::FaultSituation const &operator[](int32_t index) const
			{
				return _fault_situation_queue[index];
			}

			/* #region 迭代 */

			auto begin()
			{
				return _fault_situation_queue.begin();
			}

			auto end()
			{
				return _fault_situation_queue.end();
			}

			auto begin() const
			{
				return _fault_situation_queue.begin();
			}

			auto end() const
			{
				return _fault_situation_queue.end();
			}

			/* #endregion */
		};

		extern FaultManager fault_manager;

	} // namespace profidrive
} // namespace base
