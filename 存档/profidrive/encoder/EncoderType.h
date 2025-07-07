#pragma once
#include <cstdint>

namespace base
{
	namespace profidrive
	{
		enum class EncoderType : uint8_t
		{
			///
			/// @brief 旋转编码器。
			///
			///
			Rotary = 0,

			///
			/// @brief 线性编码器。
			///
			///
			Linear = 1,
		};

	} // namespace profidrive
} // namespace base
