#pragma once
#include <cstdint>
#include <new> // IWYU pragma: keep
#include <utility>

namespace base
{
	template <typename T>
	class Placement
	{
	private:
		bool _available = false;
		alignas(T) uint8_t _buffer[sizeof(T)];

	public:
		Placement() = default;

		Placement(Placement const &other)
		{
			*this = other;
		}

		Placement(Placement &&other)
		{
			*this = other;
		}

		Placement(T const &value)
		{
			new (_buffer) T{value};
			_available = true;
		}

		Placement(T &&value)
		{
			new (_buffer) T{value};
			_available = true;
		}

		~Placement()
		{
			if (_available)
			{
				reinterpret_cast<T *>(_buffer)->~T();
			}
		}

		Placement &operator=(Placement const &other)
		{
			if (other._available)
			{
				// other 有效。
				if (_available)
				{
					// 本对象有效。
					Object() = other.Object();
				}
				else
				{
					// 本对象无效。
					new (_buffer) T{other.Object()};
					_available = true;
				}

				return *this;
			}

			// other 无效。
			if (_available)
			{
				// 本对象有效。
				reinterpret_cast<T *>(_buffer)->~T();
				_available = false;
			}

			return *this;
		}

		Placement &operator=(Placement &&other)
		{
			if (other._available)
			{
				// other 有效。
				if (_available)
				{
					// 本对象有效。
					Object() = std::move(other.Object());
				}
				else
				{
					// 本对象无效。
					new (_buffer) T{std::move(other.Object())};
					_available = true;
				}

				return *this;
			}

			// other 无效。
			if (_available)
			{
				// 本对象有效。
				reinterpret_cast<T *>(_buffer)->~T();
				_available = false;
			}

			return *this;
		}

		///
		/// @brief 本对象中占位的字节数组中是否构造了有效的 T 对象。
		///
		/// @return
		///
		bool Avalable() const
		{
			return _available;
		}

		T *operator->()
		{
			return reinterpret_cast<T *>(_buffer);
		}

		T const *operator->() const
		{
			return reinterpret_cast<T const *>(_buffer);
		}

		///
		/// @brief 获取本对象中占位的字节数组中存储的 T 对象。
		///
		/// @return
		///
		T &operator*()
		{
			return *reinterpret_cast<T *>(_buffer);
		}

		///
		/// @brief 获取本对象中占位的字节数组中存储的 T 对象。
		///
		/// @return
		///
		T const &operator*() const
		{
			return *reinterpret_cast<T const *>(_buffer);
		}

		///
		/// @brief 获取本对象中占位的字节数组中存储的 T 对象。
		///
		/// @return
		///
		T &Object()
		{
			return *reinterpret_cast<T *>(_buffer);
		}

		///
		/// @brief 获取本对象中占位的字节数组中存储的 T 对象。
		///
		/// @return
		///
		T const &Object() const
		{
			return *reinterpret_cast<T const *>(_buffer);
		}
	};

} // namespace base
