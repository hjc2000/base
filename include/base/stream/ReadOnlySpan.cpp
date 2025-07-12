#include "ReadOnlySpan.h"
#include "base/string/String.h"
#include <cstdint>

/* #region 构造函数 */

base::ReadOnlySpan::ReadOnlySpan(base::String const &str)
{
	base::ReadOnlySpan span = str.Span();
	*this = span;
}

/* #endregion */

std::shared_ptr<base::IEnumerator<uint8_t const>> base::ReadOnlySpan::GetEnumerator()
{
	class Enumerator :
		public base::IEnumerator<uint8_t const>
	{
	private:
		ReadOnlySpan *_span = nullptr;
		int32_t _index = 0;

	public:
		Enumerator(ReadOnlySpan *span)
		{
			_span = span;
		}

		///
		/// @brief 迭代器当前是否指向尾后元素。
		///
		/// @return
		///
		virtual bool IsEnd() const override
		{
			return _index == _span->Size();
		}

		///
		/// @brief 获取当前值的引用。
		///
		/// @return ItemType&
		///
		virtual uint8_t const &CurrentValue() override
		{
			return (*_span)[_index];
		}

		///
		/// @brief 递增迭代器的位置。
		///
		///
		virtual void Add() override
		{
			++_index;
		}
	};

	return std::shared_ptr<IEnumerator<uint8_t const>>{new Enumerator{this}};
}
