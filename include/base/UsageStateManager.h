#pragma once
#include "base/string/define.h"
#include "base/task/IMutex.h"

namespace base
{
	///
	/// @brief 使用状态管理器。
	///
	///
	class UsageStateManager
	{
	private:
		std::shared_ptr<base::IMutex> _lock = base::CreateIMutex();
		bool _is_used = false;

		void CheckUsage()
		{
			if (_is_used)
			{
				throw std::runtime_error{CODE_POS_STR + "已经被占用了。"};
			}
		}

	public:
		///
		/// @brief 设置为使用。
		///
		/// @note 如果本来已经是使用中了，则会抛出异常。
		///
		///
		void SetAsUsed()
		{
			// 双重检查锁定
			CheckUsage();
			base::LockGuard g{*_lock};
			CheckUsage();

			_is_used = true;
		}

		///
		/// @brief 设置为未使用。
		///
		///
		void SetAsUnused()
		{
			base::LockGuard g{*_lock};
			_is_used = false;
		}
	};
} // namespace base
