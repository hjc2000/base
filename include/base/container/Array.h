#pragma once
#include "base/container/IRawArray.h"
#include <array>
#include <initializer_list>

namespace base
{
	///
	/// @brief 数组
	///
	template <typename ItemType, int64_t TCount>
	class Array final :
		public base::IRawArray<ItemType>
	{
	private:
		std::array<ItemType, TCount> _arr{};

	public:
		/* #region 构造函数 */

		///
		/// @brief 无参构造。
		///
		/// @note 构造出的数组的元素也全部使用无参构造函数初始化。
		///
		Array() = default;

		Array(base::ReadOnlyArraySpan<ItemType> const &span)
		{
			if (span.Count() != TCount)
			{
				throw std::invalid_argument{"span 的元素个数和本数组不同。"};
			}

			this->Span().CopyFrom(span);
		}

		///
		/// @brief 将初始化列表的数据拷贝过来。
		///
		/// @param list 初始化列表。
		///
		Array(std::initializer_list<ItemType> const &list)
		{
			int64_t i = 0;
			for (auto &item : list)
			{
				_arr[i++] = item;
			}
		}

		///
		/// @brief 将 o 的数据拷贝过来。
		///
		/// @param o
		///
		Array(std::array<ItemType, TCount> const &o)
		{
			_arr = o;
		}

		/* #endregion */

		///
		/// @brief 数组的大小。
		///
		/// @return
		///
		virtual int64_t Count() const override
		{
			return TCount;
		}

		///
		/// @brief 获取底层的缓冲区。
		///
		/// @return
		///
		virtual ItemType *Buffer() override
		{
			return _arr.data();
		}

		///
		/// @brief 获取底层的缓冲区。
		///
		/// @return
		///
		virtual ItemType const *Buffer() const override
		{
			return _arr.data();
		}
	};

} // namespace base
