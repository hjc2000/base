#pragma once

namespace base
{
	///
	/// @brief 锁接口
	///
	class ILock
	{
	public:
		virtual void Lock() = 0;
		virtual void Unlock() = 0;
	};

	///
	/// @brief 锁守卫。
	/// @note 构造时加锁，析构时解锁。
	///
	class LockGuard final
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

	///
	/// @brief 解锁守卫。
	/// @note 构造时解锁，析构时加锁。与 LockGuard 相反。
	///
	class UnlockGuard final
	{
	private:
		base::ILock &_lock;

	public:
		UnlockGuard(base::ILock &lock)
			: _lock(lock)
		{
			_lock.Unlock();
		}

		~UnlockGuard()
		{
			_lock.Lock();
		}
	};
} // namespace base
