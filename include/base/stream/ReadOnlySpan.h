#pragma once
#include "base/container/Array.h"
#include "base/container/ArraySpan.h"
#include "base/container/Range.h"
#include "base/string/define.h"
#include <algorithm>
#include <cstdint>
#include <cstring>
#include <stdexcept>

namespace base
{
	///
	/// @brief 只读内存段。
	///
	/// @note 引用一段只读的内存。
	///
	/// @warning 要求本类对象的生命周期内，引用的外部内存始终存活。
	///
	class ReadOnlySpan
	{
	private:
		uint8_t const *_buffer = nullptr;
		int64_t _size = 0;

	public:
		/* #region 构造函数 */

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
		ReadOnlySpan(uint8_t const *buffer, int64_t size)
		{
			_buffer = buffer;
			_size = size;

			if (_buffer == nullptr)
			{
				_size = 0;
			}
		}

		///
		/// @brief 引用字符串的内存段。不包括结尾的空字符。
		///
		/// @param str
		///
		ReadOnlySpan(char const *str)
		{
			int64_t white_char_index = 0;
			while (true)
			{
				if (str[white_char_index] == '\0')
				{
					break;
				}

				white_char_index++;
			}

			_buffer = reinterpret_cast<uint8_t const *>(str);
			_size = white_char_index;
		}

		///
		/// @brief 从 base::ArraySpan<uint8_t> 构造，引用它所引用的内存。
		///
		/// @param span
		///
		ReadOnlySpan(base::ArraySpan<uint8_t> const &span)
		{
			_buffer = span.Buffer();
			_size = span.Count();

			if (_buffer == nullptr)
			{
				_size = 0;
			}
		}

		///
		/// @brief 从 base::ReadOnlyArraySpan<uint8_t> 构造，引用它所引用的内存段。
		///
		/// @param span
		///
		ReadOnlySpan(base::ReadOnlyArraySpan<uint8_t> const &span)
		{
			_buffer = span.Buffer();
			_size = span.Count();

			if (_buffer == nullptr)
			{
				_size = 0;
			}
		}

		///
		/// @brief 从 base::Array<uint8_t, TCount> 构造，引用它所引用的内存。
		///
		/// @tparam TCount
		/// @param array
		///
		template <int64_t TCount>
		ReadOnlySpan(base::Array<uint8_t, TCount> const &array)
			: base::ReadOnlySpan(array.Span())
		{
		}

		/* #endregion */

		/* #region 索引器 */

		///
		/// @brief 索引一个字节。
		///
		/// @param index
		///
		/// @return
		///
		uint8_t const &operator[](int64_t index) const
		{
			if (index < 0 || index >= _size)
			{
				throw std::out_of_range{CODE_POS_STR + "索引超出范围"};
			}

			return _buffer[index];
		}

		///
		/// @brief 获得指定范围的切片。
		///
		/// @param range
		///
		/// @return
		///
		base::ReadOnlySpan operator[](base::Range const &range) const
		{
			return Slice(range);
		}

		/* #endregion */

		///
		/// @brief 所引用的内存。
		///
		/// @return
		///
		uint8_t const *Buffer() const
		{
			return _buffer;
		}

		///
		/// @brief 所引用的内存大小。
		///
		/// @return
		///
		int64_t Size() const
		{
			return _size;
		}

		/* #region Slice */

		///
		/// @brief 将本 ReadOnlySpan 切片，得到一个更小的 ReadOnlySpan.
		///
		/// @param start 切片起始位置。
		/// @param size 切片大小。
		///
		/// @return
		///
		base::ReadOnlySpan Slice(int64_t start, int64_t size) const
		{
			if (start < 0)
			{
				throw std::out_of_range{CODE_POS_STR + "start 不能小于 0."};
			}

			if (size < 0)
			{
				throw std::out_of_range{CODE_POS_STR + "size 不能小于 0."};
			}

			if (start + size > _size)
			{
				throw std::out_of_range{CODE_POS_STR + "切片超出范围。"};
			}

			return base::ReadOnlySpan{_buffer + start, size};
		}

		///
		/// @brief 获得指定范围的切片。
		///
		/// @param range
		///
		/// @return
		///
		base::ReadOnlySpan Slice(base::Range const &range) const
		{
			return Slice(range.Begin(), range.Size());
		}

		/* #endregion */

		/* #region IndexOf */

