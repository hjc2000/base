#pragma once
#include "base/container/iterator/IEnumerable.h"
#include "base/container/Range.h"
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
	template <typename ItemType>
	class ArraySpan;

	template <typename ItemType>
	class ReadOnlyArraySpan;

	///
	/// @brief 只读的数组内存段。
	///
	/// @note 引用一段内存，不会持有这段内存，不管理这段内存的生命周期。
	///
	template <typename ItemType>
	class ReadOnlyArraySpan :
		public base::IEnumerable<ItemType const>
	{
	private:
		ItemType const *_buffer = nullptr;
		int32_t _count = 0;

		/* #region 迭代器 */

		class Enumerator :
			public base::IEnumerator<ItemType const>
		{
		private:
			int _index = 0;
			ItemType const *_buffer{};
			int32_t _count = 0;

		public:
			Enumerator(ItemType const *buffer, int32_t count)
			{
				_buffer = buffer;
				_count = count;
			}

			///
			/// @brief 迭代器当前是否指向尾后元素。
			///
			/// @return
			///
			virtual bool IsEnd() const override
			{
				return _index == _count;
			}

			///
			/// @brief 获取当前值的引用。
			///
			/// @return ItemType&
			///
			virtual ItemType const &CurrentValue() override
			{
				return _buffer[_index];
			}

			///
			/// @brief 递增迭代器的位置。
			///
			///
			virtual void Add() override
			{
				++_index;
			}
		};

		/* #endregion */

	public:
		/* #region 构造函数 */

		///
		/// @brief 构造函数。构造出来的对象不会引用任何有效内存段，且大小为 0.
		///
		///
		constexpr ReadOnlyArraySpan() = default;

		///
		/// @brief 构造函数。
		///
		/// @param buffer 要引用的内存段指针。
		/// @param count 要引用的内存段大小。
		///
		constexpr ReadOnlyArraySpan(ItemType const *buffer, int32_t count)
		{
			_buffer = buffer;
			_count = count;

			if (_buffer == nullptr)
			{
				_count = 0;
			}
		}

		constexpr ReadOnlyArraySpan(base::ArraySpan<ItemType> const &span)
		{
			_buffer = span.Buffer();
			_count = span.Count();

			if (_buffer == nullptr)
			{
				_count = 0;
			}
		}

		/* #endregion */

		///
		/// @brief 获取本对象引用的内存段。
		///
		/// @return
		///
		constexpr ItemType const *Buffer() const
		{
			return _buffer;
		}

		///
		/// @brief 本对象引用的内存段的元素个数。
		///
		/// @return
		///
		constexpr int32_t Count() const
		{
			return _count;
		}

		constexpr base::ReadOnlyArraySpan<ItemType> Slice(base::Range const &range) const
		{
			if (range.End() > Count())
			{
				throw std::out_of_range{"超出范围，无法切片。"};
			}

			return base::ReadOnlyArraySpan<ItemType>{Buffer() + range.Begin(), range.Size()};
		}

		/* #region GetEnumerator */

		using base::IEnumerable<ItemType const>::GetEnumerator;

		///
		/// @brief 获取迭代器。
		///
		/// @return
		///
		std::shared_ptr<IEnumerator<ItemType const>> GetEnumerator() override
		{
			return std::shared_ptr<IEnumerator<ItemType const>>{new Enumerator{Buffer(), Count()}};
		}

		/* #endregion */
	};

	///
	/// @brief 数组内存段。
	///
	/// @note 引用一段内存，不会持有这段内存，不管理这段内存的生命周期。
	///
	template <typename ItemType>
	class ArraySpan :
		public base::IEnumerable<ItemType>
	{
	private:
		ItemType *_buffer = nullptr;
		int32_t _count = 0;

		/* #region 迭代器 */

		class Enumerator :
			public base::IEnumerator<ItemType>
		{
		private:
			int _index = 0;
			ItemType *_buffer{};
			int32_t _count = 0;

		public:
			Enumerator(ItemType *buffer, int32_t count)
			{
				_buffer = buffer;
				_count = count;
			}

			///
			/// @brief 迭代器当前是否指向尾后元素。
			///
			/// @return
			///
			virtual bool IsEnd() const override
			{
				return _index == _count;
			}

			///
			/// @brief 获取当前值的引用。
			///
			/// @return ItemType&
			///
			virtual ItemType &CurrentValue() override
			{
				return _buffer[_index];
			}

			///
			/// @brief 递增迭代器的位置。
			///
			///
			virtual void Add() override
			{
				++_index;
			}
		};

		/* #endregion */

	public:
		/* #region 构造函数 */

		///
		/// @brief 构造函数。构造出来的对象不会引用任何有效内存段，且大小为 0.
		///
		///
		constexpr ArraySpan() = default;

		///
		/// @brief 构造函数。
		///
		/// @param buffer 要引用的内存段指针。
		/// @param count 要引用的内存段大小。
		///
		constexpr ArraySpan(ItemType *buffer, int32_t count)
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
		constexpr ItemType *Buffer() const
		{
			return _buffer;
		}

		///
		/// @brief 本对象引用的内存段的元素个数。
		///
		/// @return
		///
		constexpr int32_t Count() const
		{
			return _count;
		}

		///
		/// @brief 翻转本对象引用的内存段中的元素。
		///
		///
		constexpr void Reverse() const
		{
			std::reverse(_buffer, _buffer + _count);
		}

		/* #region CopyFrom */

		///
		/// @brief 将 another 的内存段的数据复制到本对象的内存段。
		///
		/// @param another
		///
		constexpr void CopyFrom(base::ReadOnlyArraySpan<ItemType> const &another) const
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
		constexpr void CopyFrom(base::ArraySpan<ItemType> const &another) const
		{
			CopyFrom(base::ReadOnlyArraySpan<ItemType>{another});
		}

		/* #endregion */

		constexpr base::ArraySpan<ItemType> Slice(base::Range const &range) const
		{
			if (range.End() > Count())
			{
				throw std::out_of_range{"超出范围，无法切片。"};
			}

			return base::ArraySpan<ItemType>{Buffer() + range.Begin(), range.Size()};
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
										 return base::LessThan(left, right);
									 }
									 else
									 {
										 return base::GreaterThan(left, right);
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
			std::vector<int32_t> index_vec = base::ShuffleIndex(Count());
			for (int32_t index : index_vec)
			{
				temp_vec.push_back(Buffer()[index]);
			}

			base::ReadOnlyArraySpan<ItemType> temp_vec_span{
				temp_vec.data(),
				static_cast<int32_t>(temp_vec.size()),
			};

			CopyFrom(temp_vec_span);
		}

		/* #region GetEnumerator */

		using IEnumerable<ItemType>::GetEnumerator;

		///
		/// @brief 获取迭代器。
		///
		/// @return std::shared_ptr<IEnumerator<ItemType>>
		///
		std::shared_ptr<IEnumerator<ItemType>> GetEnumerator() override
		{
			return std::shared_ptr<IEnumerator<ItemType>>{new Enumerator{Buffer(), Count()}};
		}

		/* #endregion */
	};
} // namespace base
