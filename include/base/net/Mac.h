#pragma once
#include <base/container/Array.h>
#include <base/stream/ReadOnlySpan.h>
#include <base/string/ICanToString.h>
#include <bit>
#include <cstdint>

namespace base
{
	///
	/// @brief MAC 地址
	/// @note 按照小端序存放。即书写 MAC 字符串时，最右边的，即最低字节，存放在本对象的低索引处；
	/// 字符串最左边的，即最高字节，存放在本对象的最高索引处。
	///
	class Mac :
		public base::ICanToString
	{
	private:
		base::Array<uint8_t, 6> _mac_buffer{};

	public:
		///
		/// @brief 无参构造函数。构造出来的 MAC 地址是全 0.
		///
		Mac() = default;

		///
		/// @brief 构造函数。
		/// @param mac_buffer MAC 地址数组。该缓冲区内的 MAC 地址必须是按小端序存放。
		///
		Mac(base::Array<uint8_t, 6> const &mac_buffer);

		///
		/// @brief 构造函数
		/// @param endian 你传入的 MAC 地址数组是大端序的还是小端序的
		/// @param mac_buffer MAC 地址数组。可以是大端序也可以是小端序，只要 endian 参数正确指明就行。
		///
		Mac(std::endian endian, base::Array<uint8_t, 6> const &mac_buffer);

		///
		/// @brief 从 ReadOnlySpan 中构造 MAC.
		/// @param endian span 中的 MAC 地址的字节序。
		/// @param span 储存着 MAC 地址的内存。会将这段内存的数据拷贝过来。
		///
		Mac(std::endian endian, base::ReadOnlySpan const &span);

		///
		/// @brief 拷贝构造函数。
		/// @param o
		///
		Mac(Mac const &o);

		///
		/// @brief 赋值运算符。
		/// @param o
		/// @return
		///
		Mac &operator=(Mac const &o);

		///
		/// @brief 获取本对象内部的用来储存 MAC 地址的数组。
		/// @return
		///
		base::Array<uint8_t, 6> const &InternalArray() const;

		///
		/// @brief 获取本对象内部的用来储存 MAC 地址的数组。
		/// @return
		///
		base::Array<uint8_t, 6> &InternalArray();

		///
		/// @brief 显示将本对象强制转换为 base::Array<uint8_t, 6>.
		/// 原理是将 MAC 地址拷贝到 base::Array<uint8_t, 6> 中。
		///
		explicit operator base::Array<uint8_t, 6>() const;

		///
		/// @brief 将 MAC 地址转换为无符号整型。
		///
		explicit operator uint64_t() const;

		///
		/// @brief 获取引用着本对象内部缓冲区的 ReadOnlySpan.
		///
		explicit operator base::ReadOnlySpan() const;

		///
		/// @brief 获取引用着本对象内部缓冲区的 Span.
		///
		explicit operator base::Span();

		///
		/// @brief 转化为字符串
		/// @return
		///
		std::string ToString() const override;

		///
		/// @brief 获取引用着本对象内部缓冲区的 ReadOnlySpan.
		/// @return
		///
		base::ReadOnlySpan AsReadOnlySpan() const;

		///
		/// @brief 获取引用着本对象内部缓冲区的 Span.
		/// @return
		///
		base::Span AsSpan();

		///
		/// @brief 访问 MAC 地址中指定索引的值。
		/// @param index
		/// @return
		///
		uint8_t &operator[](int index);

		///
		/// @brief 访问 MAC 地址中指定索引的值。
		/// @param index
		/// @return
		///
		uint8_t const &operator[](int index) const;

		///
		/// @brief 获取 MAC 地址中的 OUI.
		/// @return
		///
		base::Array<uint8_t, 3> Oui() const;

		///
		/// @brief 设置 OUI.
		/// @param value
		///
		void SetOui(base::Array<uint8_t, 3> const &value);

		///
		/// @brief 本地址是否是多播地址。
		/// @note 最高字节的最低位为 1 则是多播地址，为 0 则是单播地址。
		/// @return 是多播地址返回 true，不是则返回 false.
		///
		bool IsMulticastAddress() const;
	};
} // namespace base
