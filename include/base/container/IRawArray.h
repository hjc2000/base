#pragma once
#include <base/container/ArraySpan.h>
#include <base/container/iterator/IEnumerable.h>
#include <base/string/define.h>

namespace base
{
	/// @brief 只要底层的储存方式是 C 风格的裸数组的容器，都可以继承本接口。
	/// @tparam ItemType
	template <typename ItemType>
	class IRawArray :
		public virtual base::IEnumerable<ItemType>
	{
	private:
#pragma region 迭代器

		class Enumerator :
			public base::IEnumerator<ItemType>
		{
		private:
			int32_t _index = 0;
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
#pragma region 接口
		/// @brief 数组的大小
		/// @return
		virtual int32_t Count() const = 0;

		/// @brief 获取底层的缓冲区
		/// @return
		virtual ItemType *Buffer() = 0;

		/// @brief 获取底层的缓冲区
		/// @return
		virtual ItemType const *Buffer() const = 0;
#pragma endregion

		/// @brief 翻转数组
		void Reverse()
		{
			std::reverse(Buffer(), Buffer() + Count());
		}

#pragma region CopyFrom

		/// @brief 将 another 的元素拷贝到本容器。
		/// @note 两个容器的元素个数必须相等，否则会抛出异常。
		/// @param another
		void CopyFrom(base::IRawArray<ItemType> const &another)
		{
			if (Count() != another.Count())
			{
				throw std::invalid_argument{CODE_POS_STR + "another 的元素个数必须和本对象的元素数量一样。"};
			}

			std::copy(another.Buffer(), another.Buffer() + another.Count(), Buffer());
		}

		/// @brief 将 another 的元素拷贝到本容器。
		/// @note 两个容器的元素个数必须相等，否则会抛出异常。
		/// @param another
		void CopyFrom(base::ReadOnlyArraySpan<ItemType> const &another)
		{
			if (Count() != another.Count())
			{
				throw std::invalid_argument{CODE_POS_STR + "another 的元素个数必须和本对象的元素数量一样。"};
			}

			std::copy(another.Buffer(), another.Buffer() + another.Count(), Buffer());
		}

#pragma endregion

		base::ArraySpan<ItemType> AsArraySpan()
		{
			return base::ArraySpan<ItemType>{Buffer(), Count()};
		}

		base::ReadOnlyArraySpan<ItemType> AsReadOnlyArraySpan() const
		{
			return base::ReadOnlyArraySpan<ItemType>{Buffer(), Count()};
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
