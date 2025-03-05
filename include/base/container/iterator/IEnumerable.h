#pragma once
#include <base/container/iterator/IEnumerator.h>
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
		/**
		 * @brief const 迭代器
		 *
		 * @tparam item_type
		 */
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
		/**
		 * @brief 包装 IEnumerator 对象，并提供 C++ 迭代器的方法。这样就能在 begin, end
		 * 方法中返回本类对象，让 IEnumerable 支持 for-in 循环。
		 *
		 * @tparam item_type
		 */
		template <typename item_type>
		class ForwardIterator
		{
		private:
			std::shared_ptr<IEnumerator<item_type>> _enumerator;
			bool _end = false;

		public:
			ForwardIterator(std::shared_ptr<IEnumerator<item_type>> enumertor)
			{
				_enumerator = enumertor;
				_enumerator->Reset();
				_end = !_enumerator->MoveNext();
			}

		public:
			item_type &operator*()
			{
				return _enumerator->CurrentValue();
			}

			ItemType *operator->()
			{
				return &operator*();
			}

		public:
			/**
			 * @brief 前缀递增
			 *
			 * @return ForwardIterator<item_type>&
			 */
			ForwardIterator<item_type> &operator++()
			{
				// 不做任何操作，因为 == 运算符里面已经 MoveNext 了。
				_end = !_enumerator->MoveNext();
				return *this;
			}

			/**
			 * @brief 后缀递增。
			 *
			 * @return ForwardIterator<item_type>&
			 */
			ForwardIterator<item_type> &operator++(int)
			{
				return operator++();
			}

		public:
			bool operator==(ForwardIterator<item_type> const &o) const
			{
				return _end;
			}

			bool operator!=(ForwardIterator<item_type> const &o) const
			{
				return !(*this == o);
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
