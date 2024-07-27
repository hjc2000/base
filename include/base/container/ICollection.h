#pragma once

namespace base
{
	template <typename KeyType, typename ItemType>
	class IReadOnlyCollection
	{
	public:
		virtual int Count() const = 0;
		virtual ItemType Get(KeyType key) const = 0;
	};

	template <typename KeyType, typename ItemType>
	class ICollection
		: public IReadOnlyCollection<KeyType, ItemType>
	{
	public:
		virtual int Count() const = 0;
		virtual ItemType Get(KeyType key) const = 0;
		virtual void Put(KeyType key, ItemType const &item) = 0;
	};
}