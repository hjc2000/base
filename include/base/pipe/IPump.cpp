#include "IPump.h"
#include "base/task/task.h"

void base::IPump::PumpDataToConsumersAsync(std::shared_ptr<base::CancellationToken> cancellation_token)
{
	auto thread_func = [this, cancellation_token]()
	{
		PumpDataToConsumers(cancellation_token);
	};

	base::task::Run(thread_func);
}
