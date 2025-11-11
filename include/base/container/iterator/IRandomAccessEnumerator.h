#pragma once
#include "base/container/iterator/IEnumerator.h"
#include <cstdint>
#include <memory>

namespace base
{
	template <typename ItemType>
	class IRandomAccessEnumerator :
		public base::IEnumerator<ItemType>
	{
	public:
		~IRandomAccessEnumerator() = default;

		///
		/// @brief 克隆一个迭代器对象副本。
		///
		/// @note 派生类要实现拷贝构造函数后在这里调用自己的拷贝构造函数拷贝一份自己。
		///
		/// @return
		///
		virtual std::shared_ptr<base::IRandomAccessEnumerator<ItemType>> Clone() const = 0;

		///
		/// @brief 容器中总共有多少个元素。
		///
		/// @return
		///
		virtual int64_t Count() const = 0;

		///
		/// @brief 当前迭代到的位置。
		///
		/// @return
		///
		virtual int64_t Position() const = 0;

		///
		/// @brief 将迭代器位置增加 value.
		///
		/// @param value 增加的值。可以是正数和负数。
		///
		virtual void Add(int64_t value) = 0;

		///
		/// @brief 获取当前值的引用。
		///
		/// @note 迭代器构造后，如果被迭代的集合不为空，要立即让 CurrentValue 指向第一个有效元素。
		///
		/// @return
		///
		virtual ItemType &CurrentValue() override = 0;

		///
		/// @brief 从未被调用过 MoveToNext 方法。
		///
		/// @note 如果自己派生 IEnumerator，且没有组合其他 IEnumerator 对象，
		/// 则自己维护一个 _has_not_moved 字段。如果组合了其他 IEnumerator 对象，
		/// 则转发，不要再自己多一个 _has_not_moved 字段了。
		///
		/// @return
		///
		virtual bool HasNotMoved() override = 0;

		///
		/// @brief 设置是否从未被调用过 MoveToNext 方法。
		///
		/// @note 如果自己派生 IEnumerator，且没有组合其他 IEnumerator 对象，
		/// 则自己维护一个 _has_not_moved 字段。如果组合了其他 IEnumerator 对象，
		/// 则转发，不要再自己多一个 _has_not_moved 字段了。
		///
		/// @param value
		///
		virtual void SetHasNotMoved(bool value) override = 0;

		/* #region 接口扩展 */

		///
		/// @brief 递增迭代器的位置。
		///
		/// @warning 本方法可能是没有保护的，迭代器结束后，再次调用本方法的行为是未定义的，
		/// 可能移动越界了，然后导致 IsEnd 判定为 false, 但是实际上当前迭代器已经不指向
		/// 有效元素了，而是指向非法内存区域了。如果是手动操作迭代器，推荐使用 MoveToNext 方法。
		///
		virtual void Add() override final
		{
			Add(1);
		}

		///
		/// @brief 将迭代器的位置递减 1.
		///
		///
		void Subtract()
		{
			Add(-1);
		}

		///
		/// @brief 迭代器当前是否指向尾后元素。
		///
		/// @return
		///
		virtual bool IsEnd() const override final
		{
			return Position() == Count();
		}

		/* #endregion */
	};

} // namespace base
