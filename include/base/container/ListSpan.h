#pragma once
#include "base/container/IList.h"
#include "base/string/define.h"
#include <algorithm>
#include <cstdint>
#include <stdexcept>

namespace base
{
	///
	/// @brief 列表段，用来实现列表上的滑动窗口。
	///
	///
	template <typename ItemType>
	class ListSpan
	{
	private:
		base::IList<ItemType> *_list = nullptr;
		int64_t _start_index = 0;
		int64_t _end_index = 0;

	public:
		ListSpan() = default;

		constexpr ListSpan(base::IList<ItemType> &list, int64_t start_index, int64_t end_index)
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

			if (end_index > list.Count())
			{
				throw std::invalid_argument{CODE_POS_STR + "end_index 超出范围."};
			}

			_list = &list;
			_start_index = start_index;
			_end_index = end_index;
		}

		constexpr int64_t StartIndex() const
		{
			return _start_index;
		}

		constexpr int64_t EndIndex() const
		{
			return _end_index;
		}

		///
		/// @brief 列表中元素的数量。
		///
		/// @return
		///
		constexpr int64_t Count() const
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
		constexpr ItemType &Get(int64_t index)
		{
			return _list->Get(index + _start_index);
		}

		///
		/// @brief 获取指定索引位置的元素。
		///
		/// @param index
		///
		/// @return
		///
		constexpr ItemType const &Get(int64_t index) const
		{
			return _list->Get(index + _start_index);
		}

		///
		/// @brief 设置指定位置的元素。
		///
		/// @param index
		/// @param value
		///
		constexpr void Set(int64_t index, ItemType const &value)
		{
			_list->Set(index + _start_index, value);
		}

		///
		/// @brief 尽可能增大起始索引的值。这会导致窗口缩小。
		///
		/// @param value
		/// @return
		///
		constexpr int64_t AddStartAsFarAsPossible(int64_t value)
		{
			if (value < 0)
			{
				throw std::invalid_argument{CODE_POS_STR + "value 不能小于 0."};
			}

			if (value == 0)
			{
				return 0;
			}

			int64_t possible = _end_index - _start_index;
			if (possible <= 0)
			{
				return 0;
			}

			int64_t delta = std::min(possible, value);
			_start_index += delta;
			return delta;
		}

		///
		/// @brief 尽可能减小起始索引的值。这会导致窗口扩大。
		///
		/// @param value
		/// @return
		///
		constexpr int64_t SubtractStartAsFarAsPossible(int64_t value)
		{
			if (value < 0)
			{
				throw std::invalid_argument{CODE_POS_STR + "value 不能小于 0."};
			}

			if (value == 0)
			{
				return 0;
			}

			int64_t possible = _start_index;
			if (possible <= 0)
			{
				return 0;
			}

			int64_t delta = std::min(possible, value);
			_start_index -= delta;
			return delta;
		}

		///
		/// @brief 尽可能增大结束索引的值，这会导致窗口扩大。如果窗口已经顶到列表边界了就会无法继续扩大更多。
		///
		/// @param expand_size
		/// @return
		///
		constexpr int64_t AddEndAsFarAsPossible(int64_t value)
		{
			if (value < 0)
			{
				throw std::invalid_argument{CODE_POS_STR + "value 不能小于 0."};
			}

			if (value == 0)
			{
				return 0;
			}

			int64_t possible = _list->Count() - _end_index;
			if (possible <= 0)
			{
				return 0;
			}

			int64_t delta = std::min(possible, value);
			_end_index += delta;
			return delta;
		}

		///
		/// @brief 尽可能减小结束索引的值。这会导致窗口缩小。
		///
		/// @param value
		/// @return
		///
		constexpr int64_t SubtractEndAsFarAsPossible(int64_t value)
		{
			if (value < 0)
			{
				throw std::invalid_argument{CODE_POS_STR + "value 不能小于 0."};
			}

			if (value == 0)
			{
				return 0;
			}

			int64_t possible = _end_index - _start_index;
			if (possible <= 0)
			{
				return 0;
			}

			int64_t delta = std::min(possible, value);
			_end_index -= delta;
			return delta;
		}

		///
		/// @brief 移动列表窗口。
		///
		/// @param step
		/// @return
		///
		constexpr bool TryMove(int64_t step)
		{
			if (_start_index + step < 0)
			{
				return false;
			}

			if (_end_index + step > _list->Count())
			{
				return false;
			}

			_start_index += step;
			_end_index += step;
			return true;
		}

		///
		/// @brief 尽可能移动列表窗口。如果窗口已经顶到列表边界了就会无法继续移动更多。
		///
		/// @param step
		///
		/// @return 实际移动距离。
		///
		constexpr int64_t TryMoveAsFarAsPossible(int64_t step)
		{
			int64_t delta = 0;

			if (step > 0)
			{
				int64_t avalible = _list->Count() - _end_index;
				delta = std::min(step, avalible);
				TryMove(delta);
			}
			else if (step < 0)
			{
				int64_t avalible = -_start_index;
				delta = std::max(step, avalible);
				TryMove(delta);
			}

			return delta;
		}
	};

} // namespace base
