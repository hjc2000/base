#pragma once
#include <base/container/ArraySpan.h>
#include <base/container/iterator/IEnumerable.h>
#include <base/container/Range.h>
#include <cstdint>

namespace base
{
	class ReadOnlySpan;

	/// @brief 引用一段连续内存，不持有这段内存。
	/// @warning 要求本类对象的生命周期内，引用的外部内存始终存活。
	/// @note 本类的很多方法都有 const 修饰符。这并不是说不会改变所引用的内存，而是不会改变本对象的字段，
	/// 即不会变成引用别的内存，或者更改引用的内存段大小。
	class Span :
		public base::IEnumerable<uint8_t>
	{
	private:
		uint8_t *_buffer = nullptr;
		int32_t _size = 0;

	public:
#pragma region 生命周期
		/// @brief 无参构造函数。引用一段空内存。
		/// @note 可以通过 Size 属性判断本对象是否引用到了有效的内存。
		Span() = default;

		/// @brief 引用 buffer 指向的内存。在本对象的生命周期内，buffer 指向的内存必须始终存活。
		/// @param buffer 要引用的内存。
		/// @param size buffer 的大小。
		Span(uint8_t *buffer, int32_t size);

		Span(base::ArraySpan<uint8_t> const &span);

		/// @brief 拷贝构造函数。
		/// @note 不会拷贝对方引用的内存，而是将对方引用的内存的指针拿过来，
		/// 与对方引用同一段内存。
		/// @param o
		Span(Span const &o);

		/// @brief 赋值运算符
		/// @param o
		/// @return
		Span &operator=(Span const &o);
#pragma endregion

#pragma region operator[]
		uint8_t &operator[](int32_t index) const;

		/// @brief 获得指定范围的切片。
		/// @param range
		/// @return
		base::Span operator[](base::Range const &range) const;
#pragma endregion

		/// @brief 所引用的内存。
		/// @return
		uint8_t *Buffer() const;

		/// @brief 所引用的内存大小
		/// @return
		int32_t Size() const;

#pragma region Slice
		/// @brief 将本 Span 切片，得到一个更小的 Span.
		/// @param start 切片起始位置。
		/// @param size 切片大小。
		/// @return
		base::Span Slice(int32_t start, int32_t size) const;

		/// @brief 获得指定范围的切片。
		/// @param range
		/// @return
		base::Span Slice(base::Range const &range) const;
#pragma endregion

		/// @brief 翻转本 Span 所引用的内存段。
		void Reverse() const;

#pragma region CopyFrom
		/// @brief 将 span 所引用的内存的数据拷贝过来。
		/// @param span
		void CopyFrom(base::ReadOnlySpan const &span) const;

		/// @brief 将 span 所引用的内存的数据拷贝过来。
		/// @param span
		void CopyFrom(base::Span const &span) const;

		/// @brief 将 list 的数据拷贝过来。
		/// @param list
		void CopyFrom(std::initializer_list<uint8_t> const &list) const;
#pragma endregion

		/// @brief 获取非 const 迭代器
		/// @return
		std::shared_ptr<base::IEnumerator<uint8_t>> GetEnumerator() override;

#pragma region 填充
		/// @brief 将本 Span 所引用的内存的每一个字节都填充为 0.
		void FillWithZero();

		/// @brief 将所有字节填充为 value.
		/// @param value
		void FillWith(uint8_t value);
#pragma endregion

#pragma region IndexOf
		/// @brief 查找指定值所在的第一个索引。
		/// @param match
		/// @return 找到则返回索引，没找到则返回 -1.
		int32_t IndexOf(uint8_t match) const;

		/// @brief 查找指定子内存段所在的第一个索引。
		/// @param match
		/// @return 找到则返回索引，没找到则返回 -1.
		int32_t IndexOf(base::ReadOnlySpan const &match) const;
#pragma endregion

#pragma region 比较
		int32_t Compare(base::ReadOnlySpan const &another) const;
		int32_t Compare(base::Span const &another) const;

		/// @brief another 和本内存段大小相等，且每一个字节都相等，则相等。
		/// @param another
		/// @return another 和本内存段大小相等，且每一个字节都相等，则返回 true，否则返回 false.
		bool operator==(base::ReadOnlySpan const &another) const
		{
			return Compare(another) == 0;
		}

		/// @brief another 和本内存段大小相等，且每一个字节都相等，则相等。
		/// @param another
		/// @return another 和本内存段大小相等，且每一个字节都相等，则返回 true，否则返回 false.
		bool operator==(base::Span const &another) const
		{
			return Compare(another) == 0;
		}

		bool operator<(base::ReadOnlySpan const &another) const
		{
			return Compare(another) < 0;
		}

		bool operator<(base::Span const &another) const
		{
			return Compare(another) < 0;
		}

		bool operator>(base::ReadOnlySpan const &another) const
		{
			return Compare(another) > 0;
		}

		bool operator>(base::Span const &another) const
		{
			return Compare(another) > 0;
		}

		bool operator<=(base::ReadOnlySpan const &another) const
		{
			return Compare(another) <= 0;
		}

		bool operator<=(base::Span const &another) const
		{
			return Compare(another) <= 0;
		}

		bool operator>=(base::ReadOnlySpan const &another) const
		{
			return Compare(another) >= 0;
		}

		bool operator>=(base::Span const &another) const
		{
			return Compare(another) >= 0;
		}

#pragma endregion
	};
} // namespace base
