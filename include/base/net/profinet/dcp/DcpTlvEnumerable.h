#pragma once
#include "base/container/iterator/IEnumerable.h"
#include "DcpTlvEnumerator.h"

namespace base::profinet
{
	///
	/// @brief 将一个含有 TLV 的 base::ReadOnlySpan 交给本对象，帮助迭代这里面的 TLV.
	///
	class DcpTlvEnumerable :
		public base::IEnumerable<base::ReadOnlySpan>
	{
	private:
		base::ReadOnlySpan _span;

	public:
		///
		/// @brief 构造函数。
		///
		/// @param span 将一个含有 TLV 的 base::ReadOnlySpan.
		///
		DcpTlvEnumerable(base::ReadOnlySpan const &span)
		{
			_span = span;
		}

		///
		/// @brief 获取非 const 迭代器
		///
		/// @return
		///
		virtual std::shared_ptr<base::IEnumerator<base::ReadOnlySpan>> GetEnumerator() override
		{
			return std::shared_ptr<base::IEnumerator<base::ReadOnlySpan>>{new base::profinet::DcpTlvEnumerator{_span}};
		}
	};

} // namespace base::profinet
