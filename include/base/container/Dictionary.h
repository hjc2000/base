#pragma once
#include "base/container/IDictionary.h"
#include <map>

namespace base
{
	/// @brief 字典
	/// @tparam KeyType
	/// @tparam ValueType
	template <typename KeyType, typename ValueType>
	class Dictionary :
		public base::IDictionary<KeyType, ValueType>
	{
	private:
		std::map<KeyType, ValueType> _map{};

		class Enumerator :
			public IEnumerator<std::pair<KeyType const, ValueType>>
		{
		private:
			std::map<KeyType, ValueType> *_map = nullptr;
			bool _first_move = true;

			/// @brief _map 的迭代器类型
			using IteratorType = decltype(_map->begin());
			IteratorType _it;

		public:
			Enumerator(std::map<KeyType, ValueType> *map)
			{
				_map = map;
				Reset();
			}

			/// @brief 获取当前值的引用
			/// @return
			std::pair<KeyType const, ValueType> &CurrentValue() override
			{
				return *_it;
			}

			/// @brief 迭代器前进到下一个值
			/// @return
			bool MoveNext() override
			{
				if (_first_move)
				{
					_first_move = false;
				}
				else
				{
					++_it;
				}

				if (_it == _map->end())
				{
					return false;
				}

				return true;
			}

			/// @brief 将迭代器重置到容器开始的位置。
			/// @note 开始位置是第一个元素前。也就是说重置后，要调用一次 MoveNext 才能获取到第一个值。
			void Reset() override
			{
				_it = _map->begin();
				_first_move = true;
			}
		};

	public:
		/// @brief 构造一个空字典。
		Dictionary() = default;

		/// @brief 从 map 中构造。将 map 的元素复制过来。
		/// @param o
		Dictionary(std::map<KeyType, ValueType> const &o)
		{
			_map = o;
		}

		Dictionary(std::initializer_list<std::pair<KeyType, ValueType>> const &list)
		{
			Add(list);
		}

	public:
		using base::IDictionary<KeyType, ValueType>::Add;

		/// @brief 获取元素个数。
		/// @return
		int Count() const override
		{
			return _map.size();
		}

		/// @brief 查找元素。
		/// @param key 键
		/// @return 指针。找到了返回元素的指针，找不到返回空指针。
		ValueType *Find(KeyType const &key) override
		{
			auto it = _map.find(key);
			if (it == _map.end())
			{
				return nullptr;
			}

			return &it->second;
		}

		/// @brief 移除一个元素。
		/// @param key 键
		/// @return 移除成功返回 true，元素不存在返回 false。
		bool Remove(KeyType const &key) override
		{
			auto it = _map.find(key);
			if (it != _map.end())
			{
				_map.erase(it);
				return true;
			}

			return false;
		}

		/// @brief 设置一个元素。本来不存在，会添加；本来就存在了，会覆盖。
		/// @param key
		/// @param value
		void Set(KeyType const &key, ValueType const &value) override
		{
			_map[key] = value;
		}

		/// @brief 获取迭代器
		/// @return
		std::shared_ptr<IEnumerator<std::pair<KeyType const, ValueType>>> GetEnumerator() override
		{
			return std::shared_ptr<IEnumerator<std::pair<KeyType const, ValueType>>>{new Enumerator{&_map}};
		}
	};
} // namespace base
