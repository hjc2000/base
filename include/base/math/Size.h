#pragma once
#include <cstdint>

namespace base
{
	///
	/// @brief UI 中矩形的尺寸。
	///
	///
	class Size
	{
	private:
		int32_t _x = 0;
		int32_t _y = 0;

	public:
		Size() = default;

		Size(int32_t x, int32_t y);

		///
		/// @brief x 轴的尺寸，即宽度。
		///
		/// @return int32_t
		///
		int32_t XSize() const
		{
			return _x;
		}

		///
		/// @brief y 轴的尺寸，即高度。
		///
		/// @return int32_t
		///
		int32_t YSize() const
		{
			return _y;
		}
	};
} // namespace base
