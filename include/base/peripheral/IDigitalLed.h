#pragma once

namespace base
{
	///
	/// @brief 数字 LED。只能开或关，无法调节亮度。
	///
	class IDigitalLed
	{
	public:
		///
		/// @brief 打开 LED.
		///
		///
		virtual void TurnOn() = 0;

		///
		/// @brief 关闭 LED.
		///
		///
		virtual void TurnOff() = 0;

		///
		/// @brief 翻转 LED.
		///
		///
		virtual void Toggle() = 0;

		///
		/// @brief 需要 CanRead 返回 true，本方法才有效。
		///
		/// @return
		///
		virtual bool IsTurnedOn() = 0;

		///
		/// @brief 需要 CanRead 返回 true，本方法才有效。
		///
		/// @return
		///
		virtual bool IsTurnedOff() = 0;
	};
} // namespace base
