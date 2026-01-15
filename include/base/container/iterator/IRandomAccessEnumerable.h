#pragma once
#include "base/container/iterator/IEnumerable.h"
#include "base/container/iterator/IRandomAccessEnumerator.h"

namespace base
{
	template <typename ItemType>
	class IRandomAccessEnumerable :
		public base::IEnumerable<ItemType>
	{
	private:
		/* #region const 迭代器 */

		///
		/// @brief const 迭代器
		///
		class ConstEnumerator final :
			public base::IRandomAccessEnumerator<ItemType const>
		{
		private:
			std::shared_ptr<base::IRandomAccessEnumerator<ItemType>> _enumerator;
			base::IEnumerator<ItemType const>::Context_t _context{};

		public:
			ConstEnumerator(std::shared_ptr<base::IRandomAccessEnumerator<ItemType>> const &enumerator)
			{
				_enumerator = enumerator;
			}

			ConstEnumerator(ConstEnumerator const &other)
			{
				*this = other;
			}

			ConstEnumerator &operator=(ConstEnumerator const &other)
			{
				_enumerator = other._enumerator->Clone();
				return *this;
			}

			///
			/// @brief 克隆一个迭代器对象副本。
			///
			/// @note 派生类要实现拷贝构造函数后在这里调用自己的拷贝构造函数拷贝一份自己。
			///
			/// @return
			///
			virtual std::shared_ptr<base::IRandomAccessEnumerator<ItemType const>> Clone() const override
			{
				std::shared_ptr<base::IRandomAccessEnumerator<ItemType const>> ret{new ConstEnumerator{*this}};
				return ret;
			}

			///
			/// @brief 容器中总共有多少个元素。
			///
			/// @return
			///
			virtual int64_t Count() const override
			{
				return _enumerator->Count();
			}

			///
			/// @brief 当前迭代到的位置。
			///
			/// @return
			///
			virtual int64_t Position() const override
			{
				return _enumerator->Position();
			}

			///
			/// @brief 将迭代器位置增加 value.
			///
			/// @param value 增加的值。可以是正数和负数。
			///
			virtual void Add(int64_t value) override
			{
				_enumerator->Add(value);
			}

			///
			/// @brief 获取当前值的引用。
			///
			/// @note 迭代器构造后，如果被迭代的集合不为空，要立即让 CurrentValue 指向第一个有效元素。
			///
			/// @return
			///
			virtual ItemType const &CurrentValue() override
			{
				return _enumerator->CurrentValue();
			}

			///
			/// @brief 派生类需要提供一个该对象。
			///
			/// @return
			///
			virtual base::IEnumerator<ItemType const>::Context_t &Context() override
			{
				return _context;
			}

		}; // class ConstEnumerator

		/* #endregion */

	public:
		/* #region Iterator */

		///
		/// @brief 包装 IEnumerator 对象，并提供 C++ 迭代器的方法。这样就能在 begin, end
		/// 方法中返回本类对象，让 IEnumerable 支持 for-in 循环。
		///
		/// @tparam item_type
		///
		template <typename item_type>
		class Iterator
		{
		public:
			using iterator_category = std::random_access_iterator_tag;
			using value_type = ItemType const;
			using difference_type = int64_t;
			using pointer = ItemType const *;
			using reference = ItemType const &;

		private:
			std::shared_ptr<base::IRandomAccessEnumerator<item_type>> _enumerator;

		public:
			Iterator() = default;

			Iterator(std::shared_ptr<base::IRandomAccessEnumerator<item_type>> const &enumertor)
			{
				_enumerator = enumertor;
			}

			Iterator(Iterator const &other)
			{
				*this = other;
			}

			Iterator &operator=(Iterator const &other)
			{
				if (other._enumerator != nullptr)
				{
					_enumerator = other._enumerator->Clone();
				}
				else
				{
					_enumerator = other._enumerator;
				}

				return *this;
			}

			item_type &operator*()
			{
				return _enumerator->CurrentValue();
			}

			ItemType *operator->()
			{
				return &operator*();
			}

			///
			/// @brief 前缀递增
			///
			/// @return
			///
			Iterator<item_type> &operator++()
			{
				if (_enumerator->IsEnd())
				{
					return *this;
				}

				_enumerator->Add();
				return *this;
			}

			///
			/// @brief 前缀递减。
			///
			/// @return
			///
			Iterator<item_type> &operator--()
			{
				if (_enumerator->IsEnd())
				{
					return *this;
				}

				_enumerator->Subtract();
				return *this;
			}

			Iterator &operator+=(int64_t value)
			{
				_enumerator->Add(value);
				return *this;
			}

			Iterator operator+(int64_t value)
			{
				Iterator copy{*this};
				copy._enumerator->Add(value);
				return copy;
			}

			int64_t operator-(Iterator const &other) const
			{
				if (_enumerator == nullptr && other._enumerator != nullptr)
				{
					// 本对象是 end, other 不是 end.
					// end - other
					return other._enumerator->Count() - other._enumerator->Position();
				}

				if (_enumerator != nullptr && other._enumerator == nullptr)
				{
					// 本对象不是 end, other 是 end.
					// this - end
					return _enumerator->Position() - _enumerator->Count();
				}

				if (_enumerator != nullptr && other._enumerator != nullptr)
				{
					return _enumerator->Position() - other._enumerator->Position();
				}

				if (_enumerator == nullptr && other._enumerator == nullptr)
				{
					return 0;
				}

				return 0;
			}

			bool operator==(Iterator<item_type> const &other) const
			{
				if (_enumerator != nullptr && other._enumerator == nullptr)
				{
					// 本对象不是 end, other 是 end.
					return _enumerator->IsEnd();
				}

				if (_enumerator == nullptr && other._enumerator != nullptr)
				{
					// 本对象是 end, other 不是 end.
					return other._enumerator->IsEnd();
				}

				if (_enumerator != nullptr && other._enumerator != nullptr)
				{
					return _enumerator->Position() == other._enumerator->Position();
				}

				if (_enumerator == nullptr && other._enumerator == nullptr)
				{
					return true;
				}

				return true;
			}

			bool operator!=(Iterator<item_type> const &other) const
			{
				return !(*this == other);
			}
		};

		/* #endregion */

		virtual ~IRandomAccessEnumerable() = default;

		/* #region 接口 */

		///
		/// @brief 获取非 const 迭代器
		///
		/// @return
		///
		virtual std::shared_ptr<base::IRandomAccessEnumerator<ItemType>> GetRandomAccessEnumerator() = 0;

		/* #endregion */

		/* #region 接口扩展 */

		using base::IEnumerable<ItemType>::GetEnumerator;

		///
		/// @brief 获取非 const 迭代器
		///
		/// @return
		///
		virtual std::shared_ptr<base::IEnumerator<ItemType>> GetEnumerator() override final
		{
			return GetRandomAccessEnumerator();
		}

		///
		/// @brief 获取 const 迭代器
		///
		/// @return
		///
		std::shared_ptr<base::IRandomAccessEnumerator<ItemType const>> GetRandomAccessEnumerator() const
		{
			return std::shared_ptr<IRandomAccessEnumerator<ItemType const>>{new ConstEnumerator{
				const_cast<base::IRandomAccessEnumerable<ItemType> *>(this)->GetRandomAccessEnumerator(),
			}};
		}

		Iterator<ItemType> begin()
		{
			return Iterator<ItemType>{GetRandomAccessEnumerator()};
		}

		Iterator<ItemType> end()
		{
			return Iterator<ItemType>{};
		}

		Iterator<ItemType const> begin() const
		{
			return Iterator<ItemType const>{GetRandomAccessEnumerator()};
		}

		Iterator<ItemType const> end() const
		{
			return Iterator<ItemType const>{};
		}

		/* #endregion */

	}; // class IRandomAccessEnumerable

} // namespace base
