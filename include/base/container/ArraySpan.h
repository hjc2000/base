#pragma once
#include "base/sfinae/Compare.h"
#include "base/string/define.h"
#include <algorithm>
#include <base/container/iterator/IEnumerable.h>
#include <base/container/Range.h>
#include <base/math/random.h>
#include <functional>
#include <stdexcept>
#include <stdint.h>
#include <vector>

namespace base
{
	template <typename ItemType>
	class ArraySpan;

	template <typename ItemType>
	class ReadOnlyArraySpan;

	/**
	 * @brief 只读的数组内存段。
	 *
	 * @note 引用一段内存，不会持有这段内存，不管理这段内存的生命周期。
	 *
	 * @tparam ItemType
	 */
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
			bool _first_move = true;
			ItemType const *_buffer{};
			int32_t _count = 0;

		public:
			Enumerator(ItemType const *buffer, int32_t count)
			{
				_buffer = buffer;
				_count = count;
				Reset();
			}

			/**
			 * @brief 获取当前值的引用
			 *
			 * @return ItemType const&
			 */
			ItemType const &CurrentValue() override
			{
				return _buffer[_index];
			}

			/**
			 * @brief 迭代器前进到下一个值。
			 *
			 * @return true
			 * @return false
			 */
			bool MoveNext() override
			{
				if (_first_move)
				{
					_first_move = false;
				}
				else
				{
					_index++;
				}

				if (_index < 0 || _index >= _count)
				{
					return false;
				}

				return true;
			}

			/**
			 * @brief 将迭代器重置到容器开始的位置。
			 *
			 * @note 开始位置是第一个元素前。也就是说重置后，要调用一次 MoveNext 才能获取到第一个值。
			 */
			void Reset() override
			{
				_first_move = true;
				_index = 0;
			}
		};

		/* #endregion */

	public:
		/* #region 构造函数 */

		///
		/// @brief 构造函数。构造出来的对象不会引用任何有效内存段，且大小为 0.
		///
		///
		ReadOnlyArraySpan() = default;

		///
		/// @brief 构造函数。
		///
		/// @param buffer 要引用的内存段指针。
		/// @param count 要引用的内存段大小。
		///
		ReadOnlyArraySpan(ItemType const *buffer, int32_t count)
		{
			_buffer = buffer;
			_count = count;

			if (_buffer == nullptr)
			{
				_count = 0;
			}
		}

		ReadOnlyArraySpan(base::ArraySpan<ItemType> const &span)
		{
			_buffer = span.Buffer();
			_count = span.Count();

			if (_buffer == nullptr)
			{
				_count = 0;
			}
		}

		/* #endregion */

		/**
		 * @brief 获取本对象引用的内存段。
		 *
		 * @return ItemType const*
		 */
		ItemType const *Buffer() const
		{
			return _buffer;
		}

		/**
		 * @brief 本对象引用的内存段的元素个数。
		 *
		 * @return int32_t
		 */
		int32_t Count() const
		{
			return _count;
		}

		base::ReadOnlyArraySpan<ItemType> Slice(base::Range const &range) const
		{
			if (range.End() > Count())
			{
				throw std::out_of_range{"超出范围，无法切片。"};
			}

			return base::ReadOnlyArraySpan<ItemType>{Buffer() + range.Begin(), range.Size()};
		}

		/**
		 * @brief 获取迭代器
		 *
		 * @return std::shared_ptr<IEnumerator<ItemType const>>
		 */
		std::shared_ptr<IEnumerator<ItemType const>> GetEnumerator() override
		{
			return std::shared_ptr<IEnumerator<ItemType const>>{new Enumerator{Buffer(), Count()}};
		}
	};

	/**
	 * @brief 数组内存段。
	 *
	 * @note 引用一段内存，不会持有这段内存，不管理这段内存的生命周期。
	 *
	 * @tparam ItemType
	 */
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
			bool _first_move = true;
			ItemType *_buffer{};
			int32_t _count = 0;

		public:
			Enumerator(ItemType *buffer, int32_t count)
			{
				_buffer = buffer;
				_count = count;
				Reset();
			}

			/**
			 * @brief 获取当前值的引用。
			 *
			 * @return ItemType&
			 */
			ItemType &CurrentValue() override
			{
				return _buffer[_index];
			}

			/**
			 * @brief 迭代器前进到下一个值。
			 *
			 * @return true
			 * @return false
			 */
			bool MoveNext() override
			{
				if (_first_move)
				{
					_first_move = false;
				}
				else
				{
					_index++;
				}

				if (_index < 0 || _index >= _count)
				{
					return false;
				}

				return true;
			}

			/**
			 * @brief 将迭代器重置到容器开始的位置。
			 *
			 * @note 开始位置是第一个元素前。也就是说重置后，要调用一次 MoveNext 才能获取到第一个值。
			 */
			void Reset() override
			{
				_first_move = true;
				_index = 0;
			}
		};

		/* #endregion */

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
		ArraySpan(ItemType *buffer, int32_t count)
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

		/**
		 * @brief 本对象引用的内存段的元素个数。
		 *
		 * @return int32_t
		 */
		int32_t Count() const
		{
			return _count;
		}

		/**
		 * @brief 翻转本对象引用的内存段中的元素。
		 *
		 */
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
				throw std::invalid_argument{"another 的 Count 属性必须和本对象的 Count 属性相等。"};
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
		/// @param compare 自定义比较器。如果 left 小于 right，则返回小于 0 的值，如果相等，则返回 0，
		/// 如果 left 大于 right 则返回大于 0 的值。
		///
		/// @param ascending 是否按升序排序，即从小到大排序。传入 true 则按升序排序，传入 false 则按降序排序。
		///
		void Sort(std::function<int(ItemType const &left, ItemType const &right)> compare,
				  bool ascending = true)
		{
			try
			{
				std::stable_sort(Buffer(),
								 Buffer() + Count(),
								 [&](ItemType const &left, ItemType const &right) -> bool
								 {
									 if (ascending)
									 {
										 return compare(left, right) < 0;
									 }
									 else
									 {
										 return compare(left, right) > 0;
									 }
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
			std::vector<int32_t> index_vec = base::di::ShuffleIndex(Count());
			for (int32_t index : index_vec)
			{
				temp_vec.push_back(Buffer()[index]);
			}

			CopyFrom(base::ReadOnlyArraySpan<ItemType>{temp_vec.data(), static_cast<int32_t>(temp_vec.size())});
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
