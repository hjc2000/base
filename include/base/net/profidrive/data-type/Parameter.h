#pragma once
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
		};
	} // namespace profidrive
} // namespace base
