#pragma once
#include "base/container/iterator/IEnumerator.h"
#include <memory>

namespace base
{
	///
	/// @brief C# 风格的可迭代容器接口。
	///
	/// @tparam ItemType
	///
	template <typename ItemType>
	class IEnumerable
	{
	private:
		/* #region const 迭代器 */

		///
		/// @brief const 迭代器
		///
		class ConstEnumerator final :
			public IEnumerator<ItemType const>
		{
		private:
			std::shared_ptr<IEnumerator<ItemType>> _enumerator;
			base::IEnumerator<ItemType const>::Context_t _context{};

		public:
			ConstEnumerator(std::shared_ptr<IEnumerator<ItemType>> const &enumerator)
			{
				_enumerator = enumerator;
			}

			///
			/// @brief 迭代器当前是否指向尾后元素。
			///
			/// @return
			///
			virtual bool IsEnd() const override
			{
				return _enumerator->IsEnd();
			}

			ItemType const &CurrentValue() override
			{
				return _enumerator->CurrentValue();
			}

			///
			/// @brief 递增迭代器的位置。
			///
			///
			virtual void Add() override
			{
				_enumerator->Add();
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
		};

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
		private:
			std::shared_ptr<IEnumerator<item_type>> _enumerator;
			int64_t _position = 0;

		public:
			Iterator() = default;

			Iterator(std::shared_ptr<IEnumerator<item_type>> const &enumertor)
			{
				_enumerator = enumertor;
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

				_position++;
				_enumerator->Add();
				return *this;
			}

			bool operator==(Iterator<item_type> const &other) const
			{
				if (_enumerator == other._enumerator)
				{
					// 两者指向同一个对象，无论如何都是相等的。
					return true;
				}

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
					// 两个的 _enumerator 指向不同对象，分别独立迭代，则比较 _position 计数
					// 来判断是不是迭代到相同的位置了。
					return _position == other._position;
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

		virtual ~IEnumerable() = default;

		/* #region 接口 */

		///
		/// @brief 获取非 const 迭代器
		///
		/// @return
		///
		virtual std::shared_ptr<base::IEnumerator<ItemType>> GetEnumerator() = 0;

		/* #endregion */

		/* #region 接口扩展 */

		///
		/// @brief 获取 const 迭代器
		///
		/// @return
		///
		std::shared_ptr<base::IEnumerator<ItemType const>> GetEnumerator() const
		{
			auto enumerator = const_cast<base::IEnumerable<ItemType> *>(this)->GetEnumerator();
			return std::shared_ptr<ConstEnumerator>{new ConstEnumerator{enumerator}};
		}

		Iterator<ItemType> begin()
		{
			return Iterator<ItemType>{GetEnumerator()};
		}

		Iterator<ItemType> end()
		{
			return Iterator<ItemType>{};
		}

		Iterator<ItemType const> begin() const
		{
			return Iterator<ItemType const>{GetEnumerator()};
		}

		Iterator<ItemType const> end() const
		{
			return Iterator<ItemType const>{};
		}

		/* #endregion */
	};

} // namespace base
