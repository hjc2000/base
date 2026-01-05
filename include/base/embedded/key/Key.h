#pragma once
#include "key_handle.h"
#include <string>

namespace base
{
	namespace key
	{
		///
		/// @brief 按键类。包装按键句柄。
		///
		///
		class Key
		{
		private:
			base::key::sp_key_handle _handle{};

		public:
			Key(int key_id)
			{
				_handle = base::key::open(key_id);
			}

			Key(std::string const &key_name)
			{
				_handle = base::key::open(key_name);
			}

			std::string KeyName() const
			{
				return base::key::key_name(*_handle);
			}

			bool KeyIsDown() const
			{
				return base::key::key_is_down(*_handle);
			}

			bool KeyIsUp() const
			{
				return base::key::key_is_up(*_handle);
			}
		};

	} // namespace key
} // namespace base
