#pragma once
#include "base/embedded/flash/Flash.h"
#include "base/embedded/flash/LittleFsFlash.h"

namespace base
{
	namespace test
	{
		inline void TestLittleFsFlash()
		{
			base::flash::Flash flash{1};
			flash.Initialize();
			base::flash::LittleFsFlash little_fs_flash{flash};
		}

	} // namespace test
} // namespace base
