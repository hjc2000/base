#pragma once

namespace base
{
	template <typename ItemType>
	class IEnumerator
	{
	public:
		class Context_t
		{
		private:
			friend class IEnumerator;

			bool _has_not_moved = true;
		};

		virtual ~IEnumerator() = default;

		///
		/// @brief 迭代器当前是否指向尾后元素。
		///
		/// @return
		///
		virtual bool IsEnd() const = 0;

		///
		/// @brief 获取当前值的引用。
		///
		/// @note 迭代器构造后，如果被迭代的集合不为空，要立即让 CurrentValue 指向第一个有效元素。
		///
		/// @return
		///
		virtual ItemType &CurrentValue() = 0;

		///
		/// @brief 递增迭代器的位置。
		///
		/// @warning 本方法可能是没有保护的，迭代器结束后，再次调用本方法的行为是未定义的，
		/// 可能移动越界了，然后导致 IsEnd 判定为 false, 但是实际上当前迭代器已经不指向
		/// 有效元素了，而是指向非法内存区域了。如果是手动操作迭代器，推荐使用 MoveToNext 方法。
		///
		virtual void Add() = 0;

		///
		/// @brief 迭代器还没迭代结束，还指向有效元素。
		///
		/// @return
		///
		bool IsNotEnd() const
		{
			return !IsEnd();
		}

		///
		/// @brief 派生类需要提供一个该对象。
		///
		/// @return
		///
		virtual base::IEnumerator<ItemType>::Context_t &Context() = 0;

		///
		/// @brief 本方法让迭代器支持像 C# 那样使用。即一开始拿到迭代器后首先一个 MoveToNext
		/// 移动到第一个有效元素的位置。
		///
		/// @return 返回 true 表示成功移动到下一个有效元素，返回 false 表示没有下一个元素了。
		///
		bool MoveToNext()
		{
			if (Context()._has_not_moved)
			{
				Context()._has_not_moved = false;
			}
			else if (IsNotEnd())
			{
				// 不是第一次移动，并且迭代器还没结束，则递增，前往下一个位置。
				Add();
			}

			return IsNotEnd();
		}
	};

} // namespace base
