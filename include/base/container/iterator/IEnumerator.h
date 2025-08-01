#pragma once

namespace base
{
	template <typename ItemType>
	class IEnumerator
	{
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
	};

} // namespace base
