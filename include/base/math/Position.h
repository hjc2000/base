#pragma once
#include <array>
#include <cstdint>

namespace base
{
	///
	/// @brief 坐标位置。
	///
	/// @note 不同地方的坐标系不同。
	/// 	@li 数学中的坐标系：向右为 x 轴正方向，向上为 y 轴正方向。
	/// 	@li 屏幕像素坐标系：原点位于屏幕左上角顶点处，向右为 x 轴正方向，向下为 y 轴正方向。
	/// 	@li 表格坐标系：最左上角的单元格为坐标原点，向右为 x 轴正方向，向下为 y 轴正方向。
	///
	///
	class Position
	{
	private:
		int64_t _x{};
		int64_t _y{};

	public:
		///
		/// @brief 无参构造。构造出来的是坐标原点。
		///
		///
		Position() = default;

		///
		/// @brief 构造函数。
		///
		/// @param x
		/// @param y
		///
		Position(int64_t x, int64_t y)
			: _x(x),
			  _y(y)
		{
		}

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

		bool operator==(base::Position const &another) const
		{
			std::array<int64_t, 2> arr{_x, _y};
			std::array<int64_t, 2> another_arr{another._x, another._y};
			return arr == another_arr;
		}

		bool operator<(base::Position const &another) const
		{
			std::array<int64_t, 2> arr{_x, _y};
			std::array<int64_t, 2> another_arr{another._x, another._y};
			return arr < another_arr;
		}

		bool operator>(base::Position const &another) const
		{
			std::array<int64_t, 2> arr{_x, _y};
			std::array<int64_t, 2> another_arr{another._x, another._y};
			return arr > another_arr;
		}

		bool operator<=(base::Position const &another) const
		{
			std::array<int64_t, 2> arr{_x, _y};
			std::array<int64_t, 2> another_arr{another._x, another._y};
			return arr <= another_arr;
		}

		bool operator>=(base::Position const &another) const
		{
			std::array<int64_t, 2> arr{_x, _y};
			std::array<int64_t, 2> another_arr{another._x, another._y};
			return arr >= another_arr;
		}
	};
} // namespace base
