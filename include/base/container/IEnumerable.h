#pragma once
#include <base/container/IEnumerator.h>
#include <base/container/IEnumeratorForwardIterator.h>
#include <base/container/IIterator.h>
#include <memory>

namespace base
{
	/// @brief 可迭代容器接口。
	/// @tparam ItemType
	template <typename ItemType>
	class IEnumerable
	{
	public:
		virtual std::shared_ptr<IEnumerator<ItemType>> GetEnumerator() = 0;
		virtual std::shared_ptr<IEnumerator<ItemType const>> GetEnumerator() const = 0;

		IEnumeratorForwardIterator<ItemType> begin()
		{
			return IEnumeratorForwardIterator<ItemType>{GetEnumerator()};
		}

		IEnumeratorForwardIterator<ItemType> end()
		{
			return IEnumeratorForwardIterator<ItemType>{GetEnumerator()};
		}

		IEnumeratorForwardIterator<ItemType const> begin() const
		{
			return IEnumeratorForwardIterator<ItemType const>{GetEnumerator()};
		}

		IEnumeratorForwardIterator<ItemType const> end() const
		{
			return IEnumeratorForwardIterator<ItemType const>{GetEnumerator()};
		}
	};
}
