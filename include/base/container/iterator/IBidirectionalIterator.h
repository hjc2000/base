#pragma once
#include "base/string/define.h"
#include <memory>
#include <stdexcept>

namespace base
{
	template <typename ItemType>
	class IBidirectionalIterator
	{
	public:
		virtual ~IBidirectionalIterator() = default;

		///
		/// @brief 派生类利用拷贝构造函数拷贝一个自己，然后返回。
		///
		/// @return
		///
		virtual std::shared_ptr<IBidirectionalIterator> Clone() = 0;

		///
		/// @brief 返回当前迭代器指向的对象的引用。
		///
		/// @return
		///
		virtual ItemType &Current() = 0;

		virtual void Increment() = 0;

		virtual void Decrement() = 0;

		virtual bool Equal(IBidirectionalIterator const &other) const = 0;
	};

	///
	/// @brief 先派生 IBidirectionalIterator 类，然后就可以用本类包装 IBidirectionalIterator
	/// 派生类对象，并在 being 和 end 中返回本类对象。
	///
	template <typename ItemType>
	class BidirectionalIterator final
	{
	public:
		using iterator_category = std::bidirectional_iterator_tag;
		using value_type = ItemType;
		using pointer = ItemType *;
		using reference = ItemType &;

	private:
		std::shared_ptr<IBidirectionalIterator<ItemType>> _iterator{};

	public:
		BidirectionalIterator() = default;

		BidirectionalIterator(std::shared_ptr<IBidirectionalIterator<ItemType>> const &iterator)
			: _iterator{iterator}
		{
		}

		BidirectionalIterator(BidirectionalIterator const &other)
		{
			*this = other;
		}

		BidirectionalIterator &operator=(BidirectionalIterator const &other)
		{
			_iterator = other._iterator->Clone();
			return *this;
		}

		reference operator*()
		{
			if (_iterator == nullptr)
			{
				throw std::invalid_argument{CODE_POS_STR + "迭代器处于无效状态。"};
			}

			return _iterator->Current();
		}

		pointer operator->()
		{
			return &_iterator->Current();
		}

		///
		/// @brief 前缀递增
		///
		/// @return
		///
		BidirectionalIterator &operator++()
		{
			_iterator->Increment();
			return *this;
		}

		///
		/// @brief 后缀递增。
		///
		BidirectionalIterator operator++(int)
		{
			BidirectionalIterator copy{*this};
			_iterator->Increment();
			return copy;
		}

		///
		/// @brief 前缀递减。
		///
		/// @return
		///
		BidirectionalIterator &operator--()
		{
			_iterator->Decrement();
			return *this;
		}

		///
		/// @brief 后缀递减。
		///
		/// @return
		///
		BidirectionalIterator operator--(int)
		{
			BidirectionalIterator copy{*this};
			_iterator->Decrement();
			return copy;
		}

		bool operator==(BidirectionalIterator const &other) const
		{
			return _iterator->Equal(*other._iterator);
		}

		bool operator!=(BidirectionalIterator const &other) const
		{
			return !(*this == other);
		}
	};

	///
	/// @brief 先派生 IBidirectionalIterator 类，然后就可以用本类包装 IBidirectionalIterator
	/// 派生类对象，并在 being 和 end 中返回本类对象。
	///
	template <typename ItemType>
	class ConstBidirectionalIterator final
	{
	public:
		using iterator_category = std::bidirectional_iterator_tag;
		using value_type = ItemType;
		using pointer = ItemType const *;
		using reference = ItemType const &;

	private:
		std::shared_ptr<IBidirectionalIterator<ItemType>> _iterator{};

	public:
		ConstBidirectionalIterator() = default;

		ConstBidirectionalIterator(std::shared_ptr<IBidirectionalIterator<ItemType>> const &iterator)
			: _iterator{iterator}
		{
		}

		ConstBidirectionalIterator(ConstBidirectionalIterator const &other)
		{
			*this = other;
		}

		ConstBidirectionalIterator &operator=(ConstBidirectionalIterator const &other)
		{
			_iterator = other._iterator->Clone();
			return *this;
		}

		reference operator*()
		{
			if (_iterator == nullptr)
			{
				throw std::invalid_argument{CODE_POS_STR + "迭代器处于无效状态。"};
			}

			return _iterator->Current();
		}

		pointer operator->()
		{
			return &_iterator->Current();
		}

		///
		/// @brief 前缀递增
		///
		/// @return
		///
		ConstBidirectionalIterator &operator++()
		{
			_iterator->Increment();
			return *this;
		}

		///
		/// @brief 后缀递增。
		///
		ConstBidirectionalIterator operator++(int)
		{
			ConstBidirectionalIterator copy{*this};
			_iterator->Increment();
			return copy;
		}

		///
		/// @brief 前缀递减。
		///
		/// @return
		///
		ConstBidirectionalIterator &operator--()
		{
			_iterator->Decrement();
			return *this;
		}

		///
		/// @brief 后缀递减。
		///
		/// @return
		///
		ConstBidirectionalIterator operator--(int)
		{
			ConstBidirectionalIterator copy{*this};
			_iterator->Decrement();
			return copy;
		}

		bool operator==(ConstBidirectionalIterator const &other) const
		{
			return _iterator->Equal(*other._iterator);
		}

		bool operator!=(ConstBidirectionalIterator const &other) const
		{
			return !(*this == other);
		}
	};

} // namespace base