		///
		/// @brief 在本内存段中从前往后查找最后一个匹配项所在的索引。
		///
		/// @param match 匹配项。
		///
		/// @return 找到了返回匹配位置的索引。没找到返回 -1.
		///
		int64_t IndexOf(uint8_t match) const
		{
			for (int64_t i = 0; i < _size; i++)
			{
				if (_buffer[i] == match)
				{
					return i;
				}
			}

			return -1;
		}

		///
		/// @brief 从本内存段查找匹配项所在的索引。
		///
		/// @param start 查找的起始索引。从此处往后开始查找。
		/// @param match 匹配项。
		///
		/// @return 找到了返回匹配位置的索引。没找到返回 -1.
		///
		int64_t IndexOf(int64_t start, uint8_t match) const
		{
			if (start < 0)
			{
				throw std::invalid_argument{CODE_POS_STR + "start 不能小于 0."};
			}

			if (start >= Size())
			{
				throw std::invalid_argument{CODE_POS_STR + "start 索引超出边界，大于 Size."};
			}

			int64_t result = Slice(base::Range{start, _size}).IndexOf(match);
			if (result < 0)
			{
				return result;
			}

			return start + result;
		}

		///
		/// @brief 从本内存段查找匹配项所在的索引。
		///
		/// @param match 匹配项。
		///
		/// @return 找到了返回匹配位置的索引。没找到返回 -1.
		///
		int64_t IndexOf(base::ReadOnlySpan const &match) const
		{
			if (match.Size() <= 0)
			{
				throw std::invalid_argument{CODE_POS_STR + "match 的长度必须大于 0."};
			}

			if (Size() < match.Size())
			{
				// 本内存段的大小还没 match 的大，不可能匹配。
				return -1;
			}

			uint8_t const first_byte_of_match = match[0];

			for (int64_t i = 0; i < Size(); i++)
			{
				if (i + match.Size() > Size())
				{
					// 剩下的未匹配的部分已经没有 match 的长的，不可能匹配了。
					return -1;
				}

				if (_buffer[i] == first_byte_of_match)
				{
					// 匹配到第 1 个字符了。
					if (Slice(i, match.Size()) == match)
					{
						return i;
					}
				}
			}

			return -1;
		}

		///
		/// @brief 从本内存段查找匹配项所在的索引。
		///
		/// @param start 查找的起始索引。从此处往后开始查找。
		/// @param match 匹配项。
		///
		/// @return 找到了返回匹配位置的索引。没找到返回 -1.
		///
		int64_t IndexOf(int64_t start, base::ReadOnlySpan const &match) const
		{
			if (start < 0)
			{
				throw std::invalid_argument{CODE_POS_STR + "start 不能小于 0."};
			}

			if (start >= Size())
			{
				throw std::invalid_argument{CODE_POS_STR + "start 索引超出边界，大于 Size."};
			}

			int64_t result = Slice(base::Range{start, _size}).IndexOf(match);
			if (result < 0)
			{
				return result;
			}

			return start + result;
		}

		/* #endregion */

		/* #region LastIndexOf */

		///
		/// @brief 从后往前查找最后一个匹配项所在的索引。
		///
		/// @param match 匹配项。
		///
		/// @return 找到了返回匹配位置的索引。没找到返回 -1.
		///
		int64_t LastIndexOf(uint8_t match) const
		{
			for (int64_t i = _size - 1; i >= 0; i--)
			{
				if (_buffer[i] == match)
				{
					return i;
				}
			}

			return -1;
		}

		///
		/// @brief 从 start 索引位置开始，从后往前查找匹配项。
		///
		/// @param start 要从后往前查找的起始索引位置。
		/// @param match 匹配项。
		///
		/// @return 找到了返回匹配位置的索引。没找到返回 -1.
		///
		int64_t LastIndexOf(int64_t start, uint8_t match) const
		{
			if (start < 0)
			{
				throw std::invalid_argument{CODE_POS_STR + "start 不能小于 0."};
			}

			if (start >= Size())
			{
				throw std::invalid_argument{CODE_POS_STR + "start 索引超出边界，大于 Size."};
			}

			int64_t result = Slice(base::Range{0, start + 1}).LastIndexOf(match);
			return result;
		}

		///
		/// @brief 从后往前查找最后一个匹配位置的索引。
		///
		/// @param match 匹配项。
		///
		/// @return
		///
		int64_t LastIndexOf(base::ReadOnlySpan const &match) const
		{
			if (match.Size() <= 0)
			{
				throw std::invalid_argument{CODE_POS_STR + "match 的长度必须大于 0."};
			}

			if (Size() < match.Size())
			{
				// 本内存段的大小还没 match 的大，不可能匹配。
				return -1;
			}

			uint8_t const first_byte_of_match = match[0];

			for (int64_t i = Size() - match.Size(); i >= 0; i--)
			{
				if (_buffer[i] == first_byte_of_match)
				{
					// 匹配到第 1 个字符了。
					if (Slice(i, match.Size()) == match)
					{
						return i;
					}
				}
			}

			return -1;
		}

