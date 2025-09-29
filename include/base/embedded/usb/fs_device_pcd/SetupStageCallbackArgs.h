#pragma once
#include "base/stream/ReadOnlySpan.h"

namespace base
{
	namespace usb
	{
		namespace fs_device_pcd
		{
			class SetupStageCallbackArgs
			{
			private:
				base::ReadOnlySpan _span;

			public:
				SetupStageCallbackArgs(base::ReadOnlySpan const &span)
				{
					_span = span;
				}

				base::ReadOnlySpan Span() const
				{
					return _span;
				}
			};

		} // namespace fs_device_pcd
	} // namespace usb
} // namespace base
