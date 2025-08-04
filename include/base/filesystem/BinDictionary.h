#pragma once
#include "base/container/IDictionary.h"
#include "base/stream/Stream.h"
#include <memory>
#include <string>

namespace base
{
	namespace filesystem
	{
		///
		/// @brief 二进制字典。
		///
		/// @note 利用文件系统实现。
		///
		/// @note 文件系统就是天然的字典。文件名是 key, 文件内容是 value.
		/// 这里封装一个通用的二进制文件字典，以字符串作为 key, 用来打开文件，然后返回此文件
		/// 的流，作为 value.
		///
		class BinDictionary :
			public base::IDictionary<std::string, std::shared_ptr<base::Stream>>
		{
		public:
			BinDictionary()
			{
			}
		};

	} // namespace filesystem
} // namespace base
