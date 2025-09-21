#pragma once
#include <cstdint>
#include <memory>
#include <string>

namespace base
{
	namespace usb_pcd
	{
		/* #region 参数类 */

		enum class PhyType
		{
			///
			/// @brief 低引脚数外置 PHY.
			///
			ULPI,

			///
			/// @brief 高引脚数外置 PHY.
			///
			UTMI,

			///
			/// @brief 内置 PHY.
			///
			Embedded,
		};

		/* #endregion */

		class usb_fs_pcd_handle;

		std::shared_ptr<base::usb_pcd::usb_fs_pcd_handle> open(uint32_t id);

		void initialize_as_full_speed_mode_device(base::usb_pcd::usb_fs_pcd_handle &self,
												  std::string const &clock_source_name,
												  uint32_t divider,
												  base::usb_pcd::PhyType phy_type);

		///
		/// @brief 底层初始化。
		///
		/// @note 例如 GPIO 引脚复用功能的初始化。这种初始化是板级的，即和具体的电路板
		/// 相关，外设功能可以复用到不同的引脚上，这里只负责驱动外设，不处理板级的配置。
		///
		/// @param id
		///
		void msp_initialize(uint32_t id);

	} // namespace usb_pcd
} // namespace base
