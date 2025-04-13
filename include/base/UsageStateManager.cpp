#include "UsageStateManager.h"
#include "base/string/define.h"

void base::UsageStateManager::CheckUsage()
{
	if (_is_used)
	{
		throw std::runtime_error{CODE_POS_STR + "已经被占用了。"};
	}
}

void base::UsageStateManager::SetAsUsed()
{
	// 双重检查锁定
	CheckUsage();
	base::LockGuard g{*_lock};
	CheckUsage();

	_is_used = true;
}

void base::UsageStateManager::SetAsUnused()
{
	base::LockGuard g{*_lock};
	_is_used = false;
}
