#pragma once
#include <array>
#include <cstdint>

namespace base
{
	template <typename T, int32_t Size>
	class CircleDQueue
	{
	private:
		std::array<T, Size> _buffer{};

	public:
	};

} // namespace base
