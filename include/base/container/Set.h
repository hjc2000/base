#pragma once
#include "base/container/ISet.h"
#include "ISet.h"
#include "iterator/IBidirectionalIterator.h"
#include <cstdint>
#include <initializer_list>
#include <memory>
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
		using std_set_iterator_type = decltype(std::set<ItemType>{}.begin());

		class Iterator :
			public base::IBidirectionalIterator<ItemType const>
		{
		private:
			std_set_iterator_type _it{};

		public:
			Iterator(std_set_iterator_type const &iterator)
				: _it{iterator}
			{
			}

			///
			/// @brief 派生类利用拷贝构造函数拷贝一个自己，然后返回。
			///
			/// @return
			///
			virtual std::shared_ptr<base::IBidirectionalIterator<ItemType const>> Clone() override
			{
				return std::shared_ptr<Iterator>{new Iterator{*this}};
			}

			///
			/// @brief 返回当前迭代器指向的对象的引用。
			///
			/// @return
			///
			virtual ItemType const &Current() override
			{
				return *_it;
			}

			virtual void Increment() override
			{
				++_it;
			}

			virtual void Decrement() override
			{
				--_it;
			}

			virtual bool Equal(base::IBidirectionalIterator<ItemType const> const &other) const override
			{
				return _it == static_cast<Iterator const &>(other)._it;
			}
		};

	private:
		std::set<ItemType> _set;

	public:
		/* #region 构造函数 */

		Set() = default;

		Set(std::initializer_list<ItemType> list)
		{
			for (auto &item : list)
			{
				Add(item);
			}
		}

		Set(ISet<ItemType> const &set)
		{
			for (ItemType const &item : set)
			{
				Add(item);
			}
		}

		/* #endregion */

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
		/// @brief 清空元素。
		///
		/// @return
		///
		virtual void Clear() override
		{
			_set.clear();
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
		/// @return int64_t
		///
		virtual int64_t Count() const override
		{
			return _set.size();
		}

		virtual std::shared_ptr<base::IBidirectionalIterator<ItemType const>> BeginIterator() override
		{
			return std::shared_ptr<Iterator>{new Iterator{_set.begin()}};
		}

		virtual std::shared_ptr<base::IBidirectionalIterator<ItemType const>> EndIterator() override
		{
			return std::shared_ptr<Iterator>{new Iterator{_set.end()}};
		}

		/* #region GetEnumerator */

		/* #endregion */

		/* #region 集合运算符 */

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
		/// @brief 求两个集合的交集。
		///
		/// @param another
		/// @return base::Set<ItemType>
		///
		base::Set<ItemType> operator*(base::ISet<ItemType> const &another)
		{
			base::Set<ItemType> ret{};
			for (ItemType const &item : _set)
			{
				if (another.Contains(item))
				{
					ret.Add(item);
				}
			}

			return ret;
		}

		/* #endregion */

		/* #region 自改变集合运算符 */

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
		/// @brief 求本集合与 another 的交集，然后将本集合设置为该交集。
		///
		/// @param another
		/// @return base::Set<ItemType>
		///
		base::Set<ItemType> &operator*=(base::ISet<ItemType> const &another)
		{
			base::Set<ItemType> temp = *this * another;
			*this = temp;
			return *this;
		}

		/* #endregion */
	};

} // namespace base
