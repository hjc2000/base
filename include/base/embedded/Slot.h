#pragma once
#include "base/string/define.h"
#include <cstdint>
#include <memory>
#include <stdexcept>
#include <vector>

namespace base
{
	template <typename T>
	class Slot
	{
	private:
		std::vector<std::shared_ptr<void>> _vector;

	public:
		void Add(std::shared_ptr<T> const &item)
		{
			_vector.push_back(item);
		}

		std::shared_ptr<T> operator[](int32_t index) const
		{
			if (index < 0 || index > static_cast<int32_t>(_vector.size()))
			{
				throw std::out_of_range{CODE_POS_STR + "索引溢出。"};
			}

			return std::static_pointer_cast<T>(_vector[index]);
		}
	};
} // namespace base
