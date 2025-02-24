#pragma once
#include <base/container/iterator/IEnumerable.h>

namespace base
{
	/// @brief 集合接口。
	/// @note 集合被迭代的仅仅是元素，而不是键值对。这点与字典不同。
	/// @tparam KeyType
	/// @tparam ValueType
	template <typename KeyType, typename ValueType>
	class IDictionary :
		public base::IEnumerable<std::pair<KeyType const, ValueType>>
	{
	public:
		/// @brief 获取元素个数。
		/// @return
		virtual int Count() const = 0;

		/// @brief 查找元素。
		/// @param key 键
		/// @return 指针。找到了返回元素的指针，找不到返回空指针。
		virtual ValueType *Find(KeyType const &key) = 0;

		/// @brief 移除一个元素。
		/// @param key 键
		/// @return 移除成功返回 true，元素不存在返回 false。
		virtual bool Remove(KeyType const &key) = 0;

		/// @brief 设置一个元素。本来不存在，会添加；本来就存在了，会覆盖。
		/// @param key
		/// @param item
		virtual void Set(KeyType const &key, ValueType const &item) = 0;

		/// @brief 获取迭代器
		/// @return
		virtual std::shared_ptr<IEnumerator<std::pair<KeyType const, ValueType>>> GetEnumerator() = 0;

		/// @brief 获取元素。找不到会抛出异常。
		/// @param key
		/// @return
		ValueType &Get(KeyType const &key)
		{
			ValueType *p = Find(key);
			if (p == nullptr)
			{
				throw std::runtime_error{"找不到元素"};
			}

			return *p;
		}

		/// @brief 获取元素。找不到会抛出异常。
		/// @param key
		/// @return
		ValueType const &Get(KeyType const &key) const
		{
			return const_cast<IDictionary<KeyType, ValueType> *>(this)->Get(key);
		}

		/// @brief 查找元素。
		/// @param key 键
		/// @return 指针。找到了返回元素的指针，找不到返回空指针。
		ValueType const *Find(KeyType const &key) const
		{
			ValueType *p = const_cast<IDictionary<KeyType, ValueType> *>(this)->Find(key);
			return p;
		}

		/// @brief 检查字典中是否包含指定的键。
		/// @param key
		/// @return 包含则返回 true，不包含则返回 false。
		bool Contains(KeyType const &key) const
		{
			ValueType *p = const_cast<IDictionary<KeyType, ValueType> *>(this)->Find(key);
			if (p == nullptr)
			{
				return false;
			}

			return true;
		}

		/// @brief 添加一个键值对到字典中。如果此键已经存在，会抛出异常。
		/// @param key
		/// @param item
		void Add(KeyType const &key, ValueType const &item)
		{
			if (Contains(key))
			{
				throw std::runtime_error{"此键已经存在，无法添加"};
			}

			// 原本没有，添加
			Set(key, item);
		}

		/// @brief 添加一个键值对到字典中。如果此键已经存在，会抛出异常。
		/// @param pair
		void Add(std::pair<KeyType, ValueType> const &pair)
		{
			Add(pair.first, pair.second);
		}

		/// @brief 将列表中的键值对添加到字典中。添加过程中，如果键重复，会抛出异常。
		/// @param list
		void Add(std::initializer_list<std::pair<KeyType, ValueType>> const &list)
		{
			for (auto &pair : list)
			{
				Add(pair);
			}
		}
	};
} // namespace base
