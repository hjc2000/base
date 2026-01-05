#pragma once
#include <cstdint>

namespace base
{
	namespace usb
	{
		namespace fs_device_pcd
		{
			class IsoInIncompleteCallbackArgs
			{
			private:
				uint8_t _endpoint_number{};

			public:
				IsoInIncompleteCallbackArgs(uint8_t endpoint_number)
				{
					_endpoint_number = endpoint_number;
				}

				uint8_t EndpointNumber() const
				{
					return _endpoint_number;
				}
			};

		} // namespace fs_device_pcd
	} // namespace usb
} // namespace base
