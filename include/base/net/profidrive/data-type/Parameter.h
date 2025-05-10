#pragma once
#include "base/net/profidrive/data-type/ParameterDataTypeEnum.h"
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
			///
			/// @brief 参数值缓冲区。
			///
			/// @note 因为无法确定参数类型，所以使用缓冲区，让应用层自行转换为具体类型。
			///
			/// @return std::vector<uint8_t>&
			///
			std::vector<uint8_t> &ParameterValuesBuffer()
			{
				return _parameter_values_buffer;
			}

			/* #region 参数描述 */

			///
			/// @brief 指示参数值的类型。
			///
			/// @note 标识符 bit0 到 bit7.
			///
			/// @return
			///
			base::profidrive::ParameterDataTypeEnum ValueType() const
			{
				return base::profidrive::ParameterDataTypeEnum::Bool;
			}

			///
			/// @brief 标准化系数和变量属性不相关。
			///
			/// @note 标识符 bit8.
			/// @note 如果根据参数无法计算出物理值，则本属性为 true，例如参数是一个字符串时。
			///
			/// @return true
			/// @return false
			///
			bool StandardizationCoefficientAndVariablePropertiesAreNotCorrelated() const
			{
				return false;
			}

			///
			/// @brief 参数不可写。
			///
			/// @note 标识符 bit9.
			///
			/// @return true
			/// @return false
			///
			bool ParametersCannotBeWritten() const
			{
				return false;
			}

			///
			/// @brief 有附加文本数组。
			///
			/// @note 标识符 bit10.
			///
			/// @return true
			/// @return false
			///
			bool HasAdditionalTextArray() const
			{
				return false;
			}

			///
			/// @brief 本参数值与出厂设置不同。
			///
			/// @note 标识符 bit12.
			/// @note 本参数被修改成与出厂设置不同时本属性为 true.
			///
			/// @return true
			/// @return false
			///
			bool DifferentFromTheFactorySetting() const
			{
				return false;
			}

			///
			/// @brief 本参数可被重置。
			///
			/// @note 标识符 bit13.
			///
			/// @return true
			/// @return false
			///
			bool CanBeReset() const
			{
				return true;
			}

			///
			/// @brief 本参数的参数值是一个数组。
			///
			/// @note 标识符 bit14.
			///
			/// @return true
			/// @return false
			///
			bool IsAnArray() const
			{
				return false;
			}

			///
			/// @brief 参数值数组的元素个数或字符串长度。
			///
			/// @note 当参数值是一个数组时，本属性指示元素个数。
			///
			/// @note 当参数值是一个字符串或普通的字节串时，本属性指示字符串长度。
			///
			/// @note 参数值不能是字符串或字节串的数组。因为字符串和字节串的长度是可变的，
			/// 而参数描述没有办法描述这种数组内每一个字符串或字节串的长度。
			///
			/// @return int32_t
			///
			int32_t Length() const
			{
				return 0;
			}

			///
			/// @brief 标准化系数。
			///
			/// @return double
			///
			double StandardizedCoefficient() const
			{
				return 0.0;
			}

			///
			/// @brief 变量索引。
			///
			/// @return uint8_t
			///
			uint8_t VariableIndex() const
			{
				return 0;
			}

			///
			/// @brief 转换索引。
			///
			/// @return int8_t
			///
			int8_t ConvertionIndex() const
			{
				return 0;
			}

			/* #endregion */
		};
	} // namespace profidrive
} // namespace base
