#pragma once
#include "base/string/define.h"
#include <cstdint>
#include <memory>
#include <stdexcept>

namespace base
{
	template <typename ItemType>
	class IRandomAccessIterator
	{
	public:
		virtual ~IRandomAccessIterator() = default;

		///
		/// @brief 派生类利用拷贝构造函数拷贝一个自己，然后返回。
		///
		/// @return
		///
		virtual std::shared_ptr<IRandomAccessIterator> Clone() = 0;

		///
		/// @brief 返回当前迭代器指向的对象的引用。
		///
		/// @return
		///
		virtual ItemType &Current() = 0;

		virtual void Increment() = 0;

		virtual void Decrement() = 0;

		virtual void Add(int64_t value) = 0;

		virtual int64_t Subtract(IRandomAccessIterator const &other) const = 0;

		virtual bool Equal(IRandomAccessIterator const &other) const = 0;
	};

	///
	/// @brief 先派生 IRandomAccessIterator 类，然后就可以用本类包装 IRandomAccessIterator
	/// 派生类对象，并在 being 和 end 中返回本类对象。
	///
	template <typename ItemType>
	class RandomAccessIterator final
	{
	public:
		using iterator_category = std::random_access_iterator_tag;
		using value_type = ItemType;
		using difference_type = int64_t;
		using pointer = ItemType *;
		using reference = ItemType &;

	private:
		std::shared_ptr<IRandomAccessIterator<ItemType>> _iterator{};

	public:
		RandomAccessIterator() = default;

		RandomAccessIterator(std::shared_ptr<IRandomAccessIterator<ItemType>> const &iterator)
			: _iterator{iterator}
		{
		}

		RandomAccessIterator(RandomAccessIterator const &other)
		{
			*this = other;
		}

		RandomAccessIterator &operator=(RandomAccessIterator const &other)
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
		RandomAccessIterator &operator++()
		{
			_iterator->Increment();
			return *this;
		}

		///
		/// @brief 后缀递增。
		///
		RandomAccessIterator operator++(int)
		{
			RandomAccessIterator copy{*this};
			_iterator->Increment();
			return copy;
		}

		///
		/// @brief 前缀递减。
		///
		/// @return
		///
		RandomAccessIterator &operator--()
		{
			_iterator->Decrement();
			return *this;
		}

		///
		/// @brief 后缀递减。
		///
		/// @return
		///
		RandomAccessIterator operator--(int)
		{
			RandomAccessIterator copy{*this};
			_iterator->Decrement();
			return copy;
		}

		RandomAccessIterator &operator+=(int64_t value)
		{
			_iterator->Add(value);
			return *this;
		}

		RandomAccessIterator operator+(int64_t value) const
		{
			// 基于 Iterator &operator+=(int64_t value) 实现。
			RandomAccessIterator copy{*this};
			copy += value;
			return copy;
		}

		difference_type operator-(RandomAccessIterator const &other) const
		{
			return _iterator->Subtract(*other._iterator);
		}

		bool operator==(RandomAccessIterator const &other) const
		{
			return _iterator->Equal(*other._iterator);
		}

		bool operator!=(RandomAccessIterator const &other) const
		{
			return !(*this == other);
		}
	};

	///
	/// @brief 先派生 IRandomAccessIterator 类，然后就可以用本类包装 IRandomAccessIterator
	/// 派生类对象，并在 being 和 end 中返回本类对象。
	///
	template <typename ItemType>
	class ConstRandomAccessIterator final
	{
	public:
		using iterator_category = std::random_access_iterator_tag;
		using value_type = ItemType;
		using difference_type = int64_t;
		using pointer = ItemType const *;
		using reference = ItemType const &;

	private:
		std::shared_ptr<IRandomAccessIterator<ItemType>> _iterator{};

	public:
		ConstRandomAccessIterator() = default;

		ConstRandomAccessIterator(std::shared_ptr<IRandomAccessIterator<ItemType>> const &iterator)
			: _iterator{iterator}
		{
		}

		ConstRandomAccessIterator(ConstRandomAccessIterator const &other)
		{
			*this = other;
		}

		ConstRandomAccessIterator &operator=(ConstRandomAccessIterator const &other)
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
		ConstRandomAccessIterator &operator++()
		{
			_iterator->Increment();
			return *this;
		}

		///
		/// @brief 后缀递增。
		///
		ConstRandomAccessIterator operator++(int)
		{
			ConstRandomAccessIterator copy{*this};
			_iterator->Increment();
			return copy;
		}

		///
		/// @brief 前缀递减。
		///
		/// @return
		///
		ConstRandomAccessIterator &operator--()
		{
			_iterator->Decrement();
			return *this;
		}

		///
		/// @brief 后缀递减。
		///
		/// @return
		///
		ConstRandomAccessIterator operator--(int)
		{
			ConstRandomAccessIterator copy{*this};
			_iterator->Decrement();
			return copy;
		}

		ConstRandomAccessIterator &operator+=(int64_t value)
		{
			_iterator->Add(value);
			return *this;
		}

		ConstRandomAccessIterator operator+(int64_t value) const
		{
			// 基于 Iterator &operator+=(int64_t value) 实现。
			ConstRandomAccessIterator copy{*this};
			copy += value;
			return copy;
		}

		difference_type operator-(ConstRandomAccessIterator const &other) const
		{
			return _iterator->Subtract(*other._iterator);
		}

		bool operator==(ConstRandomAccessIterator const &other) const
		{
			return _iterator->Equal(*other._iterator);
		}

		bool operator!=(ConstRandomAccessIterator const &other) const
		{
			return !(*this == other);
		}
	};

} // namespace base
