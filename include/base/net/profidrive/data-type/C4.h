#pragma once
#include "base/bit/AutoBitConverter.h"
#include "base/math/Fraction.h"
#include "base/stream/ReadOnlySpan.h"
#include <base/container/Array.h>

namespace base
{
	namespace profidrive
	{
		/**
		 * @brief profidrive 行规特定类型: C4.
		 *
		 */
		class C4 final
		{
		private:
			/**
			 * @brief C4 字节序列。
			 * @note 储存到这里的必须是是大端序，可以直接发送。
			 */
			base::Array<uint8_t, 4> _buffer{};

			/**
			 * @brief 自适应转换器。
			 * @note 将远程字节序设置为大端序后，在转换时能够根据本机字节序决定是否翻转。
			 */
			base::AutoBitConverter _converter{std::endian::big};

			int32_t Factor() const;

		public:
			/**
			 * @brief 无参构造函数。
			 *
			 */
			C4() = default;

			/**
			 * @brief 从 profinet 收到大端序的数据后原封不动地将字节序列传进来。
			 *
			 * @param value
			 */
			C4(base::ReadOnlySpan const &value);

			/**
			 * @brief 通过实际的分数值构造行规特定数据类型。
			 *
			 * @param value
			 */
			C4(base::Fraction const &value);

		public:
			/**
			 * @brief 获取可以直接被用来发送的字节序列。已经是大端序了。
			 *
			 * @return base::Span
			 */
			base::Span Span();

			/**
			 * @brief 获取可以直接被用来发送的字节序列。已经是大端序了。
			 *
			 * @return base::ReadOnlySpan
			 */
			base::ReadOnlySpan Span() const;

			/**
			 * @brief 强制转换为分数类型。
			 *
			 * @return base::Fraction
			 */
			explicit operator base::Fraction() const;
		};
	} // namespace profidrive
} // namespace base
