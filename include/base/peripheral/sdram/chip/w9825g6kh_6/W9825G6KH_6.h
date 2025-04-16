#pragma once
#include "base/peripheral/sdram/SdramController.h"

namespace base
{
	namespace sdram
	{
		namespace chip
		{
			namespace w9825g6kh_6
			{
				class W9825G6KH_6
				{
				private:
					base::sdram::SdramController _controller;

				public:
					///
					/// @brief 构造函数。
					/// @param controller 需要一个控制器来控制 SDRAM 芯片。
					///
					W9825G6KH_6(base::sdram::SdramController const &controller);

					///
					/// @brief 打开 SDRAM.
					///
					/// @note 分为 2 步：
					/// 	@li 打开 SDRAM 控制器。
					/// 	@li 初始化 SDRAM 芯片。
					///
					void Open();

					///
					/// @brief 此 SDRAM 的内存段。
					/// @return
					///
					base::Span Span() const;
				};
			} // namespace w9825g6kh_6
		} // namespace chip
	} // namespace sdram
} // namespace base
