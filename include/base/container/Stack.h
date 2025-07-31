#pragma once
#include "base/container/IRawArray.h"
#include "base/string/define.h"
#include <stdexcept>
#include <vector>

namespace base
{
	template <typename ItemType>
	class Stack :
		public base::IRawArray<ItemType>
	{
	private:
		std::vector<ItemType> _vector{};

	public:
		///
		/// @brief 入栈。
		///
		/// @param o
		///
		void Push(ItemType const &o)
		{
			_vector.push_back(o);
		}

		///
		/// @brief 出栈。
		///
		/// @return
		///
		ItemType Pop()
		{
			ItemType ret{};
			bool pop_result = TryPop(ret);
			if (pop_result)
			{
				return ret;
			}

			throw std::out_of_range{CODE_POS_STR + "栈为空，无法出栈。"};
		}

		///
		/// @brief 尝试出栈。
		///
		/// @param out 接收出栈对象的参数。
		///
		/// @return 出栈成功则返回 true, 失败者返回 false.
		///
		bool TryPop(ItemType &out)
		{
			if (_vector.size() == 0)
			{
				return false;
			}

			out = _vector[_vector.size() - 1];
			_vector.pop_back();
			return true;
		}

		///
		/// @brief 数组的大小。
		///
		/// @return
		///
		virtual int64_t Count() const override
		{
			return _vector.size();
		}

		///
		/// @brief 获取底层的缓冲区
		///
		/// @return
		///
		virtual ItemType *Buffer() override
		{
			return _vector.data();
		}

		///
		/// @brief 获取底层的缓冲区
		///
		/// @return
		///
		virtual ItemType const *Buffer() const override
		{
			return _vector.data();
		}
	};
} // namespace base

#if HAS_THREAD
namespace base
{
	namespace test
	{
		void test_stack();
	} // namespace test
} // namespace base
#endif
