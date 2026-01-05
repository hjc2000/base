#pragma once
#include "base/net/Mac.h"

namespace base
{
	namespace profinet
	{
		/// @brief 多播 MAC 地址集合
		class MulticastMacEnum
		{
		public:
			static base::Mac const DcpIdentify();
			static base::Mac const DcpHello();
		};
	} // namespace profinet
} // namespace base
