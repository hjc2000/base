#include "IPump.h"
#include "base/string/define.h"
#include "base/task/task.h"

std::shared_ptr<base::task::ITask> base::IPump::PumpDataToConsumersAsync(std::shared_ptr<base::CancellationToken> cancellation_token)
{
	auto thread_func = [this, cancellation_token]()
	{
		try
		{
			PumpDataToConsumers(cancellation_token);
		}
		catch (std::exception const &e)
		{
			throw std::runtime_error{CODE_POS_STR + e.what()};
		}
		catch (...)
		{
			throw std::runtime_error{CODE_POS_STR + "未知的异常。"};
		}
	};

	return base::task::run(thread_func);
}
