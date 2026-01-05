#pragma once

namespace base
{
	namespace bit
	{
		///
		/// @brief 浮点数值类型。
		///
		///
		enum class FloatValueType
		{
			///
			/// @brief 规格化数。
			///
			///
			Normalized,

			///
			/// @brief 非规格化数。
			///
			///
			Denormalized,

			///
			/// @brief 不是一个数。
			///
			///
			NaN,

			///
			/// @brief 正无穷。
			///
			///
			PositiveInfinite,

			///
			/// @brief 负无穷。
			///
			///
			NegativeInfinite,
		};

	} // namespace bit
} // namespace base
