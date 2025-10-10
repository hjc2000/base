#pragma once
#include "base/profidrive/telegram/ReceivedTelegram3.h"
#include "base/profidrive/telegram/SentTelegram3.h"

namespace base::profidrive
{
	extern base::profidrive::SentTelegram3 last_sent_telegram3;
	extern base::profidrive::SentTelegram3 sent_telegram3;
	extern base::profidrive::ReceivedTelegram3 received_telegram3;

} // namespace base::profidrive
