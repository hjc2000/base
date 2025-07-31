#pragma once
#include <cstdint>

namespace base
{
	template <typename T>
	class IDeque
	{
	public:
		virtual ~IDeque() = default;

		///
		/// @brief 队列中当前元素的数量。
		///
		/// @return
		///
		virtual int64_t Count() const = 0;

		///
		/// @brief 从队列末端入队。
		///
		/// @param obj
		///
		virtual void PushBack(T const &obj) = 0;

		///
		/// @brief 从队列末端退队。
		///
		/// @return
		///
		virtual T PopBack() = 0;

		///
		/// @brief 尝试从队列末端退队。
		///
		/// @param out
		/// @return
		///
		virtual bool TryPopBack(T &out) = 0;

		///
		/// @brief 从队列前端入队。
		///
		/// @param obj
		///
		virtual void PushFront(T const &obj) = 0;

		///
		/// @brief 从队列前端退队。
		///
		/// @return
		///
		virtual T PopFront() = 0;

		///
		/// @brief 尝试从队列前端退队。
		///
		/// @param out
		/// @return
		///
		virtual bool TryPopFront(T &out) = 0;

		///
		/// @brief 清空队列。
		///
		///
		virtual void Clear() = 0;
	};

} // namespace base
