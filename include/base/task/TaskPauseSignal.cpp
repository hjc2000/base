#include "TaskPauseSignal.h"
#include "base/IDisposable.h"
#include "base/string/define.h"

base::TaskPauseSignal::~TaskPauseSignal()
{
	Dispose();
}

void base::TaskPauseSignal::Dispose()
{
	if (_disposed)
	{
		return;
	}

	_disposed = true;
	_block_thread_signal.Dispose();
	_response_signal.Dispose();
}

void base::TaskPauseSignal::Request(bool pause)
{
	if (_disposed)
	{
		throw base::ObjectDisposedException{CODE_POS_STR + "已经释放，无法使用。"};
	}

	if (pause)
	{
		_response_signal.Reset();

		// 先重置 _response_signal, 然后设置 _should_pause, 因为一旦设置 _should_pause,
		// 后台线程随时可能检测到。
		//
		// 如果不这么做，而是先设置 _should_pause 再重置 _response_signal, 就有可能发生
		// 这边还没重置 _response_signal, 后台线程就先设置 _response_signal 的结果了，
		// 然后这边又接着重置 _response_signal, 然后等待结果，导致陷入死锁。
		_should_pause = true;

		// 等待回应。后台线程暂停后会设置结果。
		_response_signal.Wait();
	}
	else
	{
		_should_pause = false;

		// 设置用来阻塞后台线程的信号的结果，让后台线程恢复执行。
		_block_thread_signal.SetResult();
	}
}

void base::TaskPauseSignal::Response()
{
	if (_disposed)
	{
		throw base::ObjectDisposedException{CODE_POS_STR + "已经释放，无法使用。"};
	}

	if (_should_pause)
	{
		// 重置，准备暂停后台线程。
		_block_thread_signal.Reset();

		// 收到请求了，等会儿马上暂停。
		_response_signal.SetResult();

		// 暂停。
		_block_thread_signal.Wait();
	}
}

/* #region TaskPauseSignalGuard */

base::TaskPauseSignalGuard::TaskPauseSignalGuard(base::TaskPauseSignal &signal)
	: _signal(signal)
{
}

base::TaskPauseSignalGuard::~TaskPauseSignalGuard()
{
	// 因为线程退出后，不再能够暂停，也无法再响应暂停请求，所以为了防止 UI 线程
	// 再次发出暂停请求，需要使用 Dispose 而不是使用 Response 来响应一次暂停
	// 请求。
	_signal.Dispose();
}

/* #endregion */
