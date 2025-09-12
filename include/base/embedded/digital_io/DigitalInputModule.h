#pragma once
#include "base/embedded/Slot.h"
#include "digital_input_module_handle.h"
#include <cstdint>
#include <memory>

namespace base
{
	namespace digital_input_module
	{
		class DigitalInputModule
		{
		private:
			std::shared_ptr<base::digital_input_module::digital_input_module_handle> _handle;

		public:
			/* #region 构造函数 */

			DigitalInputModule(std::string const &name)
			{
				_handle = base::digital_input_module::open(name);
			}

			DigitalInputModule(uint32_t id)
			{
				_handle = base::digital_input_module::open(id);
			}

			/* #endregion */

			int32_t GroupCount() const
			{
				return base::digital_input_module::group_count(*_handle);
			}

			int32_t BitCountPerGroup() const
			{
				return base::digital_input_module::bit_count_per_group(*_handle);
			}

			bool ReadBit(int32_t group_index, int32_t bit_index) const
			{
				return base::digital_input_module::read_bit(*_handle, group_index, bit_index);
			}

			uint64_t ReadGroup(int32_t group_index) const
			{
				return base::digital_input_module::read_group(*_handle, group_index);
			}
		};

		///
		/// @brief 数字输入模块插槽。
		///
		///
		base::Slot<base::digital_input_module::DigitalInputModule> &digital_input_module_slot();

	} // namespace digital_input_module
} // namespace base
