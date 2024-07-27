#pragma once

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
}