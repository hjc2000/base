#pragma once
#include "base/container/iterator/IRandomAccessEnumerable.h"
#include "base/container/iterator/IRandomAccessEnumerator.h"
#include "base/container/Range.h"
#include "base/container/ReadOnlyArraySpan.h"
#include "base/math/random.h"
#include "base/sfinae/Compare.h"
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
	class ArraySpan final :
		public base::IRandomAccessEnumerable<ItemType>
	{
	private:
		/* #region 迭代器 */

		class RandomAccessEnumerator :
			public base::IRandomAccessEnumerator<ItemType>
		{
		private:
			int64_t _index = 0;
			ItemType *_buffer{};
			int64_t _count = 0;
			bool _has_not_moved = true;

		public:
			RandomAccessEnumerator(ItemType *buffer, int64_t count)
			{
				_buffer = buffer;
				_count = count;
			}

			///
			/// @brief 克隆一个迭代器对象副本。
			///
			/// @return
			///
			virtual std::shared_ptr<base::IRandomAccessEnumerator<ItemType>> Clone() const override
			{
				std::shared_ptr<base::IRandomAccessEnumerator<ItemType>> ret{new RandomAccessEnumerator{*this}};
				return ret;
			}

			///
			/// @brief 容器中总共有多少个元素。
			///
			/// @return
			///
			virtual int64_t Count() const override
			{
				return _count;
			}

			///
			/// @brief 当前迭代到的位置。
			///
			/// @return
			///
			virtual int64_t Position() const override
			{
				return _index;
			}

			///
			/// @brief 将迭代器位置增加 value.
			///
			/// @param value 增加的值。可以是正数和负数。
			///
			virtual void Add(int64_t value) override
			{
				_index += value;
			}

			///
			/// @brief 获取当前值的引用。
			///
			/// @note 迭代器构造后，如果被迭代的集合不为空，要立即让 CurrentValue 指向第一个有效元素。
			///
			/// @return
			///
			virtual ItemType &CurrentValue() override
			{
				return _buffer[_index];
			}

			///
			/// @brief 从未被调用过 MoveToNext 方法。
			///
			/// @return
			///
			virtual bool HasNotMoved() override
			{
				return _has_not_moved;
			}

			///
			/// @brief 设置是否从未被调用过 MoveToNext 方法。
			///
			/// @param value
			///
			virtual void SetHasNotMoved(bool value) override
			{
				_has_not_moved = value;
			}
		};

		/* #endregion */

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
		void Sort(std::function<bool(ItemType const &left, ItemType const &right)> const &compare)
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

		/* #region GetRandomAccessEnumerator */

		using base::IRandomAccessEnumerable<ItemType>::GetRandomAccessEnumerator;

		///
		/// @brief 获取非 const 迭代器
		///
		/// @return
		///
		virtual std::shared_ptr<base::IRandomAccessEnumerator<ItemType>> GetRandomAccessEnumerator() override
		{
			return std::shared_ptr<base::IRandomAccessEnumerator<ItemType>>{new RandomAccessEnumerator{Buffer(), Count()}};
		}

		/* #endregion */

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
	};

} // namespace base
