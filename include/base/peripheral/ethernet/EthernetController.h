#pragma once
#include "ethernet_controller_handle.h"
#include <memory>

namespace base
{
	namespace ethernet
	{
		class EthernetController
		{
		private:
			std::shared_ptr<base::ethernet::ethernet_controller_handle> _handle;

		public:
			EthernetController()
			{
				_handle = base::ethernet::open();
			}

			EthernetController(uint32_t id)
			{
				_handle = base::ethernet::open(id);
			}
		};
	} // namespace ethernet
} // namespace base
