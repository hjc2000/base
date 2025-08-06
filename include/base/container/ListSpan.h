#pragma once
#include "base/container/IList.h"
#include "base/string/define.h"
#include <algorithm>
#include <cstdint>
#include <stdexcept>

namespace base
{
	template <typename ItemType>
	class ListSpan
	{
	private:
		base::IList<ItemType> &_list;
		int64_t _start_index = 0;
		int64_t _end_index = 0;

	public:
		ListSpan(base::IList<ItemType> &list, int64_t start_index, int64_t end_index)
			: _list(list),
			  _start_index(start_index),
			  _end_index(end_index)
		{
			if (start_index < 0)
			{
				throw std::invalid_argument{CODE_POS_STR + "start_index 不能小于 0."};
			}

			if (end_index < 0)
			{
				throw std::invalid_argument{CODE_POS_STR + "end_index 不能小于 0."};
			}

			if (end_index < start_index)
			{
				throw std::invalid_argument{CODE_POS_STR + "end_index 不能小于 start_index."};
			}

			if (end_index > _list.Count())
			{
				throw std::invalid_argument{CODE_POS_STR + "end_index 超出范围."};
			}
		}

		///
		/// @brief 列表中元素的数量。
		///
		/// @return
		///
		int64_t Count() const
		{
			return _end_index - _start_index;
		}

		///
		/// @brief 获取指定索引位置的元素。
		///
		/// @param index
		///
		/// @return
		///
		ItemType &Get(int64_t index)
		{
			return _list.Get(index + _start_index);
		}

		///
		/// @brief 获取指定索引位置的元素。
		///
		/// @param index
		///
		/// @return
		///
		ItemType const &Get(int64_t index) const
		{
			return _list.Get(index + _start_index);
		}

		///
		/// @brief 设置指定位置的元素。
		///
		/// @param index
		/// @param value
		///
		void Set(int64_t index, ItemType const &value)
		{
			_list.Set(index + _start_index, value);
		}

		bool TryMove(int64_t step)
		{
			if (_start_index + step < 0)
			{
				return false;
			}

			if (_end_index + step > _list.Count())
			{
				return false;
			}

			_start_index += step;
			_end_index += step;
			return true;
		}

		int64_t TryMoveAsFarAsPossible(int64_t step)
		{
			int64_t have_moved = 0;

			if (step > 0)
			{
				int64_t avalible = _list.Count() - _end_index;
				have_moved = std::min(step, avalible);
				TryMove(have_moved);
			}
			else if (step < 0)
			{
				int64_t avalible = -_start_index;
				have_moved = std::max(step, avalible);
				TryMove(have_moved);
			}

			return have_moved;
		}
	};

} // namespace base
