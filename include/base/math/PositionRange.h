#pragma once
#include "Position.h"

namespace base
{
	///
	/// @brief 由 2 个点定义的位置范围。例如 (x1, y1) , (x2, y2) 指示的范围
	/// 就是从 x1 到 x2 ，从 y1 到 y2 之间围成的矩形。
	///
	/// (x1, y1) , (x2, y2) 这两个点也算在范围内。
	///
	template <typename T>
	class PositionRange
	{
	private:
		base::Position<T> _start;
		base::Position<T> _end;

	public:
		constexpr PositionRange() = default;

		constexpr PositionRange(base::Position<T> const &start, base::Position<T> const &end)
			: _start(start),
			  _end(end)
		{
		}

		constexpr base::Position<T> Start() const
		{
			return _start;
		}

		constexpr base::Position<T> End() const
		{
			return _end;
		}
	};
} // namespace base
