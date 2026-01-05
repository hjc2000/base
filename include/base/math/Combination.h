#pragma once
#include "base/math/math.h"
#include "base/string/define.h"
#include "base/string/ICanToString.h"
#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

namespace base
{
	///
	/// @brief 组合。
	///
	class Combination :
		public base::ICanToString
	{
	private:
		int64_t _n = 0;
		int64_t _m = 0;
		bool _move_to_next_for_the_first_time = true;
		std::vector<int64_t> _current_combination;

	public:
		///
		/// @brief 组合。从 n 个里面选出任意 m 个进行组合。
		///
		/// @param n
		/// @param m
		///
		Combination(int64_t n, int64_t m)
			: _n(n),
			  _m(m)
		{
			if (_m > _n)
			{
				throw std::invalid_argument{CODE_POS_STR + "m 不能比 n 大。"};
			}

			for (int64_t i = 0; i < _m; i++)
			{
				_current_combination.push_back(i);
			}
		}

		///
		/// @brief 当前组合。
		///
		/// @return
		///
		std::vector<int64_t> const &Current() const
		{
			return _current_combination;
		}

		///
		/// @brief 直接访问 Current() 属性返回的向量的指定索引位置的值。
		///
		/// @param index
		/// @return
		///
		int64_t operator[](int64_t index) const
		{
			if (index < 0 || index >= _m)
			{
				throw std::out_of_range{CODE_POS_STR + "索引溢出。"};
			}

			return _current_combination[index];
		}

		///
		/// @brief 移动到下一个组合。
		///
		/// @return
		///
		bool MoveToNext()
		{
			if (_m == 0)
			{
				return false;
			}

			if (_move_to_next_for_the_first_time)
			{
				_move_to_next_for_the_first_time = false;
				return true;
			}

			if (_current_combination[0] >= _n - _m)
			{
				return false;
			}

			bool last_loop_has_broken = false;
			for (int64_t i = 0; i < _m; i++)
			{
				int64_t current_index = _m - 1 - i;
				_current_combination[current_index]++;
				if (_current_combination[current_index] > _n - 1 - i)
				{
					last_loop_has_broken = true;
					continue;
				}

				if (last_loop_has_broken)
				{
					last_loop_has_broken = false;
					for (int64_t j = current_index; j + 1 < static_cast<int64_t>(_current_combination.size()); j++)
					{
						_current_combination[j + 1] = _current_combination[j] + 1;
					}
				}

				return true;
			}

			return true;
		}

		///
		/// @brief 一共有多少种组合。
		///
		/// @return
		///
		int64_t Count() const
		{
			base::BigInteger result = base::factorial<base::BigInteger>(_n) /
									  base::factorial<base::BigInteger>(_n - _m) /
									  base::factorial<base::BigInteger>(_m);

			return static_cast<int64_t>(result);
		}

		///
		/// @brief 转化为字符串
		///
		/// @return
		///
		virtual std::string ToString() const override
		{
			std::string result;
			int64_t count = static_cast<int64_t>(_current_combination.size());

			for (int64_t i = 0; i < count; i++)
			{
				result += std::to_string(_current_combination[i]);

				if (i < count - 1)
				{
					result += ", ";
				}
			}

			return result;
		}
	};

} // namespace base
