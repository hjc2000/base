#include "CancellationToken.h"
#include "base/LockGuard.h"
#include <base/string/define.h>
#include <stdexcept>

/**
 * @brief 取消注册令牌。用于取消注册通过 CancellationToken::Register 方法注册的委托。
 *
 */
class base::CancellationToken::UnregisterToken
{
private:
	friend class CancellationToken;
	uint64_t const _id{};
	bool _used = false;

private:
	UnregisterToken(uint64_t id)
		: _id(id)
	{
	}

	UnregisterToken(UnregisterToken const &o) = delete;
	UnregisterToken &operator=(UnregisterToken const &o) = delete;
};

std::shared_ptr<base::CancellationToken> base::CancellationToken::_none_cancellation_token{new base::CancellationToken{}};

void base::CancellationToken::Cancel()
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

std::shared_ptr<base::CancellationToken> base::CancellationToken::None()
{
	return _none_cancellation_token;
}

bool base::CancellationToken::IsCancellationRequested() const
{
	return _is_cancellation_request;
}

std::shared_ptr<base::CancellationToken::UnregisterToken> base::CancellationToken::Register(std::function<void(void)> const &func)
{
	if (this == None().get())
	{
		throw std::runtime_error{"不要对 None 调用 Register 方法"};
	}

	base::LockGuard l{*_lock};
	uint64_t current_id = _id++;
	_delegates[current_id] = func;
	return std::shared_ptr<base::CancellationToken::UnregisterToken>{new base::CancellationToken::UnregisterToken{current_id}};
}

void base::CancellationToken::Unregister(std::shared_ptr<base::CancellationToken::UnregisterToken> const &token)
{
	if (this == None().get())
	{
		return;
	}

	if (token == nullptr)
	{
		throw std::invalid_argument{CODE_POS_STR + "禁止传入空指针。"};
	}

	base::LockGuard l{*_lock};
	if (token->_used)
	{
		return;
	}

	_delegates.erase(token->_id);
	token->_used = true;
}
