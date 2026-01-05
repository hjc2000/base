#pragma once
#include "base/embedded/Slot.h"
#include "usb_fs_device_pcd_handle.h"
#include <cstdint>
#include <memory>

namespace base::usb::fs_device_pcd
{
	class UsbFsDevicePcd
	{
	private:
		std::shared_ptr<base::usb::fs_device_pcd::usb_fs_device_pcd_handle> _handle;

	public:
		UsbFsDevicePcd(uint32_t id)
		{
			_handle = base::usb::fs_device_pcd::open(id);
		}

		void Initialize(base::usb::PhyType phy_type)
		{
			base::usb::fs_device_pcd::initialize(*_handle, phy_type);
		}

		/* #region 注册回调 */

		void SetSofCallback(std::function<void()> const &callback)
		{
			base::usb::fs_device_pcd::set_sof_callback(*_handle, callback);
		}

		void SetSetupStageCallback(std::function<void(base::usb::fs_device_pcd::SetupStageCallbackArgs const &)> const &callback)
		{
			base::usb::fs_device_pcd::set_setup_stage_callback(*_handle, callback);
		}

		void SetResetCallback(std::function<void()> const &callback)
		{
			base::usb::fs_device_pcd::set_reset_callback(*_handle, callback);
		}

		void SetSuspendCallback(std::function<void()> const &callback)
		{
			base::usb::fs_device_pcd::set_suspend_callback(*_handle, callback);
		}

		void SetResumeCallback(std::function<void()> const &callback)
		{
			base::usb::fs_device_pcd::set_resume_callback(*_handle, callback);
		}

		void SetConnectCallback(std::function<void()> const &callback)
		{
			base::usb::fs_device_pcd::set_connect_callback(*_handle, callback);
		}

		void SetDisconnectCallback(std::function<void()> const &callback)
		{
			base::usb::fs_device_pcd::set_disconnect_callback(*_handle, callback);
		}

		void SetDataOutStageCallback(std::function<void(base::usb::fs_device_pcd::DataOutStageCallbackArgs const &)> const &callback)
		{
			base::usb::fs_device_pcd::set_data_out_stage_callback(*_handle, callback);
		}

		void SetDataInStageCallback(std::function<void(base::usb::fs_device_pcd::DataInStageCallbackArgs const &)> const &callback)
		{
			base::usb::fs_device_pcd::set_data_in_stage_callback(*_handle, callback);
		}

		void SetIsoOutIncompleteCallback(std::function<void(base::usb::fs_device_pcd::IsoOutIncompleteCallbackArgs const &)> const &callback)
		{
			base::usb::fs_device_pcd::set_iso_out_incomplete_callback(*_handle, callback);
		}

		void SetIsoInIncompleteCallback(std::function<void(base::usb::fs_device_pcd::IsoInIncompleteCallbackArgs const &)> const &callback)
		{
			base::usb::fs_device_pcd::set_iso_in_incomplete_callback(*_handle, callback);
		}

		/* #endregion */

		///
		/// @brief 启动 USB 设备。
		///
		/// @warning 先注册回调后再启动。因为注册回调的函数内部会禁用中断。
		///
		void Start()
		{
			base::usb::fs_device_pcd::start(*_handle);
		}

		///
		/// @brief 挂起 USB 设备。
		///
		void Suspend()
		{
			base::usb::fs_device_pcd::suspend(*_handle);
		}

		void Resume()
		{
			base::usb::fs_device_pcd::resume(*_handle);
		}
	};

	base::Slot<base::usb::fs_device_pcd::UsbFsDevicePcd> &usb_fs_pcd_slot();

} // namespace base::usb::fs_device_pcd
