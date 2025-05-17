#pragma once
#include <cstdint>
#include <memory>
#include <string>

namespace base
{
	namespace digital_output_module
	{
		class digital_output_module_handle;

		/* #region open */

		///
		/// @brief 根据名称打开数字输出模块。
		///
		/// @param name
		/// @return
		///
		std::shared_ptr<base::digital_output_module::digital_output_module_handle> open(std::string const &name);

		///
		/// @brief 根据 ID 打开数字输出模块。
		///
		/// @param id
		/// @return
		///
		std::shared_ptr<base::digital_output_module::digital_output_module_handle> open(uint32_t id);

		/* #endregion */

		///
		/// @brief 数字输出模块的输出点组数。
		///
		/// @param h
		/// @return
		///
		int32_t group_count(digital_output_module_handle &h);

		///
		/// @brief 每一组有多少个输出点。
		///
		/// @param h
		/// @return
		///
		int32_t bit_count_per_group(digital_output_module_handle &h);

		/* #region 读写单个位 */

		///
		/// @brief 读单个位。
		///
		/// @param h
		/// @param group_index
		/// @param bit_index
		/// @return
		///
		bool read_bit(digital_output_module_handle &h, uint32_t group_index, uint32_t bit_index);

		///
		/// @brief 写单个位。
		///
		/// @param h
		/// @param group_index
		/// @param bit_index
		///
		void write_bit(digital_output_module_handle &h, uint32_t group_index, uint32_t bit_index, bool value);

		///
		/// @brief 翻转单个位。
		///
		/// @param h
		/// @param group_index
		/// @param bit_index
		///
		void toggle_bit(digital_output_module_handle &h, uint32_t group_index, uint32_t bit_index);

		/* #endregion */

		/* #region 读写一整个组 */

		///
		/// @brief 读一整个组的位。
		///
		/// @param h
		/// @param group_index
		/// @return
		///
		uint64_t read_group(digital_output_module_handle &h, uint32_t group_index);

		///
		/// @brief 写一整个组的位。
		///
		/// @param h
		/// @param group_index
		/// @param value
		///
		void write_group(digital_output_module_handle &h, uint32_t group_index, uint64_t value);

		/* #endregion */

	} // namespace digital_output_module
} // namespace base
