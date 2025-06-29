#pragma once
#include "base/task/TaskCompletionSignal.h"
#include "base/task/ThreadPool.h"

class base::task::ThreadPool::Task final :
	public base::task::ITask
{
private:
	std::function<void()> _func{};
	base::task::TaskCompletionSignal _signal{false};

public:
	Task(std::function<void()> const &func)
		: _func(func)
	{
	}

	void operator()() noexcept;

	///
	/// @brief 任务已经完成。
	///
	/// @return 已完成会返回 true，否则返回 false.
	///
	virtual bool IsCompleted() const override
	{
		return _signal.IsCompleted();
	}

	///
	/// @brief 等待任务完成。会阻塞当前线程。
	///
	///
	virtual void Wait() override
	{
		_signal.Wait();
	}
};
