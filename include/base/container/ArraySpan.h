#pragma once
#include <algorithm>
#include <base/container/iterator/IEnumerable.h>
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

	/// @brief 只读的数组内存段。
	/// @note 引用一段内存，不会持有这段内存，不管理这段内存的生命周期。
	/// @tparam ItemType
	template <typename ItemType>
	class ReadOnlyArraySpan :
		public base::IEnumerable<ItemType const>
	{
	private:
		ItemType const *_buffer = nullptr;
		int32_t _count = 0;

#pragma region 迭代器

		class Enumerator :
			public base::IEnumerator<ItemType const>
		{
		private:
			int _index = 0;
			bool _first_move = true;
			ItemType const *_buffer{};
			int32_t _count = 0;

		public:
			Enumerator(ItemType const *buffer, int32_t count)
			{
				_buffer = buffer;
				_count = count;
				Reset();
			}

			/// @brief 获取当前值的引用
			/// @return
			ItemType const &CurrentValue() override
			{
				return _buffer[_index];
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

				if (_index < 0 || _index >= _count)
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
		/// @brief 构造函数。构造出来的对象不会引用任何有效内存段，且大小为 0.
		ReadOnlyArraySpan() = default;

		/// @brief 构造函数。
		/// @param buffer 要引用的内存段指针。
		/// @param count 要引用的内存段大小。
		ReadOnlyArraySpan(ItemType const *buffer, int32_t count)
		{
			_buffer = buffer;
			_count = count;

			if (_buffer == nullptr)
			{
				_count = 0;
			}
		}

		ReadOnlyArraySpan(base::ArraySpan<ItemType> const &span)
		{
			_buffer = span.Buffer();
			_count = span.Count();

			if (_buffer == nullptr)
			{
				_count = 0;
			}
		}

		/// @brief 拷贝构造函数。
		/// @param span
		ReadOnlyArraySpan(base::ReadOnlyArraySpan<ItemType> const &o)
		{
			*this = o;
		}

		/// @brief 赋值运算符。
		/// @param o
		/// @return
		base::ReadOnlyArraySpan<ItemType> &operator=(base::ReadOnlyArraySpan<ItemType> const &o)
		{
			_buffer = o.Buffer();
			_count = o.Count();

			if (_buffer == nullptr)
			{
				_count = 0;
			}

			return *this;
		}

#pragma endregion

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

		base::ReadOnlyArraySpan<ItemType> Slice(base::Range const &range) const
		{
			if (range.End() > Count())
			{
				throw std::out_of_range{"超出范围，无法切片。"};
			}

			return base::ReadOnlyArraySpan<ItemType>{Buffer() + range.Begin(), range.Size()};
		}

		/// @brief 获取迭代器
		/// @return
		std::shared_ptr<IEnumerator<ItemType const>> GetEnumerator() override
		{
			return std::shared_ptr<IEnumerator<ItemType const>>{
				new Enumerator{Buffer(), Count()},
			};
		}
	};

	/// @brief 数组内存段。
	/// @note 引用一段内存，不会持有这段内存，不管理这段内存的生命周期。
	/// @tparam ItemType
	template <typename ItemType>
	class ArraySpan :
		public base::IEnumerable<ItemType>
	{
	private:
		ItemType *_buffer = nullptr;
		int32_t _count = 0;

#pragma region 迭代器

		class Enumerator :
			public base::IEnumerator<ItemType>
		{
		private:
			int _index = 0;
			bool _first_move = true;
			ItemType *_buffer{};
			int32_t _count = 0;

		public:
			Enumerator(ItemType *buffer, int32_t count)
			{
				_buffer = buffer;
				_count = count;
				Reset();
			}

			/// @brief 获取当前值的引用
			/// @return
			ItemType &CurrentValue() override
			{
				return _buffer[_index];
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

				if (_index < 0 || _index >= _count)
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
		/// @brief 构造函数。构造出来的对象不会引用任何有效内存段，且大小为 0.
		ArraySpan() = default;

		/// @brief 构造函数。
		/// @param buffer 要引用的内存段指针。
		/// @param count 要引用的内存段大小。
		ArraySpan(ItemType *buffer, int32_t count)
		{
			_buffer = buffer;
			_count = count;

			if (_buffer == nullptr)
			{
				_count = 0;
			}
		}

		/// @brief 拷贝构造函数。
		/// @param span
		ArraySpan(base::ArraySpan<ItemType> const &o)
		{
			*this = o;
		}

		/// @brief 赋值运算符。
		/// @param o
		/// @return
		base::ArraySpan<ItemType> &operator=(base::ArraySpan<ItemType> const &o)
		{
			_buffer = o.Buffer();
			_count = o.Count();

			if (_buffer == nullptr)
			{
				_count = 0;
			}

			return *this;
		}

#pragma endregion

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

#pragma region CopyFrom

		/// @brief 将 another 的内存段的数据复制到本对象的内存段。
		/// @param another
		void CopyFrom(base::ReadOnlyArraySpan<ItemType> const &another) const
		{
			if (another.Count() != Count())
			{
				throw std::invalid_argument{"another 的 Count 属性必须和本对象的 Count 属性相等。"};
			}

			std::copy(another.Buffer(),
					  another.Buffer() + another.Count(),
					  Buffer());
		}

		/// @brief 将 another 的内存段的数据复制到本对象的内存段。
		/// @param another
		void CopyFrom(base::ArraySpan<ItemType> const &another) const
		{
			CopyFrom(base::ReadOnlyArraySpan<ItemType>{another});
		}

#pragma endregion

		base::ArraySpan<ItemType> Slice(base::Range const &range) const
		{
			if (range.End() > Count())
			{
				throw std::out_of_range{"超出范围，无法切片。"};
			}

			return base::ArraySpan<ItemType>{Buffer() + range.Begin(), range.Size()};
		}

		/// @brief 获取迭代器
		/// @return
		std::shared_ptr<IEnumerator<ItemType>> GetEnumerator() override
		{
			return std::shared_ptr<IEnumerator<ItemType>>{
				new Enumerator{Buffer(), Count()},
			};
		}
	};
} // namespace base
