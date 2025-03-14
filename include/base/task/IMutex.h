#pragma once
#include <base/LockGuard.h>
#include <memory>

namespace base
{
	class IMutex :
		public base::ILock
	{
	public:
		virtual void Lock() = 0;
		virtual void Unlock() = 0;
	};
} // namespace base

/**
 * @brief 外部实现的链接时依赖注入的函数。
 *
 */
namespace base
{
	namespace di
	{
		/**
		 * @brief 创建一个互斥量。
		 *
		 * @return std::shared_ptr<base::IMutex>
		 */
		std::shared_ptr<base::IMutex> CreateIMutex();
	} // namespace di
} // namespace base
