#include "IPump.h"

void base::IPump::PumpDataToConsumersAsync(std::shared_ptr<base::CancellationToken> cancellation_token)
{
	auto thread_func = [this, cancellation_token]()
	{
		try
		{
			PumpDataToConsumers(cancellation_token);
		}
		catch (const std::exception &e)
		{
			std::cerr << e.what() << '\n';
			std::cerr << "PumpDataToConsumersAsync 启动执行的线程函数发生异常，线程退出" << std::endl;
		}
		catch (...)
		{
			std::cerr << "PumpDataToConsumersAsync 启动执行的线程函数发生未知异常，线程退出" << std::endl;
		}
	};
	std::thread{thread_func}.detach();
}
