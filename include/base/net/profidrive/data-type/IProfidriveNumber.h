#pragma once
#include <base/bit/AutoBitConverter.h>
#include <base/math/Fraction.h>
#include <base/stream/ReadOnlySpan.h>

namespace base
{
	class IProfidriveNumber
	{
	private:
		/// @brief 自适应转换器。
		/// @note 将远程字节序设置为大端序后，在转换时能够根据本机字节序决定是否翻转。
		base::AutoBitConverter _converter{std::endian::big};

	public:
		virtual int32_t Factor() const = 0;

		/// @brief 获取可以直接被用来发送的字节序列。已经是大端序了。
		/// @return
		virtual base::Span Span() = 0;

		/// @brief 获取可以直接被用来发送的字节序列。已经是大端序了。
		/// @return
		base::ReadOnlySpan Span() const
		{
			return const_cast<IProfidriveNumber *>(this)->Span();
		}

		/// @brief
		/// @param span 从 profinet 收到大端序的数据后原封不动地将字节序列传进来。
		void From(base::ReadOnlySpan const &span);
		void From(base::Fraction const &value);

		/// @brief 强制转换为分数类型。
		explicit operator base::Fraction() const;
	};
} // namespace base
