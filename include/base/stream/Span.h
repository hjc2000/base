#pragma once
#include <base/container/Array.h>
#include <base/container/ArraySpan.h>
#include <base/container/iterator/IEnumerable.h>
#include <base/container/Range.h>
#include <cstdint>

namespace base
{
	class ReadOnlySpan;
	class String;

	///
	/// @brief 引用一段连续内存，不持有这段内存。
	///
	/// @warning 要求本类对象的生命周期内，引用的外部内存始终存活。
	///
	/// @note 本类的很多方法都有 const 修饰符。这并不是说不会改变所引用的内存，
	/// 而是不会改变本对象的字段，即不会变成引用别的内存，或者更改引用的内存段大小。
	///
	class Span :
		public base::IEnumerable<uint8_t>
	{
	private:
		uint8_t *_buffer = nullptr;
		int32_t _size = 0;

	public:
		/* #region 生命周期 */

		///
		/// @brief 无参构造函数。引用一段空内存。
		///
		/// @note 可以通过 Size 属性判断本对象是否引用到了有效的内存。
		///
		Span() = default;

		///
		/// @brief 引用 buffer 指向的内存。在本对象的生命周期内，buffer 指向的内存必须始终存活。
		///
		/// @param buffer 要引用的内存。
		/// @param size buffer 的大小。
		///
		Span(uint8_t *buffer, int32_t size);

		///
		/// @brief 引用字符串的内存段。不包括结尾的空字符。
		///
		/// @param str
		///
		Span(char *str);

		///
		/// @brief 引用字符串的内存段。不包括结尾的空字符。
		///
		/// @param str
		///
		Span(base::String &str);

		///
		/// @brief 从 base::ArraySpan<uint8_t> 构造，引用它所引用的内存。
		///
		/// @param span
		///
		Span(base::ArraySpan<uint8_t> const &span);

		///
		/// @brief 从 base::Array<uint8_t, TCount> 构造，引用它所引用的内存。
		///
		/// @tparam TCount
		/// @param array
		///
		template <int32_t TCount>
		Span(base::Array<uint8_t, TCount> &array)
			: base::Span(array.Span())
		{
		}

		virtual ~Span() = default;
		/* #endregion */

		/* #region 索引器 */

		///
		/// @brief 索引一个字节。
		///
		/// @param index
		/// @return uint8_t&
		///
		uint8_t &operator[](int32_t index) const;

		///
		/// @brief 获得指定范围的切片。
		///
		/// @param range
		/// @return base::Span
		///
		base::Span operator[](base::Range const &range) const;
		/* #endregion */

		///
		/// @brief 所引用的内存。
		///
		/// @return uint8_t*
		///
		uint8_t *Buffer() const;

		///
		/// @brief 所引用的内存大小。
		///
		/// @return int32_t
		///
		int32_t Size() const;

		/* #region Slice */

		///
		/// @brief 将本 Span 切片，得到一个更小的 Span.
		///
		/// @param start 切片起始位置。
		/// @param size 切片大小。
		///
		/// @return base::Span
		///
		base::Span Slice(int32_t start, int32_t size) const;

		///
		/// @brief 获得指定范围的切片。
		///
		/// @param range
		/// @return base::Span
		///
		base::Span Slice(base::Range const &range) const;
		/* #endregion */

		///
		/// @brief 翻转本 Span 所引用的内存段。
		///
		///
		void Reverse() const;

		/* #region CopyFrom */

		///
		/// @brief 将 span 所引用的内存的数据拷贝过来。
		///
		/// @param span
		///
		void CopyFrom(base::ReadOnlySpan const &span) const;

		///
		/// @brief 将 span 所引用的内存的数据拷贝过来。
		///
		/// @param span
		///
		void CopyFrom(base::Span const &span) const;

		///
		/// @brief 将 list 的数据拷贝过来。
		///
		/// @param list
		///
		void CopyFrom(std::initializer_list<uint8_t> const &list) const;
		/* #endregion */

		using base::IEnumerable<uint8_t>::GetEnumerator;

		///
		/// @brief 获取非 const 迭代器。
		///
		/// @return std::shared_ptr<base::IEnumerator<uint8_t>>
		///
		std::shared_ptr<base::IEnumerator<uint8_t>> GetEnumerator() override;

		/* #region 填充 */

		///
		/// @brief 将本 Span 所引用的内存的每一个字节都填充为 0.
		///
		///
		void FillWithZero();

		///
		/// @brief 将所有字节填充为 value.
		///
		/// @param value
		///
		void FillWith(uint8_t value);

		/* #endregion */

		/* #region IndexOf */

		///
		/// @brief 从本内存段查找匹配项所在的索引。
		///
		/// @param match 匹配项。
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
		/// @return int32_t 找到了返回匹配位置的索引。没找到返回 -1.
		///
		int32_t IndexOf(base::ReadOnlySpan const &match) const;

		///
		/// @brief 从本内存段查找匹配项所在的索引。
		///
		/// @param start 查找的起始索引。从此处往后开始查找。
		/// @param match 匹配项。
		/// @return int32_t 找到了返回匹配位置的索引。没找到返回 -1.
		///
		int32_t IndexOf(int32_t start, base::ReadOnlySpan const &match) const;
		/* #endregion */

		/* #region LastIndexOf */

		///
		/// @brief 从后往前查找最后一个匹配项所在的索引。
		///
		/// @param match 匹配项。
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
