#pragma once
#include "base/string/define.h"
#include <memory>
#include <stdexcept>

namespace base
{
	template <typename ItemType>
	class IInputIterator
	{
	public:
		virtual ~IInputIterator() = default;

		///
		/// @brief 派生类利用拷贝构造函数拷贝一个自己，然后返回。
		///
		/// @return
		///
		virtual std::shared_ptr<IInputIterator> Clone() = 0;

		///
		/// @brief 返回当前迭代器指向的对象的引用。
		///
		/// @return
		///
		virtual ItemType &Current() = 0;

		virtual void Increment() = 0;

		virtual bool Equal(IInputIterator const &other) const = 0;
	};

	///
	/// @brief 先派生 IInputIterator 类，然后就可以用本类包装 IInputIterator
	/// 派生类对象，并在 being 和 end 中返回本类对象。
	///
	template <typename ItemType>
	class InputIterator final
	{
	public:
		using iterator_category = std::input_iterator_tag;
		using value_type = ItemType;
		using pointer = ItemType *;
		using reference = ItemType &;

	private:
		std::shared_ptr<IInputIterator<ItemType>> _iterator{};

	public:
		InputIterator() = default;

		InputIterator(std::shared_ptr<IInputIterator<ItemType>> const &iterator)
			: _iterator{iterator}
		{
		}

		InputIterator(InputIterator const &other)
		{
			*this = other;
		}

		InputIterator &operator=(InputIterator const &other)
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
		InputIterator &operator++()
		{
			_iterator->Increment();
			return *this;
		}

		///
		/// @brief 后缀递增。
		///
		InputIterator operator++(int)
		{
			InputIterator copy{*this};
			_iterator->Increment();
			return copy;
		}

		bool operator==(InputIterator const &other) const
		{
			return _iterator->Equal(*other._iterator);
		}

		bool operator!=(InputIterator const &other) const
		{
			return !(*this == other);
		}
	};

	///
	/// @brief 先派生 IInputIterator 类，然后就可以用本类包装 IInputIterator
	/// 派生类对象，并在 being 和 end 中返回本类对象。
	///
	template <typename ItemType>
	class ConstInputIterator final
	{
	public:
		using iterator_category = std::input_iterator_tag;
		using value_type = ItemType;
		using pointer = ItemType const *;
		using reference = ItemType const &;

	private:
		std::shared_ptr<IInputIterator<ItemType>> _iterator{};

	public:
		ConstInputIterator() = default;

		ConstInputIterator(std::shared_ptr<IInputIterator<ItemType>> const &iterator)
			: _iterator{iterator}
		{
		}

		ConstInputIterator(ConstInputIterator const &other)
		{
			*this = other;
		}

		ConstInputIterator &operator=(ConstInputIterator const &other)
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
		ConstInputIterator &operator++()
		{
			_iterator->Increment();
			return *this;
		}

		///
		/// @brief 后缀递增。
		///
		ConstInputIterator operator++(int)
		{
			ConstInputIterator copy{*this};
			_iterator->Increment();
			return copy;
		}

		bool operator==(ConstInputIterator const &other) const
		{
			return _iterator->Equal(*other._iterator);
		}

		bool operator!=(ConstInputIterator const &other) const
		{
			return !(*this == other);
		}
	};

} // namespace base
