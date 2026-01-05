#pragma once
#include "base/embedded/Slot.h"
#include "digital_output_module_handle.h"
#include <cstdint>
#include <memory>

namespace base
{
	namespace digital_output_module
	{
		class DigitalOutputModule
		{
		private:
			std::shared_ptr<base::digital_output_module::digital_output_module_handle> _handle;

		public:
			/* #region 构造函数 */

			DigitalOutputModule(std::string const &name)
			{
				_handle = base::digital_output_module::open(name);
			}

			DigitalOutputModule(uint32_t id)
			{
				_handle = base::digital_output_module::open(id);
			}

			/* #endregion */

			int32_t GroupCount() const
			{
				return base::digital_output_module::group_count(*_handle);
			}

			int32_t BitCountPerGroup() const
			{
				return base::digital_output_module::bit_count_per_group(*_handle);
			}

			/* #region 读写单个位 */

			bool ReadBit(int32_t group_index, int32_t bit_index) const
			{
				return base::digital_output_module::read_bit(*_handle, group_index, bit_index);
			}

			void WriteBit(int32_t group_index, int32_t bit_index, bool value)
			{
				base::digital_output_module::write_bit(*_handle, group_index, bit_index, value);
			}

			void ToggleBit(int32_t group_index, int32_t bit_index)
			{
				base::digital_output_module::toggle_bit(*_handle, group_index, bit_index);
			}

			/* #endregion */

			/* #region 读写一整个组 */

			uint64_t ReadGroup(int32_t group_index) const
			{
				return base::digital_output_module::read_group(*_handle, group_index);
			}

			void WriteGroup(int32_t group_index, uint64_t value)
			{
				base::digital_output_module::write_group(*_handle, group_index, value);
			}

			/* #endregion */
		};

		///
		/// @brief 数字输出模块插槽。
		///
		///
		base::Slot<base::digital_output_module::DigitalOutputModule> &digital_output_module_slot();

	} // namespace digital_output_module
} // namespace base
