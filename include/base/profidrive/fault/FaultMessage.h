#pragma once
#include "base/profidrive/fault/FaultClass.h"
#include <cstdint>

namespace base::profidrive
{
	class FaultMessage
	{
	private:
		///
		/// @brief 错误代码。
		///
		///
		uint16_t _fault_code{};

		///
		/// @brief 错误号。
		///
		///
		uint16_t _fault_number{};

		///
		/// @brief 错误类别。
		///
		///
		base::profidrive::FaultClass _fault_class{};

		///
		/// @brief 错误文本。
		///
		/// @note 最多只能有 16 个字符，不包括 C 式字符串结尾的 \0 字符。
		///
		char const *_fault_text{};

		///
		/// @brief 故障时间。
		///
		///
		uint32_t _fault_time{};

		///
		/// @brief 故障值。
		///
		///
		uint16_t _fault_value{};

	public:
		constexpr FaultMessage() = default;

		constexpr FaultMessage(uint16_t fault_code,
							   uint16_t fault_number,
							   base::profidrive::FaultClass fault_class,
							   char const *fault_text)
			: _fault_code(fault_code),
			  _fault_number(fault_number),
			  _fault_class(fault_class),
			  _fault_text(fault_text)
		{
		}

		constexpr FaultMessage(uint16_t fault_code,
							   uint16_t fault_number,
							   base::profidrive::FaultClass fault_class,
							   char const *fault_text,
							   uint32_t fault_time,
							   uint16_t fault_value)
			: _fault_code(fault_code),
			  _fault_number(fault_number),
			  _fault_class(fault_class),
			  _fault_text(fault_text),
			  _fault_time(fault_time),
			  _fault_value(fault_value)
		{
		}

		///
		/// @brief 错误代码。
		///
		/// @return
		///
		constexpr uint16_t FaultCode() const
		{
			return _fault_code;
		}

		///
		/// @brief 错误号。
		///
		/// @return
		///
		constexpr uint16_t FaultNumber() const
		{
			return _fault_number;
		}

		///
		/// @brief 错误类。
		///
		/// @return
		///
		constexpr base::profidrive::FaultClass FaultClass() const
		{
			return _fault_class;
		}

		///
		/// @brief 错误文本。
		///
		/// @return
		///
		constexpr char const *FaultText() const
		{
			return _fault_text;
		}

		///
		/// @brief 错误时间。
		///
		/// @return
		///
		constexpr uint32_t FaultTime() const
		{
			return _fault_time;
		}

		///
		/// @brief 设置错误时间。
		///
		/// @param value
		///
		constexpr void SetFaultTime(uint32_t value)
		{
			_fault_time = value;
		}

		///
		/// @brief 错误值。
		///
		/// @return
		///
		constexpr uint16_t FaultValue() const
		{
			return _fault_value;
		}

		///
		/// @brief 设置错误值。
		///
		/// @param value
		///
		constexpr void SetFaultValue(uint16_t value)
		{
			_fault_value = value;
		}
	};

} // namespace base::profidrive
