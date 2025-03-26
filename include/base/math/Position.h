#pragma once
#include <cstdint>

namespace base
{
	///
	/// @brief 坐标位置。
	///
	///
	class Position
	{
	private:
		int64_t _x{};
		int64_t _y{};

	public:
		Position(int64_t x, int64_t y);

		int64_t X() const
		{
			return _x;
		}

		void SetX(int64_t value)
		{
			_x = value;
		}

		int64_t Y() const
		{
			return _y;
		}

		void SetY(int64_t value)
		{
			_y = value;
		}
	};
} // namespace base
