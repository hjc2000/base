#pragma once
#include <base/stream/Span.h>
#include <cstdint>

namespace base
{
	class ReadOnlySpan :
		public base::IEnumerable<uint8_t const>
	{
	private:
		uint8_t const *_buffer = nullptr;
		int32_t _size = 0;

	public:
		/// @brief 无参构造函数。引用一段空内存。
		/// @note 可以通过 Size 属性判断本对象是否引用到了有效的内存。
		ReadOnlySpan() = default;

		/// @brief 引用 buffer 指向的内存。在本对象的生命周期内，buffer 指向的内存必须始终存活。
		/// @param buffer 要引用的内存。
		/// @param size buffer 的大小。
		ReadOnlySpan(uint8_t const *buffer, int32_t size);

		/// @brief 通过一个可读可写的 Span 构造只读的 ReadOnlySpan.
		/// @param o
		ReadOnlySpan(base::Span const &o);

		/// @brief 拷贝构造函数。
		/// @note 不会拷贝对方引用的内存，而是将对方引用的内存的指针拿过来，
		/// 与对方引用同一段内存。
		/// @param o
		ReadOnlySpan(ReadOnlySpan const &o);

		/// @brief 赋值运算符。
		/// @param o
		/// @return
		ReadOnlySpan &operator=(ReadOnlySpan const &o);

		uint8_t const &operator[](int32_t index) const;

		/// @brief 获得指定范围的切片。
		/// @param range
		/// @return
		base::ReadOnlySpan operator[](base::Range const &range) const;

		/// @brief 所引用的内存。
		/// @return
		uint8_t const *Buffer() const;

		/// @brief 所引用的内存大小。
		/// @return
		int32_t Size() const;

		/// @brief 将本 ReadOnlySpan 切片，得到一个更小的 ReadOnlySpan.
		/// @param start 切片起始位置。
		/// @param size 切片大小。
		/// @return
		base::ReadOnlySpan Slice(int32_t start, int32_t size) const;

		/// @brief 获得指定范围的切片。
		/// @param range
		/// @return
		base::ReadOnlySpan Slice(base::Range const &range) const;

		/// @brief 获取非 const 迭代器。
		/// @return
		std::shared_ptr<base::IEnumerator<uint8_t const>> GetEnumerator() override;

		/// @brief 查找指定值所在的第一个索引。
		/// @param value
		/// @return 找到则返回索引，没找到则返回 -1.
		int32_t IndexOf(uint8_t value) const;
	};
} // namespace base
