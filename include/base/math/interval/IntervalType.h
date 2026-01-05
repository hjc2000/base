#pragma once

namespace base
{
	enum class IntervalType
	{
		///
		/// @brief 闭区间。
		///
		///
		Closed,

		///
		/// @brief 开区间。
		///
		///
		Open,

		///
		/// @brief 左开右闭区间。
		///
		///
		LeftOpenRightClosed,

		///
		/// @brief 左闭右开区间。
		///
		///
		LeftClosedRightOpen,

		///
		/// @brief 左边负无穷，右边开的区间。
		///
		///
		LeftInfiniteRightOpen,

		///
		/// @brief 左边负无穷，右边闭的区间。
		///
		///
		LeftInfiniteRightClosed,

		///
		/// @brief 左边开，右边正无穷的区间。
		///
		///
		LeftOpenRightInfinite,

		///
		/// @brief 左边闭，右边正无穷的区间。
		///
		///
		LeftClosedRightInfinite
	};

} // namespace base
