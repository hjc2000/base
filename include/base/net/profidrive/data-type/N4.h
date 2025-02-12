#pragma once
#include <base/container/Array.h>
#include <base/net/profidrive/data-type/IProfidriveNumber.h>

namespace base
{
	/// @brief profidrive 行规特定类型: N4.
	class N4 final :
		public base::IProfidriveNumber
	{
	private:
		/// @brief N4 字节序列。
		/// @note 储存到这里的必须是是大端序，可以直接发送。
		base::Array<uint8_t, 4> _buffer{};

	public:
		N4() = default;

		/// @brief 从 profinet 收到大端序的数据后原封不动地将字节序列传进来。
		/// @param value
		N4(base::ReadOnlySpan const &value)
		{
			From(value);
		}

		N4(base::Fraction const &value)
		{
			From(value);
		}

		virtual int32_t Factor() const override
		{
			// 2 的 30 次方
			return static_cast<int64_t>(1 << 30);
		}

		/// @brief 获取可以直接被用来发送的字节序列。已经是大端序了。
		/// @return
		virtual base::Span Span() override
		{
			return _buffer.AsArraySpan();
		}
	};
} // namespace base
