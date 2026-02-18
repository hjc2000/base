#pragma once
#include "base/bit/bit.h"
#include "base/string/define.h"
#include <cstdint>
#include <stdexcept>

namespace base::sdram::chip::w9825g6kh_6
{
	/* #region 模式寄存器参数类 */

	///
	/// @brief 读突发模式。
	///
	///
	enum class ReadingBurstMode
	{
		///
		/// @brief 连续地突发。
		///
		///
		Sequential,

		///
		/// @brief 交错地突发。
		///
		///
		Interleaved,
	};

	///
	/// @brief 写突发模式。
	///
	///
	enum class WritingBurstMode
	{
		///
		/// @brief 编程的突发模式。
		///
		///
		Programmed,

		///
		/// @brief 单点突发模式。即一次写入一个列，实际上就是不突发。
		///
		///
		Single,
	};

	/* #endregion */

	///
	/// @brief w9825g6kh_6 的模式寄存器。
	///
	///
	class ModeRegister
	{
	private:
		uint32_t _value = 0;

	public:
		constexpr uint32_t Value() const
		{
			return _value;
		}

		/* #region 读突发长度 */

		constexpr uint32_t ReadingBurstLength() const
		{
			uint32_t value = base::bit::ReadBits(_value, 0, 3);
			value *= 2;

			if (value == 0)
			{
				value = 1;
			}

			return value;
		}

		///
		/// @brief 设置读突发长度。
		///
		/// @param value 读突发长度。只能是 2 的整数幂。
		///
		constexpr void SetReadingBurstLength(uint32_t value)
		{
			if (value % 2 != 0 && value != 1)
			{
				throw std::invalid_argument{CODE_POS_STR + "读突发长度只能是 2 的整数幂。"};
			}

			if (value > 8)
			{
				throw std::invalid_argument{CODE_POS_STR + "读突发长度不能 > 8."};
			}

			base::bit::WriteBits(_value, 0, 3, value / 2);
		}

		/* #endregion */

		/* #region 读突发模式 */

		constexpr base::sdram::chip::w9825g6kh_6::ReadingBurstMode ReadingBurstMode() const
		{
			if (base::bit::ReadBit(_value, 3))
			{
				return base::sdram::chip::w9825g6kh_6::ReadingBurstMode::Interleaved;
			}

			return ReadingBurstMode::Sequential;
		}

		constexpr void SetReadingBurstMode(base::sdram::chip::w9825g6kh_6::ReadingBurstMode value)
		{
			if (value == base::sdram::chip::w9825g6kh_6::ReadingBurstMode::Interleaved)
			{
				base::bit::WriteBit(_value, 3, true);
			}
			else
			{
				base::bit::WriteBit(_value, 3, false);
			}
		}

		/* #endregion */

		/* #region CasLatency */

		constexpr uint32_t CasLatency() const
		{
			return base::bit::ReadBits(_value, 4, 6);
		}

		constexpr void SetCasLatency(uint32_t value)
		{
			if (value < 2)
			{
				throw std::invalid_argument{CODE_POS_STR + "非法 CasLatency 值。"};
			}

			if (value > 3)
			{
				throw std::invalid_argument{CODE_POS_STR + "非法 CasLatency 值。"};
			}

			base::bit::WriteBits(_value, 4, 6, value);
		}

		/* #endregion */

		/* #region 写突发模式 */

		constexpr base::sdram::chip::w9825g6kh_6::WritingBurstMode WritingBurstMode() const
		{
			if (base::bit::ReadBit(_value, 9))
			{
				return base::sdram::chip::w9825g6kh_6::WritingBurstMode::Single;
			}

			return base::sdram::chip::w9825g6kh_6::WritingBurstMode::Programmed;
		}

		constexpr void SetWritingBurstMode(base::sdram::chip::w9825g6kh_6::WritingBurstMode value)
		{
			if (value == base::sdram::chip::w9825g6kh_6::WritingBurstMode::Single)
			{
				base::bit::WriteBit(_value, 9, true);
			}
			else
			{
				base::bit::WriteBit(_value, 9, false);
			}
		}

		/* #endregion */
	};

} // namespace base::sdram::chip::w9825g6kh_6