		///
		/// @brief 从 start 索引位置开始，从后往前查找匹配项。
		///
		/// @param start 要从后往前查找的起始索引位置。
		/// @param match 匹配项。
		///
		/// @return 找到了返回匹配位置的索引。没找到返回 -1.
		///
		int64_t LastIndexOf(int64_t start, base::ReadOnlySpan const &match) const
		{
			if (start < 0)
			{
				throw std::invalid_argument{CODE_POS_STR + "start 不能小于 0."};
			}

			if (start >= Size())
			{
				throw std::invalid_argument{CODE_POS_STR + "start 索引超出边界，大于 Size."};
			}

			int64_t result = Slice(base::Range{0, start + 1}).LastIndexOf(match);
			return result;
		}

		/* #endregion */

		/* #region 开始，结束 */

		///
		/// @brief 检查本内存段是否以 match 开头。
		///
		/// @param match
		///
		/// @return
		///
		bool StartWith(uint8_t match)
		{
			if (Size() == 0)
			{
				return false;
			}

			return _buffer[0] == match;
		}

		///
		/// @brief 检查本内存段是否以 match 开头。
		///
		/// @param match
		///
		/// @return
		///
		bool StartWith(base::ReadOnlySpan const &match)
		{
			if (Size() < match.Size())
			{
				return false;
			}

			return Slice(base::Range{0, match.Size()}) == match;
		}

		///
		/// @brief 检查本内存段是否以 match 结尾。
		///
		/// @param match
		///
		/// @return
		///
		bool EndWith(uint8_t match)
		{
			if (Size() == 0)
			{
				return false;
			}

			return _buffer[_size - 1] == match;
		}

		///
		/// @brief 检查本内存段是否以 match 结尾。
		///
		/// @param match
		///
		/// @return
		///
		bool EndWith(base::ReadOnlySpan const &match)
		{
			if (Size() < match.Size())
			{
				return false;
			}

			return Slice(base::Range{_size - match.Size(), _size}) == match;
		}

		/* #endregion */

		/* #region 比较 */

		///
		/// @brief 基于字典序的比较逻辑比较两段内存。
		///
		/// @param another
		///
		/// @return
		///
		int64_t Compare(base::ReadOnlySpan const &another) const
		{
			if (Size() == 0 && another.Size() == 0)
			{
				// 两段内存的大小都为 0，也认为相等。
				return 0;
			}

			int64_t result = std::memcmp(Buffer(),
										 another.Buffer(),
										 std::min<int64_t>(Size(), another.Size()));

			if (result == 0)
			{
				// 如果比较结果 == 0, 说明说比较的直接都相等。接下来就是谁更长，谁的字典序更后面了。
				// 如果本内存段更长，减法的结果是正数，表示本内存段应该排更后面。
				// 如果本内存段更短，减法的结果是负数，表示本内存段应该排更后面。
				return Size() - another.Size();
			}

			return result;
		}

		///
		/// @brief 基于 Compare 方法。
		///
		/// @param another
		///
		/// @return
		///
		bool operator==(base::ReadOnlySpan const &another) const
		{
			return Compare(another) == 0;
		}

		///
		/// @brief 基于 Compare 方法。
		///
		/// @param another
		///
		/// @return
		///
		bool operator<(base::ReadOnlySpan const &another) const
		{
			return Compare(another) < 0;
		}

		///
		/// @brief 基于 Compare 方法。
		///
		/// @param another
		///
		/// @return
		///
		bool operator>(base::ReadOnlySpan const &another) const
		{
			return Compare(another) > 0;
		}

		///
		/// @brief 基于 Compare 方法。
		///
		/// @param another
		///
		/// @return
		///
		bool operator<=(base::ReadOnlySpan const &another) const
		{
			return Compare(another) <= 0;
		}

		///
		/// @brief 基于 Compare 方法。
		///
		/// @param another
		///
		/// @return
		///
		bool operator>=(base::ReadOnlySpan const &another) const
		{
			return Compare(another) >= 0;
		}

		/* #endregion */

		/* #region 迭代 */

		uint8_t const *begin() const
		{
			return _buffer;
		}

		uint8_t const *end() const
		{
			return _buffer + _size;
		}

		/* #endregion */
	};

} // namespace base
