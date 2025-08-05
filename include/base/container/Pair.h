#pragma once

namespace base
{
	template <typename TKey, typename TValue>
	class Pair
	{
	private:
		TKey _key{};
		TValue _value{};

	public:
		constexpr Pair() = default;

		constexpr Pair(TKey const &key, TValue const &value)
			: _key(key),
			  _value(value)
		{
		}

		constexpr TKey Key() const
		{
			return _key;
		}

		constexpr TValue Value() const
		{
			return _value;
		}
	};

} // namespace base
