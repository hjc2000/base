#pragma once
#include <base/container/IEnumerable.h>
#include <map>

namespace base
{
	template <typename KeyType, typename ItemType>
	class StdMapValuesEnumerator
		: public base::IEnumerator<ItemType>
	{
	private:
		std::map<KeyType, ItemType> *_map;
		decltype(_map->begin()) _current_it;
		bool _first_move = true;

	public:
		StdMapValuesEnumerator(std::map<KeyType, ItemType> *map)
		{
			_map = map;
			Reset();
		}

		ItemType &CurrentValue() override
		{
			return _current_it->second;
		}

		bool MoveNext() override
		{
			if (_first_move)
			{
				_current_it = _map->begin();
			}
			else
			{
				_current_it++;
			}

			return _current_it != _map->end();
		}

		void Reset() override
		{
			_current_it = _map->begin();
		}
	};

	template <typename KeyType, typename ItemType>
	class StdMapValuesEnumerable
		: base::IEnumerable<ItemType>
	{
	private:
		std::shared_ptr<std::map<KeyType, ItemType>> _map;

	public:
		StdMapValuesEnumerable(std::shared_ptr<std::map<KeyType, ItemType>> map)
		{
			_map = map;
		}

		std::shared_ptr<IEnumerator<ItemType>> GetEnumerator() override
		{
			return std::shared_ptr<IEnumerator<ItemType>>{
				new StdMapValuesEnumerator<KeyType, ItemType>{_map},
			};
		}
	};
}
