#pragma once
#include "base/define.h"
#include "base/string/define.h"
#include <atomic>
#include <stdexcept>

namespace base
{
	class CancellationTokenSource;
	class CancellationToken;

	bool is_cancellation_requested(std::shared_ptr<CancellationToken> const &cancellation_token);
	void throw_if_cancellation_is_requested(std::shared_ptr<CancellationToken> const &cancellation_token);

	///
	/// @brief 取消令牌
	///
	class CancellationToken final
	{
	private:
		friend class CancellationTokenSource;
		friend bool is_cancellation_requested(std::shared_ptr<CancellationToken> const &cancellation_token);
		friend void throw_if_cancellation_is_requested(std::shared_ptr<CancellationToken> const &cancellation_token);

		CancellationToken() = default;
		DELETE_COPY_AND_MOVE(CancellationToken)

		std::atomic_bool _is_cancellation_request = false;

		void Cancel()
		{
			_is_cancellation_request = true;
		}

		///
		/// @brief 是否需要取消。
		///
		/// @return 为 true 表示已经请求取消了，为 false 表示没有请求取消。
		///
		bool IsCancellationRequested() const
		{
			return _is_cancellation_request;
		}

		///
		/// @brief 如果任务被取消了就抛出异常。
		///
		/// @note 使用本方法可以从深层嵌套中退出，快速结束当前任务。
		///
		void ThrowIfCancellationIsRequested() const
		{
			if (IsCancellationRequested())
			{
				throw std::runtime_error{CODE_POS_STR + "任务取消。"};
			}
		}
	};

	///
	/// @brief 是否需要取消。
	///
	/// @param cancellation_token
	///
	/// @return 返回 true 表示已经请求取消了，返回 false 表示没有请求取消。
	///
	inline bool is_cancellation_requested(std::shared_ptr<CancellationToken> const &cancellation_token)
	{
		if (cancellation_token == nullptr)
		{
			return false;
		}

		return cancellation_token->IsCancellationRequested();
	}

	///
	/// @brief 如果任务被取消了就抛出异常。
	///
	/// @note 使用本方法可以从深层嵌套中退出，快速结束当前任务。
	///
	/// @param cancellation_token
	///
	inline void throw_if_cancellation_is_requested(std::shared_ptr<CancellationToken> const &cancellation_token)
	{
		if (cancellation_token == nullptr)
		{
			return;
		}

		cancellation_token->ThrowIfCancellationIsRequested();
	}

} // namespace base
