#pragma once
#include "base/embedded/flash/littlefs/src/lfs.h"

namespace base
{
	namespace flash
	{
		class LittleFsFlash
		{
		private:
			class handle_context
			{
			public:
				handle_context(LittleFsFlash *self)
					: _self(self)
				{
				}

				lfs_config _config{};
				LittleFsFlash *_self = nullptr;
			};

			handle_context _handle_context{this};

		public:
		};

	} // namespace flash
} // namespace base
