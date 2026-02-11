#pragma once
#include <new> // IWYU pragma: keep
#include <utility>

namespace base
{
	///
	/// @brief 让无法拷贝和移动的 std::pair 模板实例类对象支持拷贝和移动。
	///
	///
	template <typename TKey, typename TValue>
	class StdPairWrapper
	{
	private:
		std::pair<TKey, TValue> _pair;

	public:
		constexpr StdPairWrapper() = default;

		constexpr StdPairWrapper(TKey const &key, TValue const &value)
			: _pair(key, value)
		{
		}

		constexpr StdPairWrapper(std::pair<TKey, TValue> const &pair)
			: _pair(pair)
		{
		}

		constexpr StdPairWrapper(base::StdPairWrapper<TKey, TValue> const &other)
		{
			*this = other;
		}

		constexpr StdPairWrapper(base::StdPairWrapper<TKey, TValue> &&other)
		{
			*this = other;
		}

		constexpr base::StdPairWrapper<TKey, TValue> &operator=(base::StdPairWrapper<TKey, TValue> const &other)
		{
			*this = other._pair;
			return *this;
		}

		constexpr base::StdPairWrapper<TKey, TValue> &operator=(base::StdPairWrapper<TKey, TValue> &&other)
		{
			*this = std::move(other._pair);
			return *this;
		}

		constexpr base::StdPairWrapper<TKey, TValue> &operator=(std::pair<TKey, TValue> const &other)
		{
			_pair.~pair();

			new (&_pair) std::pair<TKey, TValue>{
				other.first,
				other.second,
			};

			return *this;
		}

		constexpr base::StdPairWrapper<TKey, TValue> &operator=(std::pair<TKey, TValue> &&other)
		{
			_pair.~pair();

			new (&_pair) std::pair<TKey, TValue>{
				std::move(other.first),
				std::move(other.second),
			};

			return *this;
		}

		std::pair<TKey, TValue> &Pair()
		{
			return _pair;
		}

		std::pair<TKey, TValue> const &Pair() const
		{
			return _pair;
		}
	};

} // namespace base
