#pragma once
#include <algorithm>
#include <base/container/IList.h>
#include <base/container/IRawArray.h>
#include <base/sfinae/Equal.h>
#include <cstdint>
#include <stdexcept>
#include <vector>

namespace base
{
	/**
	 * @brief 基于 std::vector 的列表。
	 *
	 * @tparam ItemType
	 */
	template <typename ItemType>
	class List final :
		public base::IList<ItemType>,
		public base::IRawArray<ItemType>
	{
	private:
		std::vector<ItemType> _vector;

	public:
		// 构造函数

		/**
		 * @brief 构造一个空列表。
		 *
		 */
		List() = default;

		/**
		 * @brief 从向量中构造。将向量的元素拷贝过来。
		 *
		 * @param o
		 */
		List(std::vector<ItemType> const &o)
		{
			_vector = o;
		}

		List(std::initializer_list<ItemType> const &list)
		{
			_vector = list;
		}

	public:
		using IList<ItemType>::Add;

		void Add(ItemType const &item) override
		{
			_vector.push_back(item);
		}

		void Insert(int32_t const index, ItemType const &item) override
		{
			if (index < 0 || index > static_cast<int32_t>(_vector.size()))
			{
				throw std::out_of_range{"索引超出范围"};
			}

			_vector.insert(_vector.begin() + index, item);
		}

		bool Remove(ItemType const &item) override
		{
			auto it = std::find_if(_vector.begin(),
								   _vector.end(),
								   [&](ItemType const &p)
								   {
									   return base::Equal(p, item);
								   });

			if (it != _vector.end())
			{
				_vector.erase(it);
				return true; // 返回 true 表示成功找到并删除了元素
			}

			// 如果没有找到元素，返回 false
			return false;
		}

		void RemoveAt(int32_t const index) override
		{
			if (index < 0 || index >= static_cast<int32_t>(_vector.size()))
			{
				throw std::out_of_range{"索引超出范围"};
			}

			_vector.erase(_vector.begin() + index);
		}

		/**
		 * @brief 移除符合条件的数据。
		 *
		 * @param should_remove 用来指示特定的元素是否应该从容器中移除。
		 */
		virtual void RemoveIf(std::function<bool(ItemType const &item)> should_remove) override
		{
			/* remove_if 函数会将容器的符合移除条件的元素移动到容器末尾，最后返回一个迭代器，
			 * 从这个迭代器指向的位置开始到容器末尾的元素，全是满足移除条件的。
			 */
			auto remove_begin = std::remove_if(
				_vector.begin(),
				_vector.end(),
				[&](ItemType const &item)
				{
					return should_remove(item);
				});

			_vector.erase(remove_begin, _vector.end());
		}

		int32_t IndexOf(ItemType const &item) const override
		{
			auto it = std::find_if(_vector.begin(),
								   _vector.end(),
								   [&](ItemType const &p)
								   {
									   return base::Equal(p, item);
								   });

			if (it != _vector.end())
			{
				return static_cast<int32_t>(std::distance(_vector.begin(), it)); // 返回元素的索引
			}

			// 如果没有找到元素，返回 -1
			return -1;
		}

		bool Contains(ItemType const &item) const override
		{
			auto it = std::find_if(_vector.begin(),
								   _vector.end(),
								   [&](ItemType const &p)
								   {
									   return base::Equal(p, item);
								   });

			return it != _vector.end();
		}

		void Clear() override
		{
			_vector.clear();
		}

		int32_t Count() const override
		{
			return static_cast<int32_t>(_vector.size());
		}

		ItemType &operator[](int32_t const index) override
		{
			if (index < 0 || index >= static_cast<int32_t>(_vector.size()))
			{
				throw std::out_of_range{"索引超出范围"};
			}

			return _vector[index];
		}

		ItemType const &operator[](int32_t const index) const override
		{
			if (index < 0 || index >= static_cast<int32_t>(_vector.size()))
			{
				throw std::out_of_range{"索引超出范围"};
			}

			return _vector[index];
		}

		/**
		 * @brief 将本列表内的元素拷贝到向量中。
		 *
		 * @return std::vector<ItemType>
		 */
		std::vector<ItemType> ToVector()
		{
			// 直接返回，利用 vector 的拷贝构造函数。
			return _vector;
		}

		/**
		 * @brief 获取底层的缓冲区
		 *
		 * @return ItemType*
		 */
		virtual ItemType *Buffer() override
		{
			return _vector.data();
		}

		/**
		 * @brief 获取底层的缓冲区
		 *
		 * @return ItemType const*
		 */
		virtual ItemType const *Buffer() const override
		{
			return _vector.data();
		}

		/**
		 * @brief 转发到 std::vector 的相等判断逻辑。
		 *
		 * @param another
		 * @return true
		 * @return false
		 */
		bool operator==(List<ItemType> const &another) const
		{
			return _vector == another._vector;
		}

		virtual std::shared_ptr<IEnumerator<ItemType>> GetEnumerator() override
		{
			return base::IRawArray<ItemType>::GetEnumerator();
		}
	};
} // namespace base
