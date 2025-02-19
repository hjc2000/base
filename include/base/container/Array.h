#pragma once
#include <algorithm>
#include <array>
#include <base/container/IRawArray.h>
#include <stdexcept>

namespace base
{
	/// @brief 数组
	/// @tparam ItemType
	/// @tparam TCount
	template <typename ItemType, int32_t TCount>
	class Array :
		public base::IRawArray<ItemType>
	{
	private:
		std::array<ItemType, TCount> _arr{};

	public:
#pragma region 生命周期
		/// @brief 无参构造。
		/// @note 构造出的数组的元素也全部使用无参构造函数初始化。
		Array() = default;

		/// @brief 拷贝构造函数。
		/// @param o
		Array(Array<ItemType, TCount> const &o)
		{
			*this = o;
		}

		/// @brief 移动构造函数。
		/// @param o
		Array(Array<ItemType, TCount> &&o)
		{
			*this = o;
		}

		Array(base::ReadOnlyArraySpan<ItemType> const &span)
		{
			if (span.Count() != TCount)
			{
				throw std::invalid_argument{"span 的元素个数和本数组不同。"};
			}

			this->AsArraySpan().CopyFrom(span);
		}

		/// @brief 将初始化列表的数据拷贝过来。
		/// @param list 初始化列表。
		Array(std::initializer_list<ItemType> const &list)
		{
			int32_t i = 0;
			for (auto &item : list)
			{
				_arr[i++] = item;
			}
		}

		/// @brief 将 o 的数据拷贝过来。
		/// @param o
		Array(std::array<ItemType, TCount> const &o)
		{
			_arr = o;
		}

		/// @brief 赋值运算符。
		/// @param o
		/// @return
		Array<ItemType, TCount> &operator=(Array<ItemType, TCount> const &o)
		{
			if (this != &o)
			{
				_arr = o._arr;
			}

			return *this;
		}

		/// @brief 移动赋值运算符。
		/// @param o
		/// @return
		Array<ItemType, TCount> &operator=(Array<ItemType, TCount> &&o)
		{
			if (this != &o)
			{
				_arr = std::move(o._arr);
			}

			return *this;
		}

#pragma endregion

		/// @brief 索引数组中的元素。
		/// @param index
		/// @return
		ItemType &operator[](int32_t index)
		{
			if (index < 0 || index >= TCount)
			{
				throw std::out_of_range{"index 超出范围。"};
			}

			return _arr[index];
		}

		/// @brief 索引数组中的元素。
		/// @param index
		/// @return
		ItemType const &operator[](int32_t index) const
		{
			Array<ItemType, TCount> *self = const_cast<Array<ItemType, TCount> *>(this);
			return (*self)[index];
		}

		/// @brief 数组的大小
		/// @return
		int32_t Count() const override
		{
			return TCount;
		}

		/// @brief 获取底层的缓冲区
		/// @return
		ItemType *Buffer() override
		{
			return _arr.data();
		}

		/// @brief 获取底层的缓冲区
		/// @return
		ItemType const *Buffer() const override
		{
			return _arr.data();
		}
	};
} // namespace base
