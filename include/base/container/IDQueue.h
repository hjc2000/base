#pragma once
#include <cstdint>

namespace base
{
	template <typename T>
	class IDQueue
	{
	public:
		virtual int32_t Count() const = 0;

		virtual void PushBack(T const &obj) = 0;

		virtual T PopBack() = 0;

		virtual bool TryPopBack(T &out) = 0;

		virtual void PushFront(T const &obj) = 0;

		virtual T PopFront() = 0;

		virtual bool TryPopFront(T &out) = 0;
	};

} // namespace base
