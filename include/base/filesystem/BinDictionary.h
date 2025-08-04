#pragma once
#include "base/Console.h"
#include "base/container/IDictionary.h"
#include "base/filesystem/filesystem.h"
#include "base/filesystem/IFileStream.h"
#include "base/filesystem/Path.h"
#include "base/stream/Stream.h"
#include "base/string/define.h"
#include <cstdint>
#include <memory>
#include <stdexcept>
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
			base::Path _workspace;

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

			void CountFile()
			{
			}

		public:
			BinDictionary(base::Path const &workspace)
			{
				_workspace = workspace;
				CountFile();
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
				if (key.size() == 0)
				{
					throw std::invalid_argument{CODE_POS_STR + "键不能是空字符串。"};
				}

				base::Path file_path = _workspace + key;
				if (!base::filesystem::Exists(file_path))
				{
					return nullptr;
				}

				try
				{
					_current_value = base::file::OpenExisting(file_path);
					return &_current_value;
				}
				catch (std::exception const &e)
				{
					base::console.WriteError(CODE_POS_STR + e.what());
					return nullptr;
				}
				catch (...)
				{
					base::console.WriteError(CODE_POS_STR + "未知异常。");
					return nullptr;
				}

				return nullptr;
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
				if (key.size() == 0)
				{
					throw std::invalid_argument{CODE_POS_STR + "键不能是空字符串。"};
				}

				base::Path file_path = _workspace + key;
				if (base::filesystem::Exists(file_path))
				{
					base::filesystem::Remove(file_path);
					return true;
				}

				return false;
			}

			///
			/// @brief 清空所有元素。
			///
			///
			virtual void Clear() override
			{
				// 先删除工作目录，以达到清空字典的目的。
				base::filesystem::Remove(_workspace);
				_count = 0;
				base::filesystem::EnsureDirectory(_workspace);
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
				if (key.size() == 0)
				{
					throw std::invalid_argument{CODE_POS_STR + "键不能是空字符串。"};
				}

				base::Path file_path = _workspace + key;
				_current_value = base::file::CreateNewAnyway(file_path);

				if (item != nullptr)
				{
					item->CopyTo(_current_value, base::CancellationToken::None());
				}
			}
		};

	} // namespace filesystem
} // namespace base
