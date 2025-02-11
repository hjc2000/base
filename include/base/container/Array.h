#pragma once
#include <algorithm>
#include <array>
#include <base/container/IRawArray.h>
#include <base/container/iterator/IEnumerable.h>
#include <stdexcept>
#include <string>

namespace base
{
	/// @brief 数组
	/// @tparam ItemType
	/// @tparam TCount
	template <typename ItemType, int32_t TCount>
	class Array :
		public base::IEnumerable<ItemType>,
		public base::IRawArray<ItemType>
	{
	private:
		std::array<ItemType, TCount> _arr{};

#pragma region 迭代器

		class Enumerator :
			public base::IEnumerator<ItemType>
		{
		private:
			int _index = 0;
			bool _first_move = true;
			std::array<ItemType, TCount> &_arr;

		public:
			Enumerator(std::array<ItemType, TCount> &arr)
				: _arr(arr)
			{
				Reset();
			}

			/// @brief 获取当前值的引用
			/// @return
			ItemType &CurrentValue() override
			{
				return _arr[_index];
			}

			/// @brief 迭代器前进到下一个值
			/// @return
			bool MoveNext() override
			{
				if (_first_move)
				{
					_first_move = false;
				}
				else
				{
					_index++;
				}

				if (_index < 0 || _index >= TCount)
				{
					return false;
				}

				return true;
			}

			/// @brief 将迭代器重置到容器开始的位置。
			/// @note 开始位置是第一个元素前。也就是说重置后，要调用一次 MoveNext 才能获取到第一个值。
			void Reset() override
			{
				_first_move = true;
				_index = 0;
			}
		};

#pragma endregion

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
			: Array(0, list)
		{
		}

		/// @brief 将初始化列表的数据拷贝过来，放在指定的起始位置。
		/// @param start 起始位置。
		/// @param list 初始化列表。
		Array(int start, std::initializer_list<ItemType> const &list)
		{
			if (start + list.size() > TCount)
			{
				throw std::out_of_range{
					std::string{"本数组无法在 start = "} +
						std::to_string(start) +
						std::string{" 的情况下装下初始化列表。"},
				};
			}

			int i = start;
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
		ItemType &operator[](int index)
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
		ItemType const &operator[](int index) const
		{
			Array<ItemType, TCount> *self = const_cast<Array<ItemType, TCount> *>(this);
			return (*self)[index];
		}

		/// @brief 获取迭代器
		/// @return
		std::shared_ptr<IEnumerator<ItemType>> GetEnumerator() override
		{
			return std::shared_ptr<IEnumerator<ItemType>>{
				new Enumerator{_arr},
			};
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
