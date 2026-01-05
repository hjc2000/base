#pragma once
#include "base/stream/ReadOnlySpan.h"

namespace base
{
	namespace usb
	{
		namespace fs_device_pcd
		{
			///
			/// @brief 数据输出回调的参数类。
			///
			class DataOutStageCallbackArgs
			{
			private:
				uint8_t _endpoint_number;
				base::ReadOnlySpan _span;

			public:
				DataOutStageCallbackArgs(uint8_t endpoint_number,
										 base::ReadOnlySpan const &span)
				{
					_endpoint_number = endpoint_number;
					_span = span;
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

				///
				/// @brief 主机输出的数据放在这个内存段里。
				///
				/// @return
				///
				base::ReadOnlySpan Span() const
				{
					return _span;
				}
			};

		} // namespace fs_device_pcd
	} // namespace usb
} // namespace base
