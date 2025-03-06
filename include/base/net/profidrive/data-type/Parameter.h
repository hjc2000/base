#pragma once
#include <base/net/profidrive/data-type/DataTypeEnum.h>
#include <cstdint>
#include <vector>

namespace base
{
	namespace profidrive
	{
		class Parameter
		{
		private:
			std::vector<uint8_t> _parameter_values_buffer;

		public:
			/**
			 * @brief 参数值缓冲区。
			 *
			 * @note 因为无法确定参数类型，所以使用缓冲区，让应用层自行转换为具体类型。
			 *
			 * @return std::vector<uint8_t>&
			 */
			std::vector<uint8_t> &ParameterValuesBuffer()
			{
				return _parameter_values_buffer;
			}

			/**
			 * @brief 指示参数值的类型。
			 *
			 * @return base::profidrive::DataTypeEnum
			 */
			base::profidrive::DataTypeEnum ValueType() const
			{
				return base::profidrive::DataTypeEnum::Bool;
			}
		};
	} // namespace profidrive
} // namespace base
