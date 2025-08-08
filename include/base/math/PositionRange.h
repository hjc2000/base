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
		base::Position<T> _left_top{};
		base::Position<T> _right_bottom{};

	public:
		constexpr PositionRange() = default;

		constexpr PositionRange(base::Position<T> const &left_top, base::Position<T> const &right_bottom)
			: _left_top(left_top),
			  _right_bottom(right_bottom)
		{
		}

		///
		/// @brief 选中范围矩形左上角的点。
		///
		/// @return
		///
		constexpr base::Position<T> LeftTop() const
		{
			return _left_top;
		}

		///
		/// @brief 选中范围矩形右下角的点。
		///
		/// @return
		///
		constexpr base::Position<T> RightBottom() const
		{
			return _right_bottom;
		}
	};

} // namespace base
