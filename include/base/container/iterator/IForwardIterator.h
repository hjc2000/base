#pragma once
#include "base/string/define.h"
#include <memory>
#include <stdexcept>
#include <type_traits>

namespace base
{
	template <typename ItemType>
	class IForwardIterator
	{
	public:
		///
		/// @brief 派生类利用拷贝构造函数拷贝一个自己，然后返回。
		///
		/// @return
		///
		virtual std::shared_ptr<IForwardIterator> Clone() = 0;

		///
		/// @brief 返回当前迭代器指向的对象的引用。
		///
		/// @return
		///
		virtual ItemType &Current() = 0;

		virtual void Increment() = 0;

		virtual bool Equal(IForwardIterator const &other) const = 0;
	};

	///
	/// @brief 先派生 IForwardIterator 类，然后就可以用本类包装 IForwardIterator
	/// 派生类对象，并在 being 和 end 中返回本类对象。
	///
	template <typename ItemType>
	class ForwardIterator final
	{
	public:
		using iterator_category = std::forward_iterator_tag;
		using value_type = ItemType;
		using pointer = ItemType *;
		using reference = ItemType &;

	private:
		std::shared_ptr<IForwardIterator<std::remove_const_t<ItemType>>> _iterator{};

	public:
		ForwardIterator() = default;

		ForwardIterator(std::shared_ptr<IForwardIterator<std::remove_const_t<ItemType>>> const &iterator)
			: _iterator{iterator}
		{
		}

		ForwardIterator(ForwardIterator const &other)
		{
			*this = other;
		}

		ForwardIterator &operator=(ForwardIterator const &other)
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
		ForwardIterator &operator++()
		{
			_iterator->Increment();
			return *this;
		}

		///
		/// @brief 后缀递增。
		///
		ForwardIterator operator++(int)
		{
			ForwardIterator copy{*this};
			_iterator->Increment();
			return copy;
		}

		bool operator==(ForwardIterator const &other) const
		{
			return _iterator->Equal(*other._iterator);
		}

		bool operator!=(ForwardIterator const &other) const
		{
			return !(*this == other);
		}
	};

} // namespace base
