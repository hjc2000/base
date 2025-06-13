#pragma once
#include <array>

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
	template <typename T>
	class Position
	{
	private:
		T _x{};
		T _y{};

	public:
		///
		/// @brief 无参构造。构造出来的是坐标原点。
		///
		///
		constexpr Position() = default;

		///
		/// @brief 构造函数。
		///
		/// @param x
		/// @param y
		///
		constexpr Position(T x, T y)
			: _x(x),
			  _y(y)
		{
		}

		///
		/// @brief 从其他类型的坐标构造。
		///
		/// @param another
		/// @return
		///
		template <typename another_type>
		constexpr explicit Position(Position<another_type> const &another)
			: _x(T{another._x}),
			  _y(T{another._y})
		{
		}

		constexpr T X() const
		{
			return _x;
		}

		constexpr void SetX(T value)
		{
			_x = value;
		}

		constexpr T Y() const
		{
			return _y;
		}

		constexpr void SetY(T value)
		{
			_y = value;
		}

		constexpr bool operator==(base::Position<T> const &another) const
		{
			std::array<T, 2> arr{_x, _y};
			std::array<T, 2> another_arr{another._x, another._y};
			return arr == another_arr;
		}

		constexpr bool operator<(base::Position<T> const &another) const
		{
			std::array<T, 2> arr{_x, _y};
			std::array<T, 2> another_arr{another._x, another._y};
			return arr < another_arr;
		}

		constexpr bool operator>(base::Position<T> const &another) const
		{
			std::array<T, 2> arr{_x, _y};
			std::array<T, 2> another_arr{another._x, another._y};
			return arr > another_arr;
		}

		constexpr bool operator<=(base::Position<T> const &another) const
		{
			std::array<T, 2> arr{_x, _y};
			std::array<T, 2> another_arr{another._x, another._y};
			return arr <= another_arr;
		}

		constexpr bool operator>=(base::Position<T> const &another) const
		{
			std::array<T, 2> arr{_x, _y};
			std::array<T, 2> another_arr{another._x, another._y};
			return arr >= another_arr;
		}
	};
} // namespace base
