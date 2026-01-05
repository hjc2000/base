#pragma once
#include "base/define.h"
#include "base/task/CancellationToken.h"

namespace base
{
	///
	/// @brief 取消令牌源
	///
	class CancellationTokenSource final
	{
	private:
		std::shared_ptr<CancellationToken> _token{new CancellationToken{}};

		DELETE_COPY_AND_MOVE(CancellationTokenSource)

	public:
		CancellationTokenSource() = default;

		///
		/// @brief 检查任务是否已经取消了。
		///
		/// @return 为 true 表示已经请求取消了，为 false 表示没有请求取消。
		///
		bool IsCancellationRequested() const
		{
			return _token->IsCancellationRequested();
		}

		///
		/// @brief 取消令牌
		///
		/// @return
		///
		std::shared_ptr<CancellationToken> Token() const
		{
			return _token;
		}

		///
		/// @brief 取消任务。
		///
		///
		void Cancel()
		{
			_token->Cancel();
		}
	};

} // namespace base
