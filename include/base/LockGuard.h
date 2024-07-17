#pragma once

namespace base
{
	/// @brief 锁接口
	class ILock
	{
	public:
		virtual void Lock() = 0;
		virtual void Unlock() = 0;
	};

	/// @brief 锁守卫
	class LockGuard
	{
	private:
		base::ILock &_lock;

	public:
		LockGuard(base::ILock &lock)
			: _lock(lock)
		{
			_lock.Lock();
		}

		~LockGuard()
		{
			_lock.Unlock();
		}
	};
}
