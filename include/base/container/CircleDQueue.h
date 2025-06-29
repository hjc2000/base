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
	};

} // namespace base
