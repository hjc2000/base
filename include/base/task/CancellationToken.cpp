#include "CancellationToken.h"
#include "base/LockGuard.h"

using namespace std;
using namespace base;

std::shared_ptr<base::CancellationToken> CancellationToken::_none_cancellation_token{new base::CancellationToken{}};

void CancellationToken::Cancel()
{
	/* 只有取消过一次，即调用本函数一次后，_is_cancellation_request
	 * 才会为 true。
	 * _is_cancellation_request 为 true 表示已经取消过一次了，
	 * 这时候就不要重复取消了
	 */
	if (_is_cancellation_request)
	{
		// 先检查一次，有机会不竞争锁直接能够返回
		return;
	}

	base::LockGuard l{*_lock};

	if (_is_cancellation_request)
	{
		// 竞争锁后再次确认
		return;
	}

	_is_cancellation_request = true;

	// 执行列表中的每一个委托
	for (auto const &pair : _delegates)
	{
		pair.second();
	}
}

std::shared_ptr<CancellationToken> base::CancellationToken::None()
{
	return _none_cancellation_token;
}

bool CancellationToken::IsCancellationRequested() const
{
	return _is_cancellation_request;
}

uint64_t CancellationToken::Register(std::function<void(void)> func)
{
	if (this == None().get())
	{
		throw std::runtime_error{"不要对 None 调用 Register 方法"};
	}

	base::LockGuard l{*_lock};
	uint64_t current_id = _id++;
	_delegates[current_id] = func;
	return current_id;
}

void CancellationToken::Unregister(uint64_t id)
{
	if (this == None().get())
	{
		return;
	}

	base::LockGuard l{*_lock};
	_delegates.erase(id);
}
