#pragma once
#include "base/container/IDictionary.h"
#include <cstdint>
#include <map>

namespace base
{
	///
	/// @brief 字典
	///
	template <typename KeyType, typename ValueType>
	class Dictionary :
		public base::IDictionary<KeyType, ValueType>
	{
	private:
		/* #region Enumerator */

		class Enumerator :
			public IEnumerator<std::pair<KeyType const, ValueType>>
		{
		private:
			using IteratorType = decltype(std::map<KeyType, ValueType>{}.begin());
			IteratorType _current;
			IteratorType _end;
			base::IEnumerator<std::pair<KeyType const, ValueType>>::Context_t _context{};

		public:
			Enumerator(std::map<KeyType, ValueType> &map)
			{
				_current = map.begin();
				_end = map.end();
			}

			///
			/// @brief 迭代器当前是否指向尾后元素。
			///
			/// @return
			///
			virtual bool IsEnd() const override
			{
				return _current == _end;
			}

			///
			/// @brief 获取当前值的引用。
			///
			/// @return ItemType&
			///
			virtual std::pair<KeyType const, ValueType> &CurrentValue() override
			{
				return *_current;
			}

			///
			/// @brief 递增迭代器的位置。
			///
			///
			virtual void Add() override
			{
				++_current;
			}

			///
			/// @brief 派生类需要提供一个该对象。
			///
			/// @return
			///
			virtual base::IEnumerator<std::pair<KeyType const, ValueType>>::Context_t &Context() override
			{
				return _context;
			}
		};

		/* #endregion */

		std::map<KeyType, ValueType> _map{};

	public:
		/* #region 构造函数 */

		/// @brief 构造一个空字典。
		Dictionary() = default;

		/// @brief 从 map 中构造。将 map 的元素复制过来。
		/// @param o
		Dictionary(std::map<KeyType, ValueType> const &o)
		{
			_map = o;
		}

		Dictionary(std::initializer_list<std::pair<KeyType const, ValueType>> const &list)
		{
			base::IDictionary<KeyType, ValueType>::Add(list);
		}

		/* #endregion */

		///
		/// @brief 获取元素个数。
		///
		/// @return
		///
		virtual int64_t Count() const override
		{
			return _map.size();
		}

		///
		/// @brief 查找元素。
		/// @param key 键
		///
		/// @return 指针。找到了返回元素的指针，找不到返回空指针。
		///
		virtual ValueType *Find(KeyType const &key) override
		{
			auto it = _map.find(key);
			if (it == _map.end())
			{
				return nullptr;
			}

			return &it->second;
		}

		///
		/// @brief 移除一个元素。
		///
		/// @param key 键
		/// @return 移除成功返回 true，元素不存在返回 false。
		///
		virtual bool Remove(KeyType const &key) override
		{
			auto it = _map.find(key);
			if (it != _map.end())
			{
				_map.erase(it);
				return true;
			}

			return false;
		}

		///
		/// @brief 清空所有元素。
		///
		///
		virtual void Clear() override
		{
			_map.clear();
		}

		///
		/// @brief 设置一个元素。本来不存在，会添加；本来就存在了，会覆盖。
		///
		/// @param key
		/// @param value
		///
		virtual void Set(KeyType const &key, ValueType const &value) override
		{
			_map[key] = value;
		}

		using base::IEnumerable<std::pair<KeyType const, ValueType>>::GetEnumerator;

		///
		/// @brief 获取迭代器
		///
		/// @return
		///
		virtual std::shared_ptr<IEnumerator<std::pair<KeyType const, ValueType>>> GetEnumerator() override
		{
			return std::shared_ptr<IEnumerator<std::pair<KeyType const, ValueType>>>{new Enumerator{_map}};
		}
	};

} // namespace base
