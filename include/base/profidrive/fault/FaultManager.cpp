#include "FaultManager.h" // IWYU pragma: keep
#include "base/profidrive/fault/fault_menu.h"
#include "base/profidrive/fault/FaultMessage.h"
#include "base/profidrive/fault/pn_diagnostic_channel.h"
#include "base/profidrive/telegram/TelegramInstance.h"
#include "base/profidrive/time.h"
#include <cstdint>

void base::profidrive::FaultManager::AddFaultMessage(uint16_t fault_number, uint16_t fault_value)
{
	if (fault_number == 0)
	{
		return;
	}

	if (_fault_bit_set[fault_number - 1])
	{
		return;
	}

	_fault_bit_set[fault_number - 1] = true;

	{
		base::profidrive::FaultMessage fault_message{base::profidrive::fault_menu::get_fault_message(fault_number)};
		fault_message.SetFaultTime(profidrive_time_in_seconds());
		fault_message.SetFaultValue(fault_value);
		CurrentFaultSituation().AddFaultMessage(fault_message);
	}

	base::profidrive::received_telegram3.Set_ZSW1_Fault(true);
	AddFaultSituationCounter();
	AddFaultMessageCounter();

	pn_diagnostic_channel_add_fault(fault_number,
									static_cast<uint32_t>(base::profidrive::fault_menu::get_fault_message(fault_number).FaultClass()));
}

void base::profidrive::FaultManager::AcknowledgeFaultSituation()
{
	AddFaultMessageCounter();
	_fault_bit_set.reset();
	base::profidrive::received_telegram3.Set_ZSW1_Fault(false);

	for (int i = 0; i < CurrentFaultSituation().FaultMessageCount(); i++)
	{
		pn_diagnostic_channel_remove_fault(CurrentFaultSituation()[i].FaultNumber(),
										   static_cast<uint32_t>(CurrentFaultSituation()[i].FaultClass()));
	}

	// 放入空的故障状况，让当前队列头部的故障状况成为故障历史。
	// 同时从队列尾部退队，让末尾的历史消失。
	_fault_situation_queue.pop_back();
	_fault_situation_queue.push_front(base::profidrive::FaultSituation{});
}

base::profidrive::FaultManager base::profidrive::fault_manager{};
