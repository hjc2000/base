#pragma once
#include <algorithm>
#include <base/container/Range.h>
#include <stdexcept>
#include <stdint.h>

namespace base
{
#pragma region 声明
	template <typename ItemType>
	class ArraySpan;

	template <typename ItemType>
	class ReadOnlyArraySpan;
#pragma endregion

#pragma region ReadOnlyArraySpan 定义

	/// @brief 只读的数组内存段。
	/// @note 引用一段内存，不会持有这段内存，不管理这段内存的生命周期。
	/// @tparam ItemType
	template <typename ItemType>
	class ReadOnlyArraySpan
	{
	private:
		ItemType const *_buffer = nullptr;
		int32_t _count = 0;

	public:
		ReadOnlyArraySpan() = default;

		ReadOnlyArraySpan(ItemType const *buffer, int32_t count)
		{
			_buffer = buffer;
			_count = count;

			if (_buffer == nullptr)
			{
				_count = 0;
			}
		}

		/// @brief 获取本对象引用的内存段。
		/// @return
		ItemType const *Buffer() const
		{
			return _buffer;
		}

		/// @brief 本对象引用的内存段的元素个数。
		/// @return
		int32_t Count() const
		{
			return _count;
		}

		/// @brief 将本对象的内存段的数据复制到 another 的内存段。
		/// @param another
		void CopyTo(base::ArraySpan<ItemType> &another) const;

		base::ReadOnlyArraySpan<ItemType> Slice(base::Range const &range) const
		{
			if (range.End() > Count())
			{
				throw std::out_of_range{"超出范围，无法切片。"};
			}

			return base::ReadOnlyArraySpan<ItemType>{Buffer() + range.Begin(), range.Size()};
		}
	};

#pragma endregion

#pragma region ArraySpan 定义

	/// @brief 数组内存段。
	/// @note 引用一段内存，不会持有这段内存，不管理这段内存的生命周期。
	/// @tparam ItemType
	template <typename ItemType>
	class ArraySpan
	{
	private:
		ItemType *_buffer = nullptr;
		int32_t _count = 0;

	public:
		ArraySpan() = default;

		ArraySpan(ItemType *buffer, int32_t count)
		{
			_buffer = buffer;
			_count = count;

			if (_buffer == nullptr)
			{
				_count = 0;
			}
		}

		/// @brief 获取本对象引用的内存段。
		/// @return
		ItemType *Buffer() const
		{
			return _buffer;
		}

		/// @brief 本对象引用的内存段的元素个数。
		/// @return
		int32_t Count() const
		{
			return _count;
		}

		/// @brief 翻转本对象引用的内存段中的元素。
		void Reverse() const
		{
			std::reverse(_buffer, _buffer + _count);
		}

		/// @brief 将 another 的内存段的数据复制到本对象的内存段。
		/// @param another
		void CopyFrom(base::ReadOnlyArraySpan<ItemType> const &another) const;

		/// @brief 将本对象的内存段的数据复制到 another 的内存段。
		/// @param another
		void CopyTo(base::ArraySpan<ItemType> &another) const
		{
			if (another.Count() != Count())
			{
				throw std::invalid_argument{"another 的 Count 属性必须和本对象的 Count 属性相等。"};
			}

			std::copy(Buffer(), Buffer() + Count(), another.Buffer());
		}

		base::ArraySpan<ItemType> Slice(base::Range const &range) const
		{
			if (range.End() > Count())
			{
				throw std::out_of_range{"超出范围，无法切片。"};
			}

			return base::ArraySpan<ItemType>{Buffer() + range.Begin(), range.Size()};
		}
	};

#pragma endregion

#pragma region ReadOnlyArraySpan 函数实现

	template <typename ItemType>
	inline void ReadOnlyArraySpan<ItemType>::CopyTo(base::ArraySpan<ItemType> &another) const
	{
		if (another.Count() != Count())
		{
			throw std::invalid_argument{"another 的 Count 属性必须和本对象的 Count 属性相等。"};
		}

		std::copy(Buffer(), Buffer() + Count(), another.Buffer());
	}

#pragma endregion

#pragma region ArraySpan 函数实现

	template <typename ItemType>
	inline void ArraySpan<ItemType>::CopyFrom(base::ReadOnlyArraySpan<ItemType> const &another) const
	{
		if (another.Count() != Count())
		{
			throw std::invalid_argument{"another 的 Count 属性必须和本对象的 Count 属性相等。"};
		}

		std::copy(another.Buffer(),
				  another.Buffer() + another.Count(),
				  Buffer());
	}

#pragma endregion
} // namespace base
