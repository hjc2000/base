#pragma once
#include <base/container/iterator/IEnumerator.h>
#include <base/container/iterator/IForwardIterator.h>
#include <memory>

namespace base
{
	/**
	 * @brief C# 风格的可迭代容器接口。
	 *
	 * @tparam ItemType
	 */
	template <typename ItemType>
	class IEnumerable
	{
	private:
		/// @brief const 迭代器
		/// @tparam item_type
		template <typename item_type>
		class ConstEnumerator :
			public IEnumerator<item_type const>
		{
		private:
			std::shared_ptr<IEnumerator<item_type>> _enumerator;

		public:
			ConstEnumerator(std::shared_ptr<IEnumerator<item_type>> enumerator)
			{
				_enumerator = enumerator;
			}

			item_type const &CurrentValue() override
			{
				return _enumerator->CurrentValue();
			}

			virtual bool MoveNext() override
			{
				return _enumerator->MoveNext();
			}

			virtual void Reset() override
			{
				_enumerator->Reset();
			}
		};

	public:
		/// @brief 将 IEnumerator 包装为 C++ 迭代器
		/// @tparam item_type
		template <typename item_type>
		class ForwardIterator :
			public base::IForwardIterator<ForwardIterator<item_type>, item_type>
		{
		private:
			std::shared_ptr<IEnumerator<item_type>> _enumertor;

		public:
			/// @brief 将 IEnumerator 包装为 C++ 迭代器
			/// @param enumertor
			ForwardIterator(std::shared_ptr<IEnumerator<item_type>> enumertor)
			{
				_enumertor = enumertor;
			}

			/// @brief 解引用
			/// @return
			item_type &operator*() override
			{
				return _enumertor->CurrentValue();
			}

			/// @brief 前缀递增
			/// @return
			ForwardIterator<item_type> &operator++() override
			{
				// 不做任何操作，因为 == 运算符里面已经 MoveNext 了。
				return *this;
			}

			/// @brief 相等运算符
			/// @param o
			/// @return
			bool operator==(ForwardIterator<item_type> const &o) const override
			{
				/* C++ 范围 for 的机制是先判断不等于 end() 然后解引用。然后递增，进入下一循环。
				 * IEnumerator 的操作顺序是先 MoveNext 然后判断是否成功，成功再利用 CurrentValue
				 * 获取引用。
				 *
				 * 让 == 运算符返回 !_enumertor->MoveNext()，这样，范围 for 的判断不等于 end() 的
				 * 步骤就会触发移动，并得到是否移动成功的结果，移动失败，就返回 true ，让范围 for 认为
				 * 当前等于 end() ，于是结束迭代。
				 */
				return !_enumertor->MoveNext();
			}
		};

	public:
		/**
		 * @brief 获取非 const 迭代器
		 *
		 * @return std::shared_ptr<base::IEnumerator<ItemType>>
		 */
		virtual std::shared_ptr<base::IEnumerator<ItemType>> GetEnumerator() = 0;

	public:
		/**
		 * @brief 获取 const 迭代器
		 *
		 * @return std::shared_ptr<base::IEnumerator<ItemType const>>
		 */
		std::shared_ptr<base::IEnumerator<ItemType const>> GetEnumerator() const
		{
			return std::shared_ptr<IEnumerator<ItemType const>>{new ConstEnumerator<ItemType>{
				const_cast<IEnumerable *>(this)->GetEnumerator(),
			}};
		}

		ForwardIterator<ItemType> begin()
		{
			return ForwardIterator<ItemType>{GetEnumerator()};
		}

		ForwardIterator<ItemType> end()
		{
			return ForwardIterator<ItemType>{GetEnumerator()};
		}

		ForwardIterator<ItemType const> begin() const
		{
			return ForwardIterator<ItemType const>{GetEnumerator()};
		}

		ForwardIterator<ItemType const> end() const
		{
			return ForwardIterator<ItemType const>{GetEnumerator()};
		}
	};
} // namespace base
