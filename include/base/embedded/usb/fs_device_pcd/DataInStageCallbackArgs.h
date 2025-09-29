#pragma once
#include <cstdint>

namespace base
{
	namespace usb
	{
		namespace fs_device_pcd
		{
			class DataInStageCallbackArgs
			{
			private:
				uint8_t _endpoint_number;

			public:
				DataInStageCallbackArgs(uint8_t endpoint_number)
				{
					_endpoint_number = endpoint_number;
				}

				///
				/// @brief 端点号。
				///
				/// @return
				///
				uint8_t EndpointNumber() const
				{
					return _endpoint_number;
				}
			};

		} // namespace fs_device_pcd
	} // namespace usb
} // namespace base
