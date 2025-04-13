#pragma once
#include "base/define.h"
#include <memory>
#include <string>

namespace base
{
	namespace key
	{
		class key_handle;
		using sp_key_handle = std::shared_ptr<base::key::key_handle>;

		base::key::sp_key_handle open(std::string const &key_name);
		base::key::sp_key_handle open(int key_id);

		///
		/// @brief 获取按键名称。
		///
		/// @param h
		/// @return std::string
		///
		std::string key_name(base::key::key_handle &h);

		///
		/// @brief 按键是否处于被按下的状态。
		///
		/// @param h
		/// @return true
		/// @return false
		///
		bool key_is_down(base::key::key_handle &h);

		///
		/// @brief 按键是否处于被松开的状态。
		///
		/// @param h
		/// @return true
		/// @return false
		///
		IMPLEMENTED
		inline bool key_is_up(base::key::key_handle &h)
		{
			return !key_is_down(h);
		}

	} // namespace key
} // namespace base
