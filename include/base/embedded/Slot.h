#pragma once
#include "base/define.h"
#include "base/string/define.h"
#include <cstdint>
#include <memory>
#include <stdexcept>
#include <vector>

namespace base
{
	///
	/// @brief 设备插槽类。
	///
	/// @note 初始化阶段初始化设备后插入插槽，后续不要修改了。
	///
	/// @note 插槽不是线程安全的，只允许一个初始化线程将设备插入插槽，并且操作过程中不允许
	/// 其他线程读写。没错，读也不行。
	///
	template <typename T>
	class Slot
	{
	private:
		DELETE_COPY_AND_MOVE(Slot);

		std::vector<std::shared_ptr<T>> _vector;

	public:
		Slot() = default;

		///
		/// @brief 插槽中的设备数量。
		///
		/// @return
		///
		int32_t Count() const
		{
			return static_cast<int32_t>(_vector.size());
		}

		///
		/// @brief 添加一个设备到插槽中。
		///
		/// @param item
		///
		void Add(std::shared_ptr<T> const &item)
		{
			_vector.push_back(item);
		}

		///
		/// @brief 获取插槽中指定索引的设备。
		///
		/// @param index
		/// @return
		///
		std::shared_ptr<T> const &operator[](int32_t index) const
		{
			if (index < 0 || index > static_cast<int32_t>(_vector.size()))
			{
				throw std::out_of_range{CODE_POS_STR + "索引溢出。"};
			}

			return _vector[index];
		}
	};

} // namespace base
