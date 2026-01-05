#pragma once
#include "base/define.h"
#include "base/string/define.h"
#include "task/Mutex.h"

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
		DELETE_COPY_AND_MOVE(UsageStateManager)

		inline static base::task::Mutex _lock{};
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
			base::task::MutexGuard g{_lock};
			CheckUsage();

			_is_used = true;
		}

		~UsageStateManager()
		{
			base::task::MutexGuard g{_lock};
			_is_used = false;
		}
	};
} // namespace base
