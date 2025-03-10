#pragma once
#include <base/container/Array.h>
#include <base/container/ArraySpan.h>
#include <base/container/Range.h>
#include <base/stream/Span.h>
#include <cstdint>

namespace base
{
	class String;

	///
	/// @brief 只读内存段。
	///
	/// @note 引用一段只读的内存。
	///
	/// @warning 要求本类对象的生命周期内，引用的外部内存始终存活。
	///
	class ReadOnlySpan :
		public base::IEnumerable<uint8_t const>
	{
	private:
		uint8_t const *_buffer = nullptr;
		int32_t _size = 0;

	public:
		/* #region 生命周期 */

		///
		/// @brief 无参构造函数。引用一段空内存。
		///
		/// @note 可以通过 Size 属性判断本对象是否引用到了有效的内存。
		///
		ReadOnlySpan() = default;

		///
		/// @brief 引用 buffer 指向的内存。在本对象的生命周期内，buffer 指向的内存必须始终存活。
		///
		/// @param buffer 要引用的内存。
		/// @param size buffer 的大小。
		///
		ReadOnlySpan(uint8_t const *buffer, int32_t size);

		///
		/// @brief 引用字符串的内存段。不包括结尾的空字符。
		///
		/// @param str
		///
		ReadOnlySpan(char const *str);

		///
		/// @brief 引用字符串的内存段。不包括结尾的空字符。
		///
		/// @param str
		///
		ReadOnlySpan(base::String const &str);

		///
		/// @brief 从 base::ReadOnlyArraySpan<uint8_t> 构造，引用它所引用的内存段。
		///
		/// @param span
		///
		ReadOnlySpan(base::ReadOnlyArraySpan<uint8_t> const &span);

		///
		/// @brief 通过一个可读可写的 Span 构造只读的 ReadOnlySpan.
		///
		/// @param o
		///
		ReadOnlySpan(base::Span const &o);

		///
		/// @brief 从 base::Array<uint8_t, TCount> 构造，引用它所引用的内存。
		///
		/// @tparam TCount
		/// @param array
		///
		template <int32_t TCount>
		ReadOnlySpan(base::Array<uint8_t, TCount> const &array)
			: base::ReadOnlySpan(array.Span())
		{
		}

		virtual ~ReadOnlySpan() = default;
		/* #endregion */

		/* #region 索引器 */

		///
		/// @brief 索引一个字节。
		///
		/// @param index
		/// @return uint8_t const&
		///
		uint8_t const &operator[](int32_t index) const;

		///
		/// @brief 获得指定范围的切片。
		///
		/// @param range
		/// @return base::ReadOnlySpan
		///
		base::ReadOnlySpan operator[](base::Range const &range) const;
		/* #endregion */

		///
		/// @brief 所引用的内存。
		///
		/// @return uint8_t const*
		///
		uint8_t const *Buffer() const;

		///
		/// @brief 所引用的内存大小。
		///
		/// @return int32_t
		///
		int32_t Size() const;

		/* #region Slice */

		///
		/// @brief 将本 ReadOnlySpan 切片，得到一个更小的 ReadOnlySpan.
		///
		/// @param start 切片起始位置。
		/// @param size 切片大小。
		/// @return base::ReadOnlySpan
		///
		base::ReadOnlySpan Slice(int32_t start, int32_t size) const;

		///
		/// @brief 获得指定范围的切片。
		///
		/// @param range
		/// @return base::ReadOnlySpan
		///
		base::ReadOnlySpan Slice(base::Range const &range) const;
		/* #endregion */

		///
		/// @brief 获取非 const 迭代器。
		///
		/// @return std::shared_ptr<base::IEnumerator<uint8_t const>>
		///
		std::shared_ptr<base::IEnumerator<uint8_t const>> GetEnumerator() override;

		/* #region IndexOf */

		///
		/// @brief 在本内存段中从前往后查找最后一个匹配项所在的索引。
		///
		/// @param match 匹配项。
		///
		/// @return int32_t 找到了返回匹配位置的索引。没找到返回 -1.
		///
		int32_t IndexOf(uint8_t match) const;

		///
		/// @brief 从本内存段查找匹配项所在的索引。
		///
		/// @param start 查找的起始索引。从此处往后开始查找。
		/// @param match 匹配项。
		///
		/// @return int32_t 找到了返回匹配位置的索引。没找到返回 -1.
		///
		int32_t IndexOf(int32_t start, uint8_t match) const;

		///
		/// @brief 从本内存段查找匹配项所在的索引。
		///
		/// @param match 匹配项。
		///
		/// @return int32_t 找到了返回匹配位置的索引。没找到返回 -1.
		///
		int32_t IndexOf(base::ReadOnlySpan const &match) const;

		///
		/// @brief 从本内存段查找匹配项所在的索引。
		///
		/// @param start 查找的起始索引。从此处往后开始查找。
		/// @param match 匹配项。
		///
		/// @return int32_t 找到了返回匹配位置的索引。没找到返回 -1.
		///
		int32_t IndexOf(int32_t start, base::ReadOnlySpan const &match) const;
		/* #endregion */

		/* #region LastIndexOf */

		///
		/// @brief 从后往前查找最后一个匹配项所在的索引。
		///
		/// @param match 匹配项。
		///
		/// @return int32_t 找到了返回匹配位置的索引。没找到返回 -1.
		///
		int32_t LastIndexOf(uint8_t match) const;

		///
		/// @brief 从 start 索引位置开始，从后往前查找匹配项。
		///
		/// @param start 要从后往前查找的起始索引位置。
		/// @param match 匹配项。
		///
		/// @return int32_t 找到了返回匹配位置的索引。没找到返回 -1.
		///
		int32_t LastIndexOf(int32_t start, uint8_t match) const;

		///
		/// @brief 从后往前查找最后一个匹配位置的索引。
		///
		/// @param match 匹配项。
		/// @return int32_t
		///
		int32_t LastIndexOf(base::ReadOnlySpan const &match) const;

		///
		/// @brief 从 start 索引位置开始，从后往前查找匹配项。
		///
		/// @param start 要从后往前查找的起始索引位置。
		/// @param match 匹配项。
		///
		/// @return int32_t 找到了返回匹配位置的索引。没找到返回 -1.
		///
		int32_t LastIndexOf(int32_t start, base::ReadOnlySpan const &match) const;

		/* #endregion */

		/* #region 开始，结束 */

		///
		/// @brief 检查本内存段是否以 match 开头。
		///
		/// @param match
		/// @return true
		/// @return false
		///
		bool StartWith(uint8_t match);

		///
		/// @brief 检查本内存段是否以 match 开头。
		///
		/// @param match
		/// @return true
		/// @return false
		///
		bool StartWith(base::ReadOnlySpan const &match);

		///
		/// @brief 检查本内存段是否以 match 结尾。
		///
		/// @param match
		/// @return true
		/// @return false
		///
		bool EndWith(uint8_t match);

		///
		/// @brief 检查本内存段是否以 match 结尾。
		///
		/// @param match
		/// @return true
		/// @return false
		///
		bool EndWith(base::ReadOnlySpan const &match);

		/* #endregion */

		/* #region 比较 */

		///
		/// @brief 比较两段内存。
		///
		/// @note 如果两段内存大小相等，且每个字节都相等，则这两段内存相等。
		///
		/// @note 逐个字节比较，直到找到一对不等的字节，这个字节的大小关系就是内存段的大小
		/// 关系。例如本内存段第 1 个字节就和 another 的第 1 个字节不等了，并且本内存段的第
		/// 1 个字节小于 another 的第 1 个字节，则认为本内存段小于 another.
		///
		/// @param another
		/// @return int32_t
		///
		int32_t Compare(base::ReadOnlySpan const &another) const;

		///
		/// @brief 比较两段内存。
		///
		/// @note 如果两段内存大小相等，且每个字节都相等，则这两段内存相等。
		///
		/// @note 逐个字节比较，直到找到一对不等的字节，这个字节的大小关系就是内存段的大小
		/// 关系。例如本内存段第 1 个字节就和 another 的第 1 个字节不等了，并且本内存段的第
		/// 1 个字节小于 another 的第 1 个字节，则认为本内存段小于 another.
		///
		/// @param another
		/// @return int32_t
		///
		int32_t Compare(base::Span const &another) const;

		///
		/// @brief 基于 Compare 方法。
		///
		/// @param another
		/// @return true
		/// @return false
		///
		bool operator==(base::ReadOnlySpan const &another) const;

		///
		/// @brief 基于 Compare 方法。
		///
		/// @param another
		/// @return true
		/// @return false
		///
		bool operator==(base::Span const &another) const;

		///
		/// @brief 基于 Compare 方法。
		///
		/// @param another
		/// @return true
		/// @return false
		///
		bool operator<(base::ReadOnlySpan const &another) const;

		///
		/// @brief 基于 Compare 方法。
		///
		/// @param another
		/// @return true
		/// @return false
		///
		bool operator<(base::Span const &another) const;

		///
		/// @brief 基于 Compare 方法。
		///
		/// @param another
		/// @return true
		/// @return false
		///
		bool operator>(base::ReadOnlySpan const &another) const;

		///
		/// @brief 基于 Compare 方法。
		///
		/// @param another
		/// @return true
		/// @return false
		///
		bool operator>(base::Span const &another) const;

		///
		/// @brief 基于 Compare 方法。
		///
		/// @param another
		/// @return true
		/// @return false
		///
		bool operator<=(base::ReadOnlySpan const &another) const;

		///
		/// @brief 基于 Compare 方法。
		///
		/// @param another
		/// @return true
		/// @return false
		///
		bool operator<=(base::Span const &another) const;

		///
		/// @brief 基于 Compare 方法。
		///
		/// @param another
		/// @return true
		/// @return false
		///
		bool operator>=(base::ReadOnlySpan const &another) const;

		///
		/// @brief 基于 Compare 方法。
		///
		/// @param another
		/// @return true
		/// @return false
		///
		bool operator>=(base::Span const &another) const;
		/* #endregion */
	};
} // namespace base
