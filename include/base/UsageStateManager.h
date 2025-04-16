#pragma once
#include "base/string/define.h"
#include "base/task/IMutex.h"

namespace base
{
	///
	/// @brief 使用状态管理器。
	///
	///
	template <typename T>
	class UsageStateManager
	{
	private:
		inline static std::shared_ptr<base::IMutex> _lock = base::CreateIMutex();
		inline static bool _is_used = false;

		void CheckUsage()
		{
			if (_is_used)
			{
				throw std::runtime_error{CODE_POS_STR + "已经被占用了。"};
			}
		}

	public:
		UsageStateManager()
		{
			// 双重检查锁定
			CheckUsage();
			base::LockGuard g{*_lock};
			CheckUsage();

			_is_used = true;
		}

		~UsageStateManager()
		{
			base::LockGuard g{*_lock};
			_is_used = false;
		}
	};
} // namespace base
