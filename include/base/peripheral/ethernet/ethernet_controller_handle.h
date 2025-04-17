#pragma once
#include <cstdint>
#include <memory>

namespace base
{
	namespace ethernet
	{
		class ethernet_controller_handle;

		/* #region open */

		///
		/// @brief 打开以太网控制器。
		///
		/// @note 如果只有一个以太网控制器，可以使用本函数打开。
		///
		/// @return
		///
		std::shared_ptr<base::ethernet::ethernet_controller_handle> open();

		///
		/// @brief 根据以太网控制器的 ID 打开以太网控制器。
		///
		/// @param id 以太网控制器的 ID.
		/// @return
		///
		std::shared_ptr<base::ethernet::ethernet_controller_handle> open(uint32_t id);

		/* #endregion */

	} // namespace ethernet
} // namespace base
