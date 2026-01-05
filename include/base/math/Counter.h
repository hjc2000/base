#pragma once
#include "base/string/define.h"
#include <limits>
#include <stdexcept>
#include <type_traits>

namespace base
{
	///
	/// @brief 任意进制的计数器。
	///
	template <typename T>
		requires(std::is_unsigned_v<T>)
	class Counter final
	{
	private:
		T _max_value = std::numeric_limits<T>::max();
		T _count = 0;

	public:
		/* #region 构造函数 */

		constexpr Counter() = default;

		///
		/// @brief 构造一个任意进制的计数器。
		///
		/// @param current_value 计数器的当前值。
		/// @param max_value 计数器的最大值。
		///
		constexpr Counter(T current_value, T max_value)
		{
			if (max_value == 0)
			{
				throw std::invalid_argument{CODE_POS_STR + "计数的最大值不允许 == 0"};
			}

			if (current_value > max_value)
			{
				throw std::invalid_argument{CODE_POS_STR + "计数器的当前值不允许 > 计数器的最大值"};
			}

			_max_value = max_value;
			*this += current_value;
		}

		/* #endregion */

		/* #region 递增、递减 */

		///
		/// @brief 前缀递增
		///
		/// @return 返回递增后的值。
		///
		constexpr T operator++()
		{
			*this += 1;
			return _count;
		}

		///
		/// @brief 后缀递增
		///
		/// @return 返回递增前的值。
		///
		constexpr T operator++(int)
		{
			T record = _count;
			*this += 1;
			return record;
		}

		///
		/// @brief 前缀递减
		///
		/// @return
		///
		constexpr T operator--()
		{
			*this -= 1;
			return _count;
		}

		///
		/// @brief 后缀递减。
		///
		/// @return
		///
		constexpr T operator--(int)
		{
			T record = _count;
			*this -= 1;
			return record;
		}

		/* #endregion */

		/* #region 加减 */

		constexpr T operator+(T value) const
		{
			base::Counter<T> copy{*this};
			copy += value;
			return copy._count;
		}

		constexpr T operator+(base::Counter<T> const &other) const
		{
			return *this + other._count;
		}

		constexpr T operator-(T value) const
		{
			base::Counter<T> copy{*this};
			copy -= value;
			return copy._count;
		}

		constexpr T operator-(base::Counter<T> const &other) const
		{
			return *this - other._count;
		}

		/* #endregion */

		/* #region 自改变加减 */

		///
		/// @brief 将计数器的值增加指定的值
		///
		/// @param value
		///
		/// @return
		///
		constexpr T operator+=(T value)
		{
			if (_max_value == std::numeric_limits<T>::max())
			{
				_count += value;
				return _count;
			}

			// 将要加的值约束在一个最小正周期内。
			value %= _max_value + 1;

			// 剩余多少达到最大值
			T remain = _max_value - _count;

			if (value > remain)
			{
				// _count + value 会发生溢出

				// value 减去 remain, 然后假设 _count 已经加到最大值了。
				value -= remain;
				// _count = _max_value;

				// value 减去 1, 假设 _count 进一步加 1, 发生环绕，_count 变成 0.
				value -= 1;
				// _count = 0;

				// value 还剩下一点点，让为 0 的 _count 加上 value,
				// 相当于直接赋值。
				_count = value;
			}
			else
			{
				_count += value;
			}

			return _count;
		}

		///
		/// @brief 将计数器的值减去指定的值。
		///
		/// @param value
		///
		/// @return 返回运算后的值。
		///
		constexpr T operator-=(T value)
		{
			if (_max_value == std::numeric_limits<T>::max())
			{
				_count -= value;
				return _count;
			}

			// 将要减的值约束在一个最小正周期内。
			value %= _max_value + 1;

			if (value > _count)
			{
				// 假设将 _count 减到 0 后还剩下多少没减
				T remain = value - _count;

				// 前面已经假设 _count 减到 0 了，接着假设 _count 继续减 1,
				// 环绕到最大值了，此时还剩下多少没减
				remain -= 1;

				// 最大值减去剩余的没减的值
				_count = _max_value - remain;
			}
			else
			{
				_count -= value;
			}

			return _count;
		}

		/* #endregion */

		///
		/// @brief 重置计数值。计数值归 0.
		///
		constexpr void Reset()
		{
			_count = 0;
		}

		///
		/// @brief 计数器的当前值。
		///
		/// @return
		///
		constexpr T Value() const
		{
			return _count;
		}

		///
		/// @brief 计数器的当前值。
		///
		/// @param value
		///
		constexpr void SetValue(T value)
		{
			_count = 0;

			// 借助加法进行溢出回绕处理。
			*this += value;
		}

		constexpr explicit operator T() const
		{
			return _count;
		}

		/* #region 比较运算符 */

		constexpr bool operator==(base::Counter<T> const &other) const
		{
			return _count == other._count;
		}

		constexpr bool operator<(base::Counter<T> const &other) const
		{
			return _count < other._count;
		}

		constexpr bool operator>(base::Counter<T> const &other) const
		{
			return _count > other._count;
		}

		constexpr bool operator<=(base::Counter<T> const &other) const
		{
			return _count <= other._count;
		}

		constexpr bool operator>=(base::Counter<T> const &other) const
		{
			return _count >= other._count;
		}

		constexpr bool operator==(T other) const
		{
			return _count == other;
		}

		constexpr bool operator<(T other) const
		{
			return _count < other;
		}

		constexpr bool operator>(T other) const
		{
			return _count > other;
		}

		constexpr bool operator<=(T other) const
		{
			return _count <= other;
		}

		constexpr bool operator>=(T other) const
		{
			return _count >= other;
		}

		/* #endregion */
	};

} // namespace base
