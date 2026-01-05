#pragma once
#include "base/container/ArraySpan.h"
#include "base/container/iterator/IRandomAccessEnumerable.h"
#include "base/sfinae/Compare.h"
#include "base/string/define.h"

namespace base
{
	///
	/// @brief 只要底层的储存方式是 C 风格的裸数组的容器，都可以继承本接口。
	///
	template <typename ItemType>
	class IRawArray :
		public virtual base::IRandomAccessEnumerable<ItemType>
	{
	public:
		virtual ~IRawArray() = default;

		/* #region 接口 */

		///
		/// @brief 数组的大小。
		///
		/// @return
		///
		virtual int64_t Count() const = 0;

		///
		/// @brief 获取底层的缓冲区。
		///
		/// @return
		///
		virtual ItemType *Buffer() = 0;

		///
		/// @brief 获取底层的缓冲区。
		///
		/// @return
		///
		virtual ItemType const *Buffer() const = 0;

		/* #endregion */

		/* #region 索引器 */

		ItemType &operator[](int64_t const index)
		{
			if (index < 0 || index >= Count())
			{
				throw std::out_of_range{CODE_POS_STR + "索引超出范围"};
			}

			return Buffer()[index];
		}

		ItemType const &operator[](int64_t const index) const
		{
			if (index < 0 || index >= static_cast<int64_t>(Count()))
			{
				throw std::out_of_range{CODE_POS_STR + "索引超出范围"};
			}

			return Buffer()[index];
		}

		/* #endregion */

		/* #region CopyFrom */

		///
		/// @brief 将 another 的元素拷贝到本容器。
		///
		/// @note 两个容器的元素个数必须相等，否则会抛出异常。
		///
		/// @param another
		///
		void CopyFrom(base::IRawArray<ItemType> const &another)
		{
			Span().CopyFrom(another.Span());
		}

		///
		/// @brief 将 another 的元素拷贝到本容器。
		///
		/// @note 两个容器的元素个数必须相等，否则会抛出异常。
		///
		/// @param another
		///
		void CopyFrom(base::ReadOnlyArraySpan<ItemType> const &another)
		{
			Span().CopyFrom(another);
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
		/// @param compare 谓语。如果希望 left 排到 right 前面，则返回 true. 如果返回 false,
		/// 则 left 和 right 会保持当前相对顺序，不会调整。
		///
		void Sort(std::function<bool(ItemType const &left, ItemType const &right)> const &compare)
		{
			Span().Sort(compare);
		}

		/* #endregion */

		///
		/// @brief 洗牌。
		///
		void Shuffle()
		{
			Span().Shuffle();
		}

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

		/* #region GetRandomAccessEnumerator */

		using base::IRandomAccessEnumerable<ItemType>::GetRandomAccessEnumerator;

		///
		/// @brief 获取非 const 迭代器
		///
		/// @return
		///
		virtual std::shared_ptr<base::IRandomAccessEnumerator<ItemType>> GetRandomAccessEnumerator() override
		{
			return Span().GetRandomAccessEnumerator();
		}

		/* #endregion */

		/* #region 比较运算符 */

		///
		/// @brief 基于字典序比较。
		///
		/// @return
		///
		bool operator==(IRawArray<ItemType> const &o) const
			requires(base::has_all_compare_operators<ItemType, ItemType>)
		{
			if (this == &o)
			{
				return true;
			}

			if (Count() != o.Count())
			{
				return false;
			}

			// 执行到这里说明 Count 相等。
			for (int64_t i = 0; i < Count(); i++)
			{
				if ((*this)[i] != o[i])
				{
					return false;
				}
			}

			return true;
		}

		///
		/// @brief 基于字典序比较。
		///
		/// @return
		///
		bool operator<(IRawArray<ItemType> const &o) const
			requires(base::has_all_compare_operators<ItemType, ItemType>)
		{
			if (this == &o)
			{
				return false;
			}

			int64_t count = std::min(Count(), o.Count());

			for (int64_t i = 0; i < count; i++)
			{
				if ((*this)[i] < o[i])
				{
					return true;
				}

				if ((*this)[i] > o[i])
				{
					return false;
				}

				// 相等就继续下一轮循环
			}

			// 经过循环后还没返回，说明比较结果都是相等。接下来比较长度。
			return Count() < o.Count();
		}

		///
		/// @brief 基于字典序比较。
		///
		/// @return
		///
		bool operator>(IRawArray<ItemType> const &o) const
			requires(base::has_all_compare_operators<ItemType, ItemType>)
		{
			if (this == &o)
			{
				return false;
			}

			int64_t count = std::min(Count(), o.Count());

			for (int64_t i = 0; i < count; i++)
			{
				if ((*this)[i] > o[i])
				{
					return true;
				}

				if ((*this)[i] < o[i])
				{
					return false;
				}

				// 相等就继续下一轮循环
			}

			// 经过循环后还没返回，说明比较结果都是相等。接下来比较长度。
			return Count() > o.Count();
		}

		///
		/// @brief 基于字典序比较。
		///
		/// @return
		///
		bool operator<=(IRawArray<ItemType> const &o) const
			requires(base::has_all_compare_operators<ItemType, ItemType>)
		{
			if (this == &o)
			{
				return false;
			}

			int64_t count = std::min(Count(), o.Count());

			for (int64_t i = 0; i < count; i++)
			{
				if ((*this)[i] < o[i])
				{
					return true;
				}

				if ((*this)[i] > o[i])
				{
					return false;
				}

				// 相等就继续下一轮循环
			}

			// 经过循环后还没返回，说明比较结果都是相等。接下来比较长度。
			return Count() <= o.Count();
		}

		///
		/// @brief 基于字典序比较。
		///
		/// @return
		///
		bool operator>=(IRawArray<ItemType> const &o) const
			requires(base::has_all_compare_operators<ItemType, ItemType>)
		{
			if (this == &o)
			{
				return false;
			}

			int64_t count = std::min(Count(), o.Count());

			for (int64_t i = 0; i < count; i++)
			{
				if ((*this)[i] > o[i])
				{
					return true;
				}

				if ((*this)[i] < o[i])
				{
					return false;
				}

				// 相等就继续下一轮循环
			}

			// 经过循环后还没返回，说明比较结果都是相等。接下来比较长度。
			return Count() >= o.Count();
		}

		/* #endregion */
	};

} // namespace base
