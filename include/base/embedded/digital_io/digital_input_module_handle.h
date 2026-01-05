#pragma once
#include <cstdint>
#include <memory>
#include <string>

namespace base
{
	namespace digital_input_module
	{
		class digital_input_module_handle;

		/* #region open */

		///
		/// @brief 根据名称打开数字输入模块。
		///
		/// @param name
		/// @return
		///
		std::shared_ptr<base::digital_input_module::digital_input_module_handle> open(std::string const &name);

		///
		/// @brief 根据 ID 打开数字输入模块。
		///
		/// @param id
		/// @return
		///
		std::shared_ptr<base::digital_input_module::digital_input_module_handle> open(uint32_t id);

		/* #endregion */

		///
		/// @brief 数字输入模块的输入点组数。
		///
		/// @param h
		/// @return
		///
		int32_t group_count(digital_input_module_handle &h);

		///
		/// @brief 每一组有多少个输入点。
		///
		/// @param h
		/// @return
		///
		int32_t bit_count_per_group(digital_input_module_handle &h);

		///
		/// @brief 读单个位。
		///
		/// @param h
		/// @param group_index
		/// @param bit_index
		/// @return
		///
		bool read_bit(digital_input_module_handle &h, uint32_t group_index, uint32_t bit_index);

		///
		/// @brief 读一整个组的位。
		///
		/// @param h
		/// @param group_index
		/// @return
		///
		uint64_t read_group(digital_input_module_handle &h, uint32_t group_index);

	} // namespace digital_input_module
} // namespace base
