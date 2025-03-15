#pragma once
#include <base/container/ArraySpan.h>
#include <base/container/iterator/IEnumerable.h>
#include <base/sfinae/Compare.h>
#include <base/string/define.h>
#include <functional>
#include <stdexcept>

namespace base
{
	/**
	 * @brief 只要底层的储存方式是 C 风格的裸数组的容器，都可以继承本接口。
	 *
	 * @tparam ItemType
	 */
	template <typename ItemType>
	class IRawArray :
		public virtual base::IEnumerable<ItemType>
	{
	public:
		/* #region 接口 */

		/**
		 * @brief 数组的大小
		 *
		 * @return int32_t
		 */
		virtual int32_t Count() const = 0;

		/**
		 * @brief 获取底层的缓冲区
		 *
		 * @return ItemType*
		 */
		virtual ItemType *Buffer() = 0;

		/**
		 * @brief 获取底层的缓冲区
		 *
		 * @return ItemType const*
		 */
		virtual ItemType const *Buffer() const = 0;

		/* #endregion */

		/* #region 索引器 */

		ItemType &operator[](int32_t const index)
		{
			if (index < 0 || index >= Count())
			{
				throw std::out_of_range{"索引超出范围"};
			}

			return Buffer()[index];
		}

		ItemType const &operator[](int32_t const index) const
		{
			if (index < 0 || index >= static_cast<int32_t>(Count()))
			{
				throw std::out_of_range{"索引超出范围"};
			}

			return Buffer()[index];
		}

		/* #endregion */

		/* #region CopyFrom */

		/**
		 * @brief 将 another 的元素拷贝到本容器。
		 *
		 * @note 两个容器的元素个数必须相等，否则会抛出异常。
		 *
		 * @param another
		 */
		void CopyFrom(base::IRawArray<ItemType> const &another)
		{
			Span().CopyFrom(another.Span());
		}

		/**
		 * @brief 将 another 的元素拷贝到本容器。
		 *
		 * @note 两个容器的元素个数必须相等，否则会抛出异常。
		 *
		 * @param another
		 */
		void CopyFrom(base::ReadOnlyArraySpan<ItemType> const &another)
		{
			Span().CopyFrom(another.Span());
		}

		/* #endregion */

		///
		/// @brief 翻转
		///
		///
		void Reverse()
		{
			Span().Reverse();
		}

		/* #region Sort */

		///
		/// @brief 排序。
		///
		/// @param ascending 是否按升序排序，即从小到大排序。传入 true 则按升序排序，传入 false 则按降序排序。
		///
		/// @warning 需要 ItemType 实现了比较运算符，否则会引发异常。
		///
		void Sort(bool ascending = true)
		{
			Span().Sort(ascending);
		}

		///
		/// @brief 排序。
		///
		/// @param compare 自定义比较器。如果 left 小于 right，则返回小于 0 的值，如果相等，则返回 0，
		/// 如果 left 大于 right 则返回大于 0 的值。
		///
		/// @param ascending 是否按升序排序，即从小到大排序。传入 true 则按升序排序，传入 false 则按降序排序。
		///
		void Sort(std::function<int(ItemType const &left, ItemType const &right)> compare,
				  bool ascending = true)
		{
			Span().Sort(compare, ascending);
		}

		/* #endregion */

		/* #region Span */

		base::ArraySpan<ItemType> Span()
		{
			return base::ArraySpan<ItemType>{Buffer(), Count()};
		}

		base::ReadOnlyArraySpan<ItemType> Span() const
		{
			return base::ReadOnlyArraySpan<ItemType>{Buffer(), Count()};
		}

		/* #endregion */

		/* #region GetEnumerator */

		using IEnumerable<ItemType>::GetEnumerator;

		///
		/// @brief 获取迭代器
		///
		/// @return std::shared_ptr<IEnumerator<ItemType>>
		///
		std::shared_ptr<IEnumerator<ItemType>> GetEnumerator() override
		{
			return Span().GetEnumerator();
		}

		/* #endregion */
	};
} // namespace base
