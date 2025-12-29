#pragma once
#include "base/container/iterator/IEnumerator.h"
#include "base/stream/ReadOnlySpan.h"

namespace base::profinet
{
	///
	/// @brief 迭代一段 base::ReadOnlySpan 中的 TLV.
	///
	class DcpTlvEnumerator :
		public base::IEnumerator<base::ReadOnlySpan>
	{
	private:
		bool _has_not_moved = true;
		base::ReadOnlySpan _span;
		base::ReadOnlySpan _remain_span;
		base::ReadOnlySpan _current_value;
		bool _is_end = false;

	public:
		///
		/// @brief 构造函数。
		///
		/// @param span 含有很多 TLV 的 base::ReadOnlySpan.
		///
		DcpTlvEnumerator(base::ReadOnlySpan const &span);

		///
		/// @brief 迭代器当前是否指向尾后元素。
		///
		/// @return
		///
		virtual bool IsEnd() const override
		{
			return _is_end;
		}

		///
		/// @brief 获取当前值的引用。
		///
		/// @return ItemType&
		///
		virtual base::ReadOnlySpan &CurrentValue() override;

		///
		/// @brief 递增迭代器的位置。
		///
		///
		virtual void Add() override;

		///
		/// @brief 从未被调用过 MoveToNext 方法。
		///
		/// @return
		///
		virtual bool HasNotMoved() override
		{
			return _has_not_moved;
		}

		///
		/// @brief 设置是否从未被调用过 MoveToNext 方法。
		///
		/// @param value
		///
		virtual void SetHasNotMoved(bool value) override
		{
			_has_not_moved = value;
		}
	};

} // namespace base::profinet
