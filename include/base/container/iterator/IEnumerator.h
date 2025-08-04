#pragma once

namespace base
{
	template <typename ItemType>
	class IEnumerator
	{
	private:
		bool _is_first_move = true;

	public:
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
		/// @brief 本方法让迭代器支持像 C# 那样使用。即一开始拿到迭代器后首先一个 MoveToNext
		/// 移动到第一个有效元素的位置。
		///
		/// @return 返回 true 表示成功移动到下一个有效元素，返回 false 表示没有下一个元素了。
		///
		bool MoveToNext()
		{
			if (_is_first_move)
			{
				_is_first_move = false;
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
