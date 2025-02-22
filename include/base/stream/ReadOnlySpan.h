#pragma once
#include <base/container/ArraySpan.h>
#include <base/stream/Span.h>
#include <cstdint>

namespace base
{
	/**
	 * @brief 只读内存段。
	 *
	 * @note 引用一段只读的内存。
	 *
	 * @warning 要求本类对象的生命周期内，引用的外部内存始终存活。
	 */
	class ReadOnlySpan :
		public base::IEnumerable<uint8_t const>
	{
	private:
		uint8_t const *_buffer = nullptr;
		int32_t _size = 0;

	public: // 构造函数
		/// @brief 无参构造函数。引用一段空内存。
		/// @note 可以通过 Size 属性判断本对象是否引用到了有效的内存。
		ReadOnlySpan() = default;

		/// @brief 引用 buffer 指向的内存。在本对象的生命周期内，buffer 指向的内存必须始终存活。
		/// @param buffer 要引用的内存。
		/// @param size buffer 的大小。
		ReadOnlySpan(uint8_t const *buffer, int32_t size);

		/**
		 * @brief Construct a new Read Only Span object
		 *
		 * @param span
		 */
		ReadOnlySpan(base::ReadOnlyArraySpan<uint8_t> const &span);

		/// @brief 通过一个可读可写的 Span 构造只读的 ReadOnlySpan.
		/// @param o
		ReadOnlySpan(base::Span const &o);

	public: // 拷贝构造
		ReadOnlySpan(ReadOnlySpan const &o);
		ReadOnlySpan &operator=(ReadOnlySpan const &o);

	public:
		/**
		 * @brief 索引一个字节。
		 *
		 * @param index
		 * @return uint8_t const&
		 */
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

	public: // IndexOf
		/// @brief 从本内存段查找匹配项所在的索引。
		/// @param match 匹配项。
		/// @return 找到了返回匹配位置的索引。没找到返回 -1.
		int32_t IndexOf(uint8_t match) const;

		/// @brief 从本内存段查找匹配项所在的索引。
		/// @param start 查找的起始索引。从此处往后开始查找。
		/// @param match 匹配项。
		/// @return 找到了返回匹配位置的索引。没找到返回 -1.
		int32_t IndexOf(int32_t start, uint8_t match) const;

		/// @brief 从本内存段查找匹配项所在的索引。
		/// @param match 匹配项。
		/// @return 找到了返回匹配位置的索引。没找到返回 -1.
		int32_t IndexOf(base::ReadOnlySpan const &match) const;

		/// @brief 从本内存段查找匹配项所在的索引。
		/// @param start 查找的起始索引。从此处往后开始查找。
		/// @param match 匹配项。
		/// @return 找到了返回匹配位置的索引。没找到返回 -1.
		int32_t IndexOf(int32_t start, base::ReadOnlySpan const &match) const;

	public: // 比较
		/**
		 * @brief 比较两段内存。
		 *
		 * @note 如果两段内存大小相等，且每个字节都相等，则这两段内存相等。
		 *
		 * @note 逐个字节比较，直到找到一对不等的字节，这个字节的大小关系就是内存段的大小
		 * 关系。例如本内存段第 1 个字节就和 another 的第 1 个字节不等了，并且本内存段的第
		 * 1 个字节小于 another 的第 1 个字节，则认为本内存段小于 another.
		 *
		 * @param another
		 * @return int32_t
		 */
		int32_t Compare(base::ReadOnlySpan const &another) const;

		/**
		 * @brief 比较两段内存。
		 *
		 * @note 如果两段内存大小相等，且每个字节都相等，则这两段内存相等。
		 *
		 * @note 逐个字节比较，直到找到一对不等的字节，这个字节的大小关系就是内存段的大小
		 * 关系。例如本内存段第 1 个字节就和 another 的第 1 个字节不等了，并且本内存段的第
		 * 1 个字节小于 another 的第 1 个字节，则认为本内存段小于 another.
		 *
		 * @param another
		 * @return int32_t
		 */
		int32_t Compare(base::Span const &another) const;

		/**
		 * @brief 基于 Compare 方法。
		 *
		 * @param another
		 * @return true
		 * @return false
		 */
		bool operator==(base::ReadOnlySpan const &another) const;

		/**
		 * @brief 基于 Compare 方法。
		 *
		 * @param another
		 * @return true
		 * @return false
		 */
		bool operator==(base::Span const &another) const;

		/**
		 * @brief 基于 Compare 方法。
		 *
		 * @param another
		 * @return true
		 * @return false
		 */
		bool operator<(base::ReadOnlySpan const &another) const;

		/**
		 * @brief 基于 Compare 方法。
		 *
		 * @param another
		 * @return true
		 * @return false
		 */
		bool operator<(base::Span const &another) const;

		/**
		 * @brief 基于 Compare 方法。
		 *
		 * @param another
		 * @return true
		 * @return false
		 */
		bool operator>(base::ReadOnlySpan const &another) const;

		/**
		 * @brief 基于 Compare 方法。
		 *
		 * @param another
		 * @return true
		 * @return false
		 */
		bool operator>(base::Span const &another) const;

		/**
		 * @brief 基于 Compare 方法。
		 *
		 * @param another
		 * @return true
		 * @return false
		 */
		bool operator<=(base::ReadOnlySpan const &another) const;

		/**
		 * @brief 基于 Compare 方法。
		 *
		 * @param another
		 * @return true
		 * @return false
		 */
		bool operator<=(base::Span const &another) const;

		/**
		 * @brief 基于 Compare 方法。
		 *
		 * @param another
		 * @return true
		 * @return false
		 */
		bool operator>=(base::ReadOnlySpan const &another) const;

		/**
		 * @brief 基于 Compare 方法。
		 *
		 * @param another
		 * @return true
		 * @return false
		 */
		bool operator>=(base::Span const &another) const;
	};
} // namespace base
