#pragma once
#include <stdexcept>
#include <stdint.h>

namespace base
{
	/// @brief 计数器。计数到最大值后会归 0.
	/// @tparam T 此类型必须是无符号整型
	template <typename T>
	class Counter final
	{
	private:
		T _max_value;
		T _count = 0;

		/// @brief 递增计数。递增到最大之后，再次递增会归 0.
		void IncCount()
		{
			if (_count == _max_value)
			{
				_count = 0;
				return;
			}

			_count++;
		}

		/// @brief 递减计数。递减到 0 后再次递减会变成最大值。
		void DecCount()
		{
			if (_count == 0)
			{
				_count = _max_value;
				return;
			}

			_count--;
		}

	public:
		/// @brief
		/// @param max_value 计数器的最大值
		Counter(T max_value)
		{
			if (max_value == 0)
			{
				throw std::invalid_argument{"计数的最大值不允许 == 0"};
			}

			_max_value = max_value;
		}

#pragma region 运算符重载
		/// @brief 前缀递增
		/// @return 返回递增后的值。
		T operator++()
		{
			IncCount();
			return _count;
		}

		/// @brief 后缀递增
		/// @param
		/// @return 返回递增前的值。
		T operator++(int)
		{
			T record = _count;
			IncCount();
			return record;
		}

		/// @brief 前缀递减
		/// @return
		T operator--()
		{
			DecCount();
			return _count;
		}

		/// @brief 后缀递减。
		/// @param
		/// @return
		T operator--(int)
		{
			T record = _count;
			DecCount();
			return record;
		}

		/// @brief 将计数器的值增加指定的值
		/// @param value
		/// @return
		T operator+=(T value)
		{
			_count += value;
			_count %= _max_value + 1;
			return _count;
		}

		/// @brief 将计数器的值减去指定的值。
		/// @param value
		/// @return 返回运算后的值。
		T operator-=(T value)
		{
			value %= _max_value + 1;
			_count += _max_value + 1 - value;
			_count %= _max_value + 1;
			return _count;
		}
#pragma endregion

		/// @brief 重置计数值。计数值归 0.
		void Reset()
		{
			_count = 0;
		}

		/// @brief 获取计数器的当前值。
		/// @return
		T CurrentValue() const
		{
			return _count;
		}

		/// @brief 设置计数器的当前值。
		/// @note 会将 value 对 (_max_value + 1) 取模，也就是说如果 value 超过最大值，
		/// 	  会发生回绕。
		///
		/// @param value
		void SetCurrentValue(T value)
		{
			_count = value % (_max_value + 1);
		}
	};
}
