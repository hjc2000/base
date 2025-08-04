#pragma once
#include "base/container/IDictionary.h"
#include "base/stream/Stream.h"
#include <cstdint>
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
		private:
			///
			/// @brief 工作目录中的文件总数，也是字典的元素数量。
			///
			/// @note 构造的时候数一遍文件数量，然后储存这个数量，后续如果这个目录只被
			/// 本对象编辑的话，这个计数理论上会保持正确。
			///
			int64_t _count = 0;

			///
			/// @brief 当前的查找结果，找到了就打开文件，把文件流储存到本字段。
			///
			std::shared_ptr<base::Stream> _current_value;

			void TryOpenFile(std::string const &file_name)
			{
			}

		public:
			BinDictionary()
			{
			}

			///
			/// @brief 获取元素个数。
			///
			/// @return
			///
			virtual int64_t Count() const override
			{
				return _count;
			}

			///
			/// @brief 查找元素。
			///
			/// @param key 键
			///
			/// @return 指针。找到了返回元素的指针，找不到返回空指针。
			///
			virtual std::shared_ptr<base::Stream> *Find(std::string const &key) override
			{
				TryOpenFile(key);
				if (_current_value == nullptr)
				{
					return nullptr;
				}

				return &_current_value;
			}

			///
			/// @brief 移除一个元素。
			///
			/// @param key 键
			///
			/// @return 移除成功返回 true，元素不存在返回 false.
			///
			virtual bool Remove(std::string const &key) override
			{
			}

			///
			/// @brief 清空所有元素。
			///
			///
			virtual void Clear() override
			{
			}

			///
			/// @brief 设置一个元素。本来不存在，会添加；本来就存在了，会覆盖。
			///
			/// @param key
			///
			/// @param item
			///
			virtual void Set(std::string const &key, std::shared_ptr<base::Stream> const &item) override
			{
			}
		};

	} // namespace filesystem
} // namespace base
