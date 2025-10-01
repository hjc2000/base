#pragma once
#include "base/embedded/usb/fs-device-pcd/callback-args/DataInStageCallbackArgs.h"
#include "base/embedded/usb/fs-device-pcd/callback-args/DataOutStageCallbackArgs.h"
#include "base/embedded/usb/fs-device-pcd/callback-args/IsoInIncompleteCallbackArgs.h"
#include "base/embedded/usb/fs-device-pcd/callback-args/IsoOutIncompleteCallbackArgs.h"
#include "base/embedded/usb/fs-device-pcd/callback-args/SetupStageCallbackArgs.h"
#include "PhyType.h"
#include <cstdint>
#include <functional>
#include <memory>

namespace base::usb::fs_device_pcd
{
	class usb_fs_device_pcd_handle;

	std::shared_ptr<base::usb::fs_device_pcd::usb_fs_device_pcd_handle> open(uint32_t id);

	void initialize(base::usb::fs_device_pcd::usb_fs_device_pcd_handle &self,
					base::usb::PhyType phy_type);

	/* #region 注册回调 */

	void set_sof_callback(base::usb::fs_device_pcd::usb_fs_device_pcd_handle &self,
						  std::function<void()> const &callback);

	void set_setup_stage_callback(base::usb::fs_device_pcd::usb_fs_device_pcd_handle &self,
								  std::function<void(base::usb::fs_device_pcd::SetupStageCallbackArgs const &)> const &callback);

	void set_reset_callback(base::usb::fs_device_pcd::usb_fs_device_pcd_handle &self,
							std::function<void()> const &callback);

	///
	/// @brief 设置收到主机发来的挂起请求时的回调。
	///
	/// @note 回调中做好自定义的工作后要调用 suspend 函数来挂起 USB 硬件。
	///
	/// @param self
	/// @param callback
	///
	void set_suspend_callback(base::usb::fs_device_pcd::usb_fs_device_pcd_handle &self,
							  std::function<void()> const &callback);

	void set_resume_callback(base::usb::fs_device_pcd::usb_fs_device_pcd_handle &self,
							 std::function<void()> const &callback);

	void set_connect_callback(base::usb::fs_device_pcd::usb_fs_device_pcd_handle &self,
							  std::function<void()> const &callback);

	void set_disconnect_callback(base::usb::fs_device_pcd::usb_fs_device_pcd_handle &self,
								 std::function<void()> const &callback);

	///
	/// @brief 设置收到来自主机的输出数据时的回调。
	///
	/// @param self
	/// @param callback
	///
	void set_data_out_stage_callback(base::usb::fs_device_pcd::usb_fs_device_pcd_handle &self,
									 std::function<void(base::usb::fs_device_pcd::DataOutStageCallbackArgs const &)> const &callback);

	///
	/// @brief 设置主机请求读取数据时触发的回调。
	///
	/// @param self
	/// @param callback
	///
	void set_data_in_stage_callback(base::usb::fs_device_pcd::usb_fs_device_pcd_handle &self,
									std::function<void(base::usb::fs_device_pcd::DataInStageCallbackArgs const &)> const &callback);

	///
	/// @brief 等时传输中，如果主机输出的数据没有及时被设备接收，就会触发此回调。
	///
	/// @param self
	/// @param callback
	///
	void set_iso_out_incomplete_callback(base::usb::fs_device_pcd::usb_fs_device_pcd_handle &self,
										 std::function<void(base::usb::fs_device_pcd::IsoOutIncompleteCallbackArgs const &)> const &callback);

	///
	/// @brief 等时传输中，主机没有及时取走输入数据，就会触发此回调。
	///
	/// @param self
	/// @param callback
	///
	void set_iso_in_incomplete_callback(base::usb::fs_device_pcd::usb_fs_device_pcd_handle &self,
										std::function<void(base::usb::fs_device_pcd::IsoInIncompleteCallbackArgs const &)> const &callback);

	/* #endregion */

	///
	/// @brief 启动 USB 设备。
	///
	/// @param self
	///
	void start(base::usb::fs_device_pcd::usb_fs_device_pcd_handle &self);

	///
	/// @brief 挂起 USB 设备。
	///
	/// @param self
	///
	void suspend(base::usb::fs_device_pcd::usb_fs_device_pcd_handle &self);

	///
	/// @brief 恢复 USB 设备。
	///
	/// @param self
	///
	void resume(base::usb::fs_device_pcd::usb_fs_device_pcd_handle &self);

	///
	/// @brief 底层初始化。
	///
	/// @note 例如 GPIO 引脚复用功能的初始化。这种初始化是板级的，即和具体的电路板
	/// 相关，外设功能可以复用到不同的引脚上，这里只负责驱动外设，不处理板级的配置。
	///
	/// @param id
	///
	void msp_initialize(uint32_t id);

} // namespace base::usb::fs_device_pcd
