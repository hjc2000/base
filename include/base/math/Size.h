#pragma once
#include <cstdint>

namespace base
{
	class Size
	{
	private:
		int32_t _x = 0;
		int32_t _y = 0;

	public:
		Size() = default;

		Size(int32_t x, int32_t y);

		int32_t XSize() const
		{
			return _x;
		}

		int32_t YSize() const
		{
			return _y;
		}
	};
} // namespace base
