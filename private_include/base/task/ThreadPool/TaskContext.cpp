#include "TaskContext.h"
#include "base/Console.h"
#include "base/string/define.h"
#include <exception>

void base::task::ThreadPool::Task::operator()() noexcept
{
	base::task::TaskCompletionSignalGuard g{_signal};
	if (_func == nullptr)
	{
		return;
	}

	try
	{
		_func();
	}
	catch (std::exception const &e)
	{
		base::console.WriteError(CODE_POS_STR + e.what());
	}
	catch (...)
	{
		base::console.WriteError(CODE_POS_STR + "未知异常。");
	}
}
