#pragma once

namespace base
{
	namespace core
	{
		///
		/// @brief 执行初始化。需要在 main 的开头调用。
		///
		/// @note 需要实现为幂等的。
		///
		void initialize();

		///
		/// @brief 执行复位重启。就好像重新上电一样，只不过没有实际断电。
		/// 也等同于通过复位引脚复位。
		///
		void reset();

	} // namespace core
} // namespace base
