#pragma once
#include "base/container/IList.h"
#include "base/container/Range.h"
#include "base/filesystem/IMemoryMapFile.h"
#include "base/filesystem/Path.h"
#include "base/stream/Span.h"
#include "base/string/define.h"
#include <algorithm>
#include <cstdint>
#include <new> // IWYU pragma: keep
#include <stdexcept>
#include <utility>

namespace base
{
	template <typename ItemType>
	class MemoryMapFileList final :
		public base::IList<ItemType>
	{
	private:
		base::Path _memory_map_file_path;
		std::shared_ptr<base::memory_map_file::IMemoryMapFile> _memory_map_file;
		base::Span _span;
		int64_t _count = 0;

		///
		/// @brief 储备空间能够储存多少个元素。
		///
		/// @return
		///
		int64_t ReservedCount() const
		{
			return _span.Size() / sizeof(ItemType);
		}

		///
		/// @brief 储备一定空间，以容纳 count 个元素。
		///
		/// @param count
		///
		void Reserve(int64_t count)
		{
			_memory_map_file->UnMapAll();

			int64_t size = count * sizeof(ItemType);
			size = std::max(size, _span.Size() * 2);
			_span = _memory_map_file->Map(base::Range{0, size});
		}

		ItemType *GetAddress(int64_t index) const
		{
			uint8_t *address = _span.Buffer() + (index * sizeof(ItemType));
			return reinterpret_cast<ItemType *>(address);
		}

		///
		/// @brief 把 index 后面的 offset 位置及后续的元素向上移动到 index 的位置。
		/// 会把 index 位置给覆盖掉，如果那个位置是一个有效元素，需要提前析构。
		///
		/// @param index
		/// @param offset
		///
		void MoveUp(int64_t index, int64_t offset)
		{
			if (offset < 0)
			{
				throw std::invalid_argument{CODE_POS_STR + "offset 不能 <0."};
			}

			if (offset == 0)
			{
				return;
			}

			int64_t current_index = index;

			for (int64_t next_index = current_index + offset; next_index < _count; next_index++)
			{
				ItemType *current_item = GetAddress(current_index);
				ItemType *next_item = GetAddress(next_index);

				try
				{
					new (current_item) ItemType{std::move(*next_item)};

					// 成功拷贝或移动后才递增 current_index.
					current_index++;
				}
				catch (...)
				{
					// 拷贝或移动失败，直接把 next_item 丢弃，递减容器计数。
					_count--;
				}

				// 失败了也会递增 next_item, 并且直接把 next_item 丢弃。
				next_item->~ItemType();
			}
		}

		void MoveDown(int64_t index, int64_t offset)
		{
			if (offset < 0)
			{
				throw std::invalid_argument{CODE_POS_STR + "offset 不能 <0."};
			}

			if (offset == 0)
			{
				return;
			}

			if (_count == 0)
			{
				return;
			}

			Reserve(_count + offset);

			int64_t discarded_count = 0;

			// 从底部开始向上推进，逐个向下拷贝。
			int64_t current_index = _count - 1 + offset;

			for (int64_t next_index = current_index - offset; next_index >= index; next_index--)
			{
				ItemType *current_item = GetAddress(current_index);
				ItemType *next_item = GetAddress(next_index);

				try
				{
					new (current_item) ItemType{std::move(*next_item)};

					// 成功拷贝或移动后才递增 current_index.
					current_index--;
				}
				catch (...)
				{
					// 拷贝或移动失败，直接把 next_item 丢弃，递减容器计数。
					discarded_count++;
				}

				next_item->~ItemType();
			}

			_count -= discarded_count;
			MoveUp(index + offset, discarded_count);
		}

	public:
		MemoryMapFileList(base::Path const &memory_map_file_path)
		{
			_memory_map_file_path = memory_map_file_path;
			_memory_map_file = base::memory_map_file::OpenOrCreate(memory_map_file_path);
			Reserve(0);
		}

		///
		/// @brief 向列表末尾添加一个元素。
		///
		/// @param item
		///
		virtual void Add(ItemType const &item) override
		{
			Reserve(_count + 1);
			ItemType *address = GetAddress(_count);
			new (address) ItemType{item};
			_count++;
		}

		///
		/// @brief 将元素插入列表指定位置。
		///
		/// @param index
		/// @param item
		///
		virtual void Insert(int64_t index, ItemType const &item) override
		{
			Reserve(_count + 1);
			MoveDown(index, 1);
			ItemType *current_address = GetAddress(index);

			try
			{
				new (current_address) ItemType{item};
				_count++;
			}
			catch (...)
			{
				MoveUp(index, 1);
			}
		}

		///
		/// @brief 移除指定索引位置的元素。
		///
		/// @param index
		///
		virtual void RemoveAt(int64_t index) override
		{
			ItemType *current_item = GetAddress(index);
			current_item->~ItemType();
			MoveUp(index, 1);
			_count--;
		}

		///
		/// @brief 清空列表。
		///
		///
		virtual void Clear() override
		{
			for (int64_t i = 0; i < _count; i++)
			{
				ItemType &item = Get(i);
				item.~ItemType();
			}

			_count = 0;
		}

		///
		/// @brief 列表中元素的数量。
		///
		/// @return
		///
		virtual int64_t Count() const override
		{
			return _count;
		}

		///
		/// @brief 获取指定索引位置的元素。
		///
		/// @param index
		///
		/// @return
		///
		virtual ItemType &Get(int64_t index) override
		{
			if (index < 0 || index >= _count)
			{
				throw std::out_of_range{CODE_POS_STR + "索引超出范围。"};
			}

			ItemType *address = GetAddress(index);
			return *address;
		}

		///
		/// @brief 获取指定索引位置的元素。
		///
		/// @param index
		///
		/// @return
		///
		virtual ItemType const &Get(int64_t index) const override
		{
			if (index < 0 || index >= _count)
			{
				throw std::out_of_range{CODE_POS_STR + "索引超出范围。"};
			}

			ItemType const *address = GetAddress(index);
			return *address;
		}

		///
		/// @brief 设置指定位置的元素。
		///
		/// @param index
		/// @param value
		///
		virtual void Set(int64_t index, ItemType const &value) override
		{
			if (index < 0 || index >= _count)
			{
				throw std::out_of_range{CODE_POS_STR + "索引超出范围。"};
			}

			ItemType const *address = GetAddress(index);
			*address = value;
		}
	};

} // namespace base
