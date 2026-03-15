#pragma once
#include "base/container/ArraySpan.h"
#include "base/sfinae/Compare.h"
#include "base/stream/ReadOnlySpan.h"
#include "base/stream/Span.h"
#include "base/string/define.h"

namespace base
{
	///
	/// @brief 只要底层的储存方式是 C 风格的裸数组的容器，都可以继承本接口。
	///
	template <typename ItemType>
	class IRawArray
	{
	private:
	public:
		/* #region 迭代器 */

		template <typename item_type>
		class Iterator
		{
		private:
			IRawArray *_array = nullptr;
			int64_t _index = 0;

		public:
			using iterator_category = std::random_access_iterator_tag;
			using value_type = item_type;
			using difference_type = int64_t;
			using pointer = item_type *;
			using reference = item_type &;

			Iterator() = default;

			Iterator(IRawArray *array, int64_t index)
			{
				_array = array;
				_index = index;
			}

			item_type &operator*()
			{
				if (_array == nullptr)
				{
					throw std::invalid_argument{CODE_POS_STR + "迭代器处于无效状态。"};
				}

				return (*_array)[_index];
			}

			item_type *operator->()
			{
				return &operator*();
			}

			///
			/// @brief 前缀递增
			///
			/// @return
			///
			Iterator &operator++()
			{
				_index++;
				return *this;
			}

			///
			/// @brief 后缀递增。
			///
			Iterator operator++(int)
			{
				Iterator copy{*this};
				_index++;
				return copy;
			}

			///
			/// @brief 前缀递减。
			///
			/// @return
			///
			Iterator &operator--()
			{
				_index--;
				return *this;
			}

			///
			/// @brief 后缀递减。
			///
			/// @return
			///
			Iterator operator--(int)
			{
				Iterator copy{*this};
				_index--;
				return copy;
			}

			Iterator &operator+=(int64_t value)
			{
				_index += value;
				return *this;
			}

			Iterator operator+(int64_t value) const
			{
				Iterator copy{*this};
				copy += value;
				return copy;
			}

			int64_t operator-(Iterator const &other) const
			{
				return _index - other._index;
			}

			bool operator==(Iterator const &other) const
			{
				return _index == other._index;
			}

			bool operator!=(Iterator const &other) const
			{
				return !(*this == other);
			}
		};

		/* #endregion */

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
			requires(has_all_compare_operators<ItemType, ItemType>)
		{
			Span().Sort(ascending);
		}

		///
		/// @brief 排序。
		///
		/// @param compare 谓语。如果希望 left 排到 right 前面，则返回 true. 如果返回 false,
		/// 则 left 和 right 会保持当前相对顺序，不会调整。
		///
		template <typename parameter_type>
		void Sort(parameter_type const &compare)
			requires(std::is_convertible_v<parameter_type, std::function<bool(ItemType const &left, ItemType const &right)>>)
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

		operator base::Span()
			requires(std::is_same_v<ItemType, uint8_t>)
		{
			return base::Span{Buffer(), Count()};
		}

		operator base::ReadOnlySpan() const
			requires(std::is_same_v<ItemType, uint8_t>)
		{
			return base::ReadOnlySpan{Buffer(), Count()};
		}

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

		Iterator<ItemType> begin()
		{
			return Iterator<ItemType>{this, 0};
		}

		Iterator<ItemType> end()
		{
			return Iterator<ItemType>{this, Count()};
		}

		Iterator<ItemType const> begin() const
		{
			return Iterator<ItemType const>{const_cast<IRawArray *>(this), 0};
		}

		Iterator<ItemType const> end() const
		{
			return Iterator<ItemType const>{const_cast<IRawArray *>(this), Count()};
		}
	};

} // namespace base
