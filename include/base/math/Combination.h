#pragma once
#include "base/string/ICanToString.h"
#include <cstdint>
#include <string>
#include <vector>

namespace base
{
	///
	/// @brief 组合。
	///
	///
	class Combination :
		public base::ICanToString
	{
	private:
		int _n = 0;
		int _m = 0;
		bool _move_to_next_for_the_first_time = true;
		std::vector<int> _current_combination;

	public:
		///
		/// @brief 组合。从 n 个里面选出任意 m 个进行组合。
		///
		/// @param n
		/// @param m
		///
		Combination(int n, int m);

		///
		/// @brief 当前组合。
		///
		/// @return std::vector<int> const&
		///
		std::vector<int> const &Current() const;

		///
		/// @brief 直接访问 Current() 属性返回的向量的指定索引位置的值。
		///
		/// @param index
		/// @return int
		///
		int operator[](int index) const;

		///
		/// @brief 移动到下一个组合。
		///
		/// @return true
		/// @return false
		///
		bool MoveToNext();

		///
		/// @brief 一共有多少种组合。
		///
		/// @return int64_t
		///
		int64_t Count() const;

		///
		/// @brief 转化为字符串
		///
		/// @return std::string
		///
		virtual std::string ToString() const override;
	};
} // namespace base

#if HAS_THREAD
namespace base
{
	namespace test
	{
		void test_combination();
	} // namespace test
} // namespace base
#endif
