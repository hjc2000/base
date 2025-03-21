#pragma once
#include "base/container/Array.h"
#include "base/stream/ReadOnlySpan.h"
#include "base/stream/Span.h"
#include "base/string/ICanToString.h"
#include "base/string/String.h"
#include <bit>

namespace base
{
	///
	/// @brief IP 地址类型。
	///
	///
	enum class IPAddressType
	{
		IPV4,
		IPV6,
	};

	///
	/// @brief IP 地址。兼容 IPV4 和 IPV6.
	///
	///
	class IPAddress :
		public base::ICanToString
	{
	private:
		/* #region Context */

		class Context
		{
		private:
			base::Array<uint8_t, 16> _ip_address_buffer;
			base::IPAddressType _type = base::IPAddressType::IPV4;

		public:
			Context() = default;

			Context(base::IPAddressType type);

			base::Span Span();

			base::ReadOnlySpan Span() const;

			base::IPAddressType IPAddressType() const;
		};

		///
		/// @brief 上下文。
		///
		///
		Context _context;

		/* #endregion */

	public:
		/* #region 生命周期 */

		///
		/// @brief 构造一个未指定的 IP 地址。此时表现为 IPV4 的 0.0.0.0.
		///
		///
		IPAddress() = default;

		///
		/// @brief 构造一个未指定的 IP 地址。此时可以指定期望的 IP 地址版本。
		/// 无论是对 IPV4 还是 IPV6，构造出来的地址的所有字节都是 0.
		///
		/// @param type
		///
		IPAddress(IPAddressType type);

		///
		/// @brief 构造一个 IPV4 地址。
		///
		/// @param endian ip_address_buffer 中 IP 地址的字节序。
		/// @param ip_address_buffer 存放着 IPV4 地址的缓冲区。
		///
		IPAddress(std::endian endian, base::Array<uint8_t, 4> const &ip_address_buffer);

		///
		/// @brief 构造一个 IPV6 地址。
		///
		/// @param endian ip_address_buffer 中 IP 地址的字节序。
		/// @param ip_address_buffer 存放着 IPV6 地址的缓冲区。
		///
		IPAddress(std::endian endian, base::Array<uint8_t, 16> const &ip_address_buffer);

		///
		/// @brief 构造一个 IP 地址。
		///
		/// @note 是 IPV4 还是 IPV6 取决于初始化列表的大小。初始化列表如果是 4 字节，则构造出来
		/// 是 IPV4 地址，如果是 16 字节，则构造出来是 IPV6 地址。如果都不是，则会抛出异常。
		///
		/// @param endian 初始化列表中的 IP 地址的字节序。
		/// @param list 储存着 IP 地址的初始化列表。
		///
		IPAddress(std::endian endian, std::initializer_list<uint8_t> const &list);

		///
		/// @brief 从 ReadOnlySpan 构造 IP 地址。
		///
		/// @param endian span 中 IP 地址的字节序。
		///
		/// @param span 储存着 IP 地址的一段内存。
		/// 	@note 构造时不是引用这段内存，而是将这段内存中的数据拷贝过来。
		///
		IPAddress(std::endian endian, base::ReadOnlySpan const &span);

		///
		/// @brief 用标准的表示 IP 地址的字符串构造。
		///
		/// @note 会根据字符串格式来识别是 IPV4 地址还是 IPV6 地址。
		/// @note IPV6 地址字符串暂不支持缩写。
		///
		/// @param ip_str
		///
		IPAddress(base::String const &ip_str);

		virtual ~IPAddress() = default;
		/* #endregion */

		uint8_t &operator[](int index);
		uint8_t const &operator[](int index) const;

		///
		/// @brief IP 地址的类型。
		///
		/// @return IPAddressType
		///
		IPAddressType Type() const;

		///
		/// @brief 转化为字符串。
		///
		/// @return std::string
		///
		std::string ToString() const override;

		///
		/// @brief 获取引用着本对象缓冲区的 Span.
		///
		/// @return base::Span
		///
		base::Span Span();

		///
		/// @brief 获取引用着本对象缓冲区的 ReadOnlySpan.
		///
		/// @return base::ReadOnlySpan
		///
		base::ReadOnlySpan Span() const;
	};

#if HAS_THREAD
	///
	/// @brief 测试 IPAddressType
	///
	///
	void TestIpAddress();
#endif
} // namespace base
