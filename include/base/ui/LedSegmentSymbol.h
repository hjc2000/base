#pragma once

namespace base::ui
{
	///
	/// @brief 数码管显示的符号。
	///
	enum class LedSegmentSymbol
	{
		///
		/// @brief 空。每一段 LED 灯都熄灭。
		///
		Space,

		Number_0,
		Number_1,
		Number_2,
		Number_3,
		Number_4,

		///
		/// @brief 数字 5 或大写字母 S.
		///
		Number_5_or_S,

		Number_6,
		Number_7,
		Number_8,
		Number_9,

		///
		/// @brief 小数点。
		///
		/// @note 7 段数码管没有小数点。8 段数码管才有。
		///
		DigitalDot,

		A,
		B,
		C,
		c,
		d,
		E,
		F,
		G,
		H,
		i,
		J,
		L,
		n,
		o,
		P,
		q,
		r,
		t,
		U_or_V,
		u_or_v,
		y,

		///
		/// @brief 位于上方的横杠。
		///
		UpperDash,

		///
		/// @brief 位于中间的横杠。
		///
		MiddleDash,

		///
		/// @brief 位于下方的横杠。
		///
		LowerDash,

		///
		/// @brief 位于上方的 2 条横杠。
		///
		UpperTwoDash,

		///
		/// @brief 位于下方的 2 条横杠。
		///
		LowerTwoDash,

		///
		/// @brief 3 条横杠。
		///
		ThreeDash,
	};

} // namespace base::ui
