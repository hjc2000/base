#pragma once
#include "base/container/iterator/IEnumerator.h"
#include "ISet.h"
#include <base/container/ISet.h>
#include <cstdint>
#include <set>

namespace base
{
	///
	/// @brief 元素不重复的集合。
	///
	/// @tparam ItemType
	///
	template <typename ItemType>
	class Set :
		public base::ISet<ItemType>
	{
	private:
		std::set<ItemType> _set;

	private:
		/* #region 迭代器。 */

		class Enumerator :
			public base::IEnumerator<ItemType const>
		{
		private:
			std::set<ItemType> &_set;
			bool _move_to_next_for_the_first_time = true;

			using it_type = decltype(_set.begin());
			it_type _current;

		public:
			Enumerator(std::set<ItemType> &set)
				: _set(set)
			{
				Reset();
			}

		public:
			///
			/// @brief 获取当前值的引用
			///
			/// @return ItemType const&
			///
			virtual ItemType const &CurrentValue() override
			{
				return *_current;
			}

			///
			/// @brief 迭代器前进到下一个值
			///
			/// @return true
			/// @return false
			///
			virtual bool MoveNext() override
			{
				if (_set.size() == 0)
				{
					return false;
				}

				if (_move_to_next_for_the_first_time)
				{
					_move_to_next_for_the_first_time = false;
					return true;
				}

				++_current;
				if (_current == _set.end())
				{
					return false;
				}

				return true;
			}

			///
			/// @brief 将迭代器重置到容器开始的位置。
			///
			/// @note 开始位置是第一个元素前。也就是说重置后，要调用一次 MoveNext 才能获取到第一个值。
			///
			virtual void Reset() override
			{
				_move_to_next_for_the_first_time = true;
				_current = _set.begin();
			}
		};

		/* #endregion */

	public:
		///
		/// @brief 构造一个空集合。
		///
		///
		Set() = default;

		using base::ISet<ItemType>::Add;

		///
		/// @brief 向集合中添加一个元素。
		///
		/// @param item
		/// @return true 集合中原本没有该元素，添加成功。
		/// @return false 集合中原本已经有该元素了，添加失败。
		///
		virtual bool Add(ItemType const &item) override
		{
			auto pair = _set.insert(item);
			return pair.second;
		}

		using base::ISet<ItemType>::Remove;

		///
		/// @brief 移除指定的元素。
		///
		/// @param item
		/// @return true 集合中有该元素，移除成功。
		/// @return false 集合中没有该元素，移除失败。
		///
		virtual bool Remove(ItemType const &item) override
		{
			return _set.erase(item);
		}

		///
		/// @brief 检查是否存在指定元素。
		///
		/// @param item
		/// @return true
		/// @return false
		///
		virtual bool Contains(ItemType const &item) const override
		{
			return _set.contains(item);
		}

		///
		/// @brief 元素个数。
		///
		/// @return int32_t
		///
		virtual int32_t Count() const override
		{
			return _set.size();
		}

		///
		/// @brief 获取非 const 迭代器
		///
		/// @return std::shared_ptr<base::IEnumerator<ItemType const>>
		///
		virtual std::shared_ptr<base::IEnumerator<ItemType const>> GetEnumerator() override
		{
			return std::shared_ptr<base::IEnumerator<ItemType const>>{new Enumerator{_set}};
		}

	public:
		///
		/// @brief 两个集合拼接，组成并集。
		///
		/// @param another
		/// @return base::Set<ItemType>
		///
		base::Set<ItemType> operator+(base::ISet<ItemType> const &another) const
		{
			base::Set<ItemType> ret{*this};
			ret.Add(another);
			return ret;
		}

		///
		/// @brief 将本集合和 another 拼接，形成并集。或者说将 another 的元素全部添加到本集合中。
		///
		/// @param another
		/// @return base::Set<ItemType>&
		///
		base::Set<ItemType> &operator+=(base::ISet<ItemType> const &another)
		{
			Add(another);
			return *this;
		}

		///
		/// @brief 创建一个新集合，拷贝本集合，然后从新集合中移除 another 中含有的元素。
		///
		/// @param another
		/// @return base::Set<ItemType>
		///
		base::Set<ItemType> operator-(base::ISet<ItemType> const &another) const
		{
			base::Set<ItemType> ret{*this};
			ret.Remove(another);
			return ret;
		}

		///
		/// @brief 从本集合中移除 another 中含有的元素。
		///
		/// @param another
		/// @return base::Set<ItemType>&
		///
		base::Set<ItemType> &operator-=(base::ISet<ItemType> const &another)
		{
			Remove(another);
			return *this;
		}

		///
		/// @brief 求两个集合的交集。
		///
		/// @param another
		/// @return base::Set<ItemType>
		///
		base::Set<ItemType> operator*(base::ISet<ItemType> const &another)
		{
			base::Set<ItemType> ret{*this};
			for (ItemType const &item : _set)
			{
				if (another.Contains(item))
				{
					ret.Add(item);
				}
			}

			return ret;
		}

		///
		/// @brief 求本集合与 another 的交集，然后将本集合设置为该交集。
		///
		/// @param another
		/// @return base::Set<ItemType>
		///
		base::Set<ItemType> operator*=(base::ISet<ItemType> const &another)
		{
			base::Set<ItemType> temp = *this * another;
			*this = temp;
		}
	};
} // namespace base

#if HAS_THREAD
namespace base
{
	namespace test
	{
		void test_set();
	} // namespace test
} // namespace base
#endif
