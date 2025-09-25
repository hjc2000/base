#pragma once
#include "base/embedded/Slot.h"
#include "usb_fs_pcd_handle.h"
#include <cstdint>
#include <memory>

namespace base
{
	namespace usb::fs_pcd
	{
		class UsbFsPcd
		{
		private:
			std::shared_ptr<base::usb::fs_pcd::usb_fs_pcd_handle> _handle;

		public:
			UsbFsPcd(uint32_t id)
			{
				_handle = base::usb::fs_pcd::open(id);
			}

			void InitializeAsDevice(base::usb::PhyType phy_type)
			{
				base::usb::fs_pcd::initialize_as_device(*_handle, phy_type);
			}

			///
			/// @brief 启动 USB 设备。
			///
			void Start()
			{
				base::usb::fs_pcd::start(*_handle);
			}

			///
			/// @brief 挂起 USB 设备。
			///
			void Suspend()
			{
				base::usb::fs_pcd::suspend(*_handle);
			}

			void Resume()
			{
				base::usb::fs_pcd::resume(*_handle);
			}

			/* #region 注册回调 */

			void SetSofCallback(std::function<void()> const &callback)
			{
				base::usb::fs_pcd::set_sof_callback(*_handle, callback);
			}

			void SetSetupStageCallback(std::function<void(base::usb::fs_pcd::SetupStageCallbackArgs const &)> const &callback)
			{
				base::usb::fs_pcd::set_setup_stage_callback(*_handle, callback);
			}

			void SetResetCallback(std::function<void()> const &callback)
			{
				base::usb::fs_pcd::set_reset_callback(*_handle, callback);
			}

			void SetSuspendCallback(std::function<void()> const &callback)
			{
				base::usb::fs_pcd::set_suspend_callback(*_handle, callback);
			}

			void SetResumeCallback(std::function<void()> const &callback)
			{
				base::usb::fs_pcd::set_resume_callback(*_handle, callback);
			}

			void SetConnectCallback(std::function<void()> const &callback)
			{
				base::usb::fs_pcd::set_connect_callback(*_handle, callback);
			}

			void SetDisconnectCallback(std::function<void()> const &callback)
			{
				base::usb::fs_pcd::set_disconnect_callback(*_handle, callback);
			}

			void SetDataOutStageCallback(std::function<void(base::usb::fs_pcd::DataOutStageCallbackArgs)> const &callback)
			{
				base::usb::fs_pcd::set_data_out_stage_callback(*_handle, callback);
			}

			/* #endregion */
		};

		base::Slot<base::usb::fs_pcd::UsbFsPcd> &usb_fs_pcd_slot();

	} // namespace usb::fs_pcd
} // namespace base
