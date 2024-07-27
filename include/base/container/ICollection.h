#pragma once
#include <array>

namespace base
{
	/// @brief 只读集合接口。
	/// @tparam KeyType
	/// @tparam ItemType
	template <typename KeyType, typename ItemType>
	class IReadOnlyCollection
	{
	public:
		virtual int Count() const = 0;
		virtual ItemType Get(KeyType key) const = 0;
	};

	/// @brief 集合接口。
	/// @tparam KeyType
	/// @tparam ItemType
	template <typename KeyType, typename ItemType>
	class ICollection
		: public IReadOnlyCollection<KeyType, ItemType>
	{
	public:
		ICollection() = default;

		virtual int Count() const = 0;
		virtual ItemType Get(KeyType key) const = 0;
		virtual void Put(KeyType key, ItemType const &item) = 0;
	};

	template <int ItemCount, typename ItemType>
	class ArrayCollection
		: public base::ICollection<int, ItemType>
	{
	private:
		std::array<ItemType, ItemCount> &_array;

	public:
		ArrayCollection(std::array<ItemType, ItemCount> array)
			: _array(array)
		{
		}

		ArrayCollection(std::array<ItemType, ItemCount> &array)
			: _array(array)
		{
		}

		int Count() const override
		{
			return static_cast<int>(_array.size());
		}

		ItemType Get(int key) const override
		{
			return _array[key];
		}

		void Put(int key, ItemType const &item) override
		{
			_array[key] = item;
		}
	};
}
