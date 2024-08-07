#pragma once
#include <stdint.h>

namespace base
{
	/// @brief 队列接口
	/// @tparam T
	template <typename T>
	class IQueue
	{
	public:
		virtual ~IQueue() = default;

		virtual int32_t Count() const = 0;
		virtual T Dequeue() = 0;
		virtual bool TryDequeue(T &out) = 0;
		virtual void Enqueue(T obj) = 0;
		virtual void Clear() = 0;
	};
}
