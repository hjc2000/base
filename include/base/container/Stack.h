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
		/**
		 * @brief 入栈。
		 *
		 * @param o
		 */
		void Push(ItemType const &o)
		{
			_vector.push_back(o);
		}

		/**
		 * @brief 出栈。
		 *
		 * @return ItemType
		 */
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

		/**
		 * @brief 尝试出栈。
		 *
		 * @param out 接收出栈对象的参数。
		 * @return true 出栈成功。
		 * @return false 出栈失败。
		 */
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

		/**
		 * @brief 数组的大小
		 *
		 * @return int32_t
		 */
		virtual int32_t Count() const override
		{
			return _vector.size();
		}

		/**
		 * @brief 获取底层的缓冲区
		 *
		 * @return ItemType*
		 */
		virtual ItemType *Buffer() override
		{
			return _vector.data();
		}

		/**
		 * @brief 获取底层的缓冲区
		 *
		 * @return ItemType const*
		 */
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
