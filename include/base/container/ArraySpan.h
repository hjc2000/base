#pragma once
#include "base/container/Range.h"
#include "base/container/ReadOnlyArraySpan.h"
#include "base/math/random.h"
#include "base/sfinae/Compare.h"
#include "base/stream/Span.h"
#include "base/string/define.h"
#include <algorithm>
#include <cstdint>
#include <functional>
#include <stdexcept>
#include <vector>

namespace base
{
	///
	/// @brief 数组内存段。
	///
	/// @note 引用一段内存，不会持有这段内存，不管理这段内存的生命周期。
	///
	template <typename ItemType>
	class ArraySpan final
	{
	private:
	public:
		/* #region 迭代器 */

		template <typename item_type>
		class Iterator
		{
		private:
			ArraySpan *_span = nullptr;
			int64_t _index = 0;

		public:
			using iterator_category = std::random_access_iterator_tag;
			using value_type = item_type;
			using difference_type = int64_t;
			using pointer = item_type *;
			using reference = item_type &;

			Iterator() = default;

			Iterator(ArraySpan *span, int64_t index)
			{
				_span = span;
				_index = index;
			}

			item_type &operator*()
			{
				if (_span == nullptr)
				{
					throw std::invalid_argument{CODE_POS_STR + "迭代器处于无效状态。"};
				}

				return (*_span)[_index];
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

	private:
		ItemType *_buffer = nullptr;
		int64_t _count = 0;

	public:
		/* #region 构造函数 */

		///
		/// @brief 构造函数。构造出来的对象不会引用任何有效内存段，且大小为 0.
		///
		///
		ArraySpan() = default;

		///
		/// @brief 构造函数。
		///
		/// @param buffer 要引用的内存段指针。
		/// @param count 要引用的内存段大小。
		///
		ArraySpan(ItemType *buffer, int64_t count)
		{
			_buffer = buffer;
			_count = count;

			if (_buffer == nullptr)
			{
				_count = 0;
			}
		}

		/* #endregion */

		///
		/// @brief 获取本对象引用的内存段。
		///
		/// @return ItemType*
		///
		ItemType *Buffer() const
		{
			return _buffer;
		}

		///
		/// @brief 本对象引用的内存段的元素个数。
		///
		/// @return
		///
		int64_t Count() const
		{
			return _count;
		}

		///
		/// @brief 翻转本对象引用的内存段中的元素。
		///
		///
		void Reverse() const
		{
			std::reverse(_buffer, _buffer + _count);
		}

		/* #region CopyFrom */

		///
		/// @brief 将 another 的内存段的数据复制到本对象的内存段。
		///
		/// @param another
		///
		void CopyFrom(base::ReadOnlyArraySpan<ItemType> const &another) const
		{
			if (another.Count() != Count())
			{
				throw std::invalid_argument{CODE_POS_STR + "another 的 Count 属性必须和本对象的 Count 属性相等。"};
			}

			std::copy(another.Buffer(),
					  another.Buffer() + another.Count(),
					  Buffer());
		}

		///
		/// @brief 将 another 的内存段的数据复制到本对象的内存段。
		///
		/// @param another
		///
		void CopyFrom(base::ArraySpan<ItemType> const &another) const
		{
			CopyFrom(base::ReadOnlyArraySpan<ItemType>{another});
		}

		/* #endregion */

		base::ArraySpan<ItemType> Slice(base::Range const &range) const
		{
			if (range.End() > Count())
			{
				throw std::out_of_range{"超出范围，无法切片。"};
			}

			return base::ArraySpan<ItemType>{Buffer() + range.Begin(), range.Size()};
		}

		base::ArraySpan<ItemType> operator[](base::Range const &range) const
		{
			return Slice(range);
		}

		ItemType &Get(int64_t index) const
		{
			if (index < 0 || index >= Count())
			{
				throw std::out_of_range{CODE_POS_STR + "index 参数超出范围。"};
			}

			return Buffer()[index];
		}

		ItemType &operator[](int64_t index) const
		{
			return Get(index);
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
			try
			{
				std::stable_sort(Buffer(),
								 Buffer() + Count(),
								 [ascending](ItemType const &left, ItemType const &right) -> bool
								 {
									 if (ascending)
									 {
										 // std::stable_sort 函数的机制是如果谓语返回 true, 则将 left 排到 right
										 // 的前面，否则就不调整 left 和 right 的顺序。
										 //
										 // 如果返回的是 base::LessThan, 则小于的时候谓语返回 true, left 排到
										 // right 前面，那这就是升序排列，即从小到大排列。
										 return left < right;
									 }
									 else
									 {
										 return left > right;
									 }
								 });
			}
			catch (std::exception const &e)
			{
				throw std::runtime_error{CODE_POS_STR + e.what()};
			}
		}

		///
		/// @brief 排序。
		///
		/// @param compare 谓语。如果希望 left 排到 right 前面，则返回 true. 如果返回 false,
		/// 则 left 和 right 会保持当前相对顺序，不会调整。
		///
		/// @note 可以实现升序、降序排列。
		/// 	@li 如果 compare 在 left < right 时返回 true, 则实现的是升序排列。
		/// 	@li 如果 compare 在 left > right 时返回 true, 则实现的是降序排列。
		///
		template <typename parameter_type>
		void Sort(parameter_type const &compare)
			requires(std::is_convertible_v<parameter_type, std::function<bool(ItemType const &left, ItemType const &right)>>)
		{
			try
			{
				std::stable_sort(Buffer(),
								 Buffer() + Count(),
								 [&](ItemType const &left, ItemType const &right) -> bool
								 {
									 return compare(left, right);
								 });
			}
			catch (std::exception const &e)
			{
				throw std::runtime_error{CODE_POS_STR + e.what()};
			}
		}

		/* #endregion */

		///
		/// @brief 洗牌。
		///
		///
		void Shuffle()
		{
			std::vector<ItemType> temp_vec{};
			std::vector<int64_t> index_vec = base::ShuffleIndex(Count());
			for (int64_t index : index_vec)
			{
				temp_vec.push_back(Buffer()[index]);
			}

			base::ReadOnlyArraySpan<ItemType> temp_vec_span{
				temp_vec.data(),
				static_cast<int64_t>(temp_vec.size()),
			};

			CopyFrom(temp_vec_span);
		}

		operator base::Span() const
			requires(std::is_same_v<ItemType, uint8_t>)
		{
			return base::Span{Buffer(), Count()};
		}

		operator base::ReadOnlySpan() const
			requires(std::is_same_v<ItemType, uint8_t>)
		{
			return base::ReadOnlySpan{Buffer(), Count()};
		}

		///
		/// @brief 隐式转换为 base::ReadOnlyArraySpan.
		///
		/// @return
		///
		operator base::ReadOnlyArraySpan<ItemType>() const
		{
			base::ReadOnlyArraySpan ret{Buffer(), Count()};
			return ret;
		}

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
			return Iterator<ItemType const>{const_cast<ArraySpan *>(this), 0};
		}

		Iterator<ItemType const> end() const
		{
			return Iterator<ItemType const>{const_cast<ArraySpan *>(this), Count()};
		}
	};

} // namespace base
