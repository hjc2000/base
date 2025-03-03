#pragma once
#include <base/container/Array.h>
#include <base/net/profidrive/data-type/IProfidriveNumber.h>

namespace base
{
	/// @brief profidrive 行规特定类型: X2.
	class X2 final :
		public base::IProfidriveNumber
	{
	private:
		/// @brief X2 字节序列。
		/// @note 储存到这里的必须是是大端序，可以直接发送。
		base::Array<uint8_t, 2> _buffer{};

	public:
		X2() = default;

		/// @brief 从 profinet 收到大端序的数据后原封不动地将字节序列传进来。
		/// @param value
		X2(base::ReadOnlySpan const &value);

		/**
		 * @brief 通过实际的分数值构造行规特定数据类型。
		 *
		 * @param value
		 */
		X2(base::Fraction const &value);

	public:
		virtual int32_t Factor() const override;

		/// @brief 获取可以直接被用来发送的字节序列。已经是大端序了。
		/// @return
		virtual base::Span Span() override;
	};
} // namespace base
