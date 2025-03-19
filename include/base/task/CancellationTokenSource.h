#pragma once
#include <base/task/CancellationToken.h>

namespace base
{
	///
	/// @brief 取消令牌源
	///
	///
	class CancellationTokenSource final
	{
	private:
		std::shared_ptr<CancellationToken> _token{new CancellationToken{}};

	public:
		///
		/// @brief 检查任务是否已经取消了。
		///
		/// @return true 已经取消。
		/// @return false 还没取消。
		///
		bool IsCancellationRequested() const;

		///
		/// @brief 取消令牌
		///
		/// @return std::shared_ptr<CancellationToken>
		///
		std::shared_ptr<CancellationToken> Token() const;

		///
		/// @brief 取消任务。
		///
		///
		void Cancel();
	};
} // namespace base
