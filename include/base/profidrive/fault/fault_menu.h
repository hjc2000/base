#pragma once
#include "base/profidrive/fault/FaultMessage.h"
#include <cstdint>

namespace base::profidrive
{
	///
	/// @brief 错误菜单需要列出所有可能发生的错误，等到错误发生时，需要添加错误消息，
	/// 可以直接从错误菜单中根据错误号获取到预先初始化的错误消息。这里的错误消息已经设置好了
	/// 错误代码、错误号、错误类、错误文本。剩下错误时间和错误值在运行时根据实际情况设置。
	///
	/// 因为 错误代码、错误号、错误类、错误文本 这些是固定的，不能运行时中改的，所以需要预先定义在
	/// 错误菜单中。错误菜单储存在 .rodata 段。
	///
	namespace fault_menu
	{
		///
		/// @brief 获取错误菜单的大小。即错误菜单中罗列了多少个错误。
		///
		/// @return
		///
		uint16_t get_size();

		///
		/// @brief 根据错误号获取错误菜单中的错误消息。
		///
		/// @param fault_number
		/// @return
		///
		base::profidrive::FaultMessage const &get_fault_message(uint16_t fault_number);

	} // namespace fault_menu
} // namespace base::profidrive
