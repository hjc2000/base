#pragma once
#include "PhyType.h"
#include <cstdint>
#include <functional>
#include <memory>

namespace base
{
	namespace usb
	{
		namespace fs_pcd
		{
			class usb_fs_pcd_handle;

			std::shared_ptr<base::usb::fs_pcd::usb_fs_pcd_handle> open(uint32_t id);

			void initialize_as_device(base::usb::fs_pcd::usb_fs_pcd_handle &self,
									  base::usb::PhyType phy_type);

			/* #region 注册回调 */

			void set_sof_callback(base::usb::fs_pcd::usb_fs_pcd_handle &self,
								  std::function<void()> const &callback);

			void set_setup_stage_callback(base::usb::fs_pcd::usb_fs_pcd_handle &self,
										  std::function<void()> const &callback);

			/* #endregion */

			///
			/// @brief 底层初始化。
			///
			/// @note 例如 GPIO 引脚复用功能的初始化。这种初始化是板级的，即和具体的电路板
			/// 相关，外设功能可以复用到不同的引脚上，这里只负责驱动外设，不处理板级的配置。
			///
			/// @param id
			///
			void msp_initialize(uint32_t id);

		} // namespace fs_pcd

	} // namespace usb
} // namespace base
