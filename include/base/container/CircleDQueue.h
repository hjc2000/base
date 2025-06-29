#pragma once
#include "base/math/Counter.h"
#include "IDQueue.h"
#include <array>
#include <cstdint>

namespace base
{
	template <typename T, int32_t Size>
		requires(Size > 0)
	class CircleDQueue :
		base::IDQueue<T>
	{
	private:
		std::array<T, Size> _buffer{};
		base::Counter<uint32_t> _begin{0, Size};
		base::Counter<uint32_t> _end{0, Size};

	public:
		///
		/// @brief 队列中当前元素的数量。
		///
		/// @return
		///
		virtual int32_t Count() const = 0;

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
	};

} // namespace base
