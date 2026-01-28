#pragma once
#include "base/bit/bit_converte.h"
#include "base/stream/ReadOnlySpan.h"
#include "base/stream/Stream.h"
#include <bit>
#include <cstdint>

namespace base
{
	///
	/// @brief 构造时设置好通信对方的大小端，进行转换时能够自动进行大小端转换。
	///
	class AutoBitConverter final
	{
	private:
		std::endian _remote_endian;

	public:
		///
		/// @brief 对方主机的字节序
		///
		/// @param remote_endian
		///
		constexpr AutoBitConverter(std::endian remote_endian)
			: _remote_endian(remote_endian)
		{
		}

		///
		/// @brief 是否应该翻转。
		///
		/// @return 远程字节序和本机字节序不同，需要翻转则返回 true, 否则返回 false.
		///
		constexpr bool ShouldReverse() const
		{
			return std::endian::native != _remote_endian;
		}

		/* #region FromBytes */

		///
		/// @brief 从字节序列中反序列化出 ReturnType.
		///
		/// @param span
		///
		/// @return
		///
		template <typename ReturnType>
		ReturnType FromBytes(base::ReadOnlySpan const &span) const
		{
			ReturnType ret = base::bit_converte::FromBytes<ReturnType>(span);

			if (ShouldReverse())
			{
				uint8_t *p = reinterpret_cast<uint8_t *>(&ret);
				std::reverse(p, p + sizeof(ReturnType));
			}

			return ret;
		}

		///
		/// @brief 从流中反序列化出 ReturnType.
		///
		/// @param stream
		///
		/// @return
		///
		template <typename ReturnType>
		ReturnType FromBytes(base::Stream &stream) const
		{
			if (!ShouldReverse())
			{
				return base::bit_converte::FromBytes<ReturnType>(stream);
			}

			struct
			{
				// 使用普通字节缓冲区，避免 ReturnType 的构造函数被调用。
				alignas(ReturnType) uint8_t _buffer[sizeof(ReturnType)];
			} buffer_provider;

			base::Span buffer_span{
				buffer_provider._buffer,
				static_cast<int64_t>(sizeof(ReturnType)),
			};

			int64_t have_read = stream.ReadExactly(buffer_span);

			if (have_read < buffer_span.Size())
			{
				throw std::runtime_error{CODE_POS_STR + "流中没有足够的字节。"};
			}

			buffer_span.Reverse();
			return *reinterpret_cast<ReturnType *>(buffer_provider._buffer);
		}

		/* #endregion */

		/* #region GetBytes */

		///
		/// @brief 将 value 序列化到缓冲区中的 offset 处。
		///
		/// @param value
		/// @param span
		///
		template <typename ValueType>
		void GetBytes(ValueType const &value, base::Span const &span) const
		{
			base::bit_converte::GetBytes<ValueType>(value, span);

			if (ShouldReverse())
			{
				span.Reverse();
			}
		}

		///
		/// @brief 将 value 序列化到流中。
		///
		/// @param value
		/// @param stream
		///
		/// @return
		///
		template <typename ValueType>
		void GetBytes(ValueType const &value, base::Stream &stream) const
		{
			if (!ShouldReverse())
			{
				base::bit_converte::GetBytes<ValueType>(value, stream);
				return;
			}

			uint8_t buffer[sizeof(ValueType)];

			base::Span buffer_span{
				buffer,
				static_cast<int64_t>(sizeof(ValueType)),
			};

			// 借用 bit_converte 执行一次复制，将 value 复制到 buffer 中。
			base::bit_converte::GetBytes<ValueType>(value, buffer_span);

			buffer_span.Reverse();
			stream.Write(buffer_span);
		}

		/* #endregion */
	};

	///
	/// @brief 远端是大端序的话使用本转换器。
	///
	constexpr base::AutoBitConverter big_endian_remote_converter{std::endian::big};

	///
	/// @brief 远端是小端序的话使用本转换器。
	///
	constexpr base::AutoBitConverter little_endian_remote_converter{std::endian::little};

} // namespace base
