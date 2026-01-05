#pragma once
#include "base/container/iterator/IEnumerable.h"
#include "base/RentedPtrFactory.h"
#include "base/string/define.h"
#include <stdexcept>

namespace base
{
	template <typename ItemType>
	class Enumerable final :
		public base::IEnumerable<ItemType>
	{
	private:
		std::shared_ptr<base::IEnumerator<ItemType>> _enumerator;

	public:
		Enumerable(std::shared_ptr<base::IEnumerator<ItemType>> const &enumerator)
		{
			if (enumerator == nullptr)
			{
				throw std::invalid_argument{CODE_POS_STR + "禁止传入空指针。"};
			}

			_enumerator = enumerator;
		}

		Enumerable(base::IEnumerator<ItemType> &enumerator)
		{
			_enumerator = base::RentedPtrFactory::Create(&enumerator);
		}

		///
		/// @brief 获取非 const 迭代器
		///
		/// @return
		///
		virtual std::shared_ptr<base::IEnumerator<ItemType>> GetEnumerator() override
		{
			return _enumerator;
		}
	};

} // namespace base
