#pragma once
#include "base/Placement.h"
#include <cstdint>

namespace base
{
	///
	/// @brief 队列接口。
	///
	///
	template <typename T>
	class IQueue
	{
	public:
		///
		/// @brief 队列中元素个数。
		///
		/// @return
		///
		virtual int64_t Count() const = 0;

		///
		/// @brief 退队。队列为空会抛出异常。
		///
		/// @return
		///
		virtual T Dequeue() = 0;

		///
		/// @brief 尝试退队。
		///
		virtual void TryDequeue(base::Placement<T> &placement) = 0;

		///
		/// @brief 入队。
		///
		/// @param obj
		///
		virtual void Enqueue(T const &obj) = 0;

		///
		/// @brief 清空队列。
		///
		virtual void Clear() = 0;
	};

} // namespace base
