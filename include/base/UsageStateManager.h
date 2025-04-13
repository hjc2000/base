#pragma once
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

		void CheckUsage();

	public:
		///
		/// @brief 设置为使用。
		///
		/// @note 如果本来已经是使用中了，则会抛出异常。
		///
		///
		void SetAsUsed();

		///
		/// @brief 设置为未使用。
		///
		///
		void SetAsUnused();
	};
} // namespace base
