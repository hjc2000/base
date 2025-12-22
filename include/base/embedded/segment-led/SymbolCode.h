#pragma once
#include "base/bit/bit.h"
#include <cstdint>

namespace base::segment_led
{
	///
	/// @brief
	///
	/// @note 数码管各段 LED 的索引如下：
	///
	///				   0
	///			      ━━━
	///			 1 ┃      ┃ 5
	///			   ┃   6  ┃
	///			      ━━━
	///			 2 ┃      ┃ 4
	///			   ┃      ┃
	///			      ━━━      7
	///			       3       ．
	///
	/// @note 数码管的代码就是 uint8_t, 每一位代表一个 LED 灯。uint8_t 的位索引与
	/// 各段 LED 的索引一致。
	///
	class SymbolCode
	{
	private:
		uint8_t _value = 0;

	public:
		class Constant;

		constexpr SymbolCode() = default;

		explicit constexpr SymbolCode(uint8_t value)
			: _value(value)
		{
		}

		explicit constexpr operator uint8_t() const
		{
			return _value;
		}

		constexpr bool ReadSegment(uint32_t index) const
		{
			return base::bit::ReadBit(_value, index);
		}

		constexpr void WriteSegment(uint32_t index, bool value)
		{
			base::bit::WriteBit(_value, index, value);
		}

		constexpr bool ReadDigitalDot() const
		{
			return base::bit::ReadBit(_value, 7);
		}

		constexpr void WriteDigitalDot(bool value)
		{
			base::bit::WriteBit(_value, 7, value);
		}

		SymbolCode &operator|=(SymbolCode const &value)
		{
			_value |= value._value;
			return *this;
		}

		SymbolCode &operator+=(SymbolCode const &value)
		{
			_value |= value._value;
			return *this;
		}

		SymbolCode operator|(SymbolCode const &value) const
		{
			SymbolCode copy{*this};
			copy += value;
			return copy;
		}

		SymbolCode operator+(SymbolCode const &value) const
		{
			SymbolCode copy{*this};
			copy += value;
			return copy;
		}
	};

	///
	/// @brief 常量。
	///
	class SymbolCode::Constant
	{
	public:
		///
		/// @brief 空白。
		///
		/// @note 每一段 LED 灯都熄灭，什么都不显示。
		///
		/// @return
		///
		static constexpr base::segment_led::SymbolCode space()
		{
			return SymbolCode{0};
		}

		static constexpr base::segment_led::SymbolCode number_0()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(0);
			value |= base::bit::Bit(1);
			value |= base::bit::Bit(2);
			value |= base::bit::Bit(3);
			value |= base::bit::Bit(4);
			value |= base::bit::Bit(5);
			return SymbolCode{value};
		}

		static constexpr base::segment_led::SymbolCode number_1()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(4);
			value |= base::bit::Bit(5);
			return SymbolCode{value};
		}

		static constexpr base::segment_led::SymbolCode number_2()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(0);
			value |= base::bit::Bit(5);
			value |= base::bit::Bit(6);
			value |= base::bit::Bit(2);
			value |= base::bit::Bit(3);
			return SymbolCode{value};
		}

		static constexpr base::segment_led::SymbolCode number_3()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(0);
			value |= base::bit::Bit(5);
			value |= base::bit::Bit(6);
			value |= base::bit::Bit(4);
			value |= base::bit::Bit(3);
			return SymbolCode{value};
		}

		static constexpr base::segment_led::SymbolCode number_4()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(1);
			value |= base::bit::Bit(5);
			value |= base::bit::Bit(6);
			value |= base::bit::Bit(4);
			return SymbolCode{value};
		}

		static constexpr base::segment_led::SymbolCode number_5()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(0);
			value |= base::bit::Bit(1);
			value |= base::bit::Bit(6);
			value |= base::bit::Bit(4);
			value |= base::bit::Bit(3);
			return SymbolCode{value};
		}

		static constexpr base::segment_led::SymbolCode number_6()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(0);
			value |= base::bit::Bit(1);
			value |= base::bit::Bit(2);
			value |= base::bit::Bit(3);
			value |= base::bit::Bit(4);
			value |= base::bit::Bit(6);
			return SymbolCode{value};
		}

		static constexpr base::segment_led::SymbolCode number_7()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(0);
			value |= base::bit::Bit(5);
			value |= base::bit::Bit(4);
			return SymbolCode{value};
		}

		static constexpr base::segment_led::SymbolCode number_8()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(0);
			value |= base::bit::Bit(1);
			value |= base::bit::Bit(2);
			value |= base::bit::Bit(3);
			value |= base::bit::Bit(4);
			value |= base::bit::Bit(5);
			value |= base::bit::Bit(6);
			return SymbolCode{value};
		}

		static constexpr base::segment_led::SymbolCode number_9()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(0);
			value |= base::bit::Bit(1);
			value |= base::bit::Bit(3);
			value |= base::bit::Bit(4);
			value |= base::bit::Bit(5);
			value |= base::bit::Bit(6);
			return SymbolCode{value};
		}

		static constexpr base::segment_led::SymbolCode digital_dot()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(7);
			return SymbolCode{value};
		}

		static constexpr base::segment_led::SymbolCode letter_A()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(0);
			value |= base::bit::Bit(1);
			value |= base::bit::Bit(2);
			value |= base::bit::Bit(4);
			value |= base::bit::Bit(5);
			value |= base::bit::Bit(6);
			return SymbolCode{value};
		}

		static constexpr base::segment_led::SymbolCode letter_b()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(1);
			value |= base::bit::Bit(2);
			value |= base::bit::Bit(3);
			value |= base::bit::Bit(4);
			value |= base::bit::Bit(6);
			return SymbolCode{value};
		}

		static constexpr base::segment_led::SymbolCode letter_C()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(0);
			value |= base::bit::Bit(1);
			value |= base::bit::Bit(2);
			value |= base::bit::Bit(3);
			return SymbolCode{value};
		}

		static constexpr base::segment_led::SymbolCode letter_c()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(2);
			value |= base::bit::Bit(3);
			value |= base::bit::Bit(6);
			return SymbolCode{value};
		}

		static constexpr base::segment_led::SymbolCode letter_d()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(2);
			value |= base::bit::Bit(3);
			value |= base::bit::Bit(4);
			value |= base::bit::Bit(5);
			value |= base::bit::Bit(6);
			return SymbolCode{value};
		}

		static constexpr base::segment_led::SymbolCode letter_E()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(0);
			value |= base::bit::Bit(1);
			value |= base::bit::Bit(2);
			value |= base::bit::Bit(3);
			value |= base::bit::Bit(6);
			return SymbolCode{value};
		}

		static constexpr base::segment_led::SymbolCode letter_F()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(0);
			value |= base::bit::Bit(1);
			value |= base::bit::Bit(2);
			value |= base::bit::Bit(6);
			return SymbolCode{value};
		}

		static constexpr base::segment_led::SymbolCode letter_G()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(0);
			value |= base::bit::Bit(1);
			value |= base::bit::Bit(2);
			value |= base::bit::Bit(3);
			value |= base::bit::Bit(4);
			return SymbolCode{value};
		}

		static constexpr base::segment_led::SymbolCode letter_H()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(1);
			value |= base::bit::Bit(2);
			value |= base::bit::Bit(4);
			value |= base::bit::Bit(5);
			value |= base::bit::Bit(6);
			return SymbolCode{value};
		}

		static constexpr base::segment_led::SymbolCode letter_i()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(4);
			return SymbolCode{value};
		}

		static constexpr base::segment_led::SymbolCode letter_J()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(2);
			value |= base::bit::Bit(3);
			value |= base::bit::Bit(4);
			value |= base::bit::Bit(5);
			return SymbolCode{value};
		}

		static constexpr base::segment_led::SymbolCode letter_L()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(0);
			value |= base::bit::Bit(1);
			value |= base::bit::Bit(2);
			return SymbolCode{value};
		}

		static constexpr base::segment_led::SymbolCode letter_n()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(2);
			value |= base::bit::Bit(4);
			value |= base::bit::Bit(6);
			return SymbolCode{value};
		}

		static constexpr base::segment_led::SymbolCode letter_o()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(2);
			value |= base::bit::Bit(3);
			value |= base::bit::Bit(4);
			value |= base::bit::Bit(6);
			return SymbolCode{value};
		}

		static constexpr base::segment_led::SymbolCode letter_P()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(0);
			value |= base::bit::Bit(1);
			value |= base::bit::Bit(2);
			value |= base::bit::Bit(5);
			value |= base::bit::Bit(6);
			return SymbolCode{value};
		}

		static constexpr base::segment_led::SymbolCode letter_q()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(0);
			value |= base::bit::Bit(1);
			value |= base::bit::Bit(4);
			value |= base::bit::Bit(5);
			value |= base::bit::Bit(6);
			return SymbolCode{value};
		}

		static constexpr base::segment_led::SymbolCode letter_r()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(2);
			value |= base::bit::Bit(6);
			return SymbolCode{value};
		}

		static constexpr base::segment_led::SymbolCode letter_S()
		{
			return number_5();
		}

		static constexpr base::segment_led::SymbolCode letter_t()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(1);
			value |= base::bit::Bit(2);
			value |= base::bit::Bit(3);
			value |= base::bit::Bit(6);
			return SymbolCode{value};
		}

		static constexpr base::segment_led::SymbolCode letter_U()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(1);
			value |= base::bit::Bit(2);
			value |= base::bit::Bit(3);
			value |= base::bit::Bit(4);
			value |= base::bit::Bit(5);
			return SymbolCode{value};
		}

		static constexpr base::segment_led::SymbolCode letter_u()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(2);
			value |= base::bit::Bit(3);
			value |= base::bit::Bit(4);
			return SymbolCode{value};
		}

		static constexpr base::segment_led::SymbolCode letter_V()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(1);
			value |= base::bit::Bit(2);
			value |= base::bit::Bit(3);
			value |= base::bit::Bit(4);
			value |= base::bit::Bit(5);
			return SymbolCode{value};
		}

		static constexpr base::segment_led::SymbolCode letter_v()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(2);
			value |= base::bit::Bit(3);
			value |= base::bit::Bit(4);
			return SymbolCode{value};
		}

		static constexpr base::segment_led::SymbolCode letter_y()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(1);
			value |= base::bit::Bit(3);
			value |= base::bit::Bit(4);
			value |= base::bit::Bit(5);
			value |= base::bit::Bit(6);
			return SymbolCode{value};
		}

		///
		/// @brief 位于上方的横杠。
		///
		/// @return
		///
		static constexpr base::segment_led::SymbolCode upper_dash()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(0);
			return SymbolCode{value};
		}

		///
		/// @brief 位于中间的横杠。
		///
		/// @return
		///
		static constexpr base::segment_led::SymbolCode middle_dash()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(6);
			return SymbolCode{value};
		}

		///
		/// @brief 位于下方的横杠。
		///
		/// @return
		///
		static constexpr base::segment_led::SymbolCode lower_dash()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(3);
			return SymbolCode{value};
		}

		///
		/// @brief 位于上方的 2 条横杠。
		///
		/// @return
		///
		static constexpr base::segment_led::SymbolCode upper_two_dash()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(0);
			value |= base::bit::Bit(6);
			return SymbolCode{value};
		}

		///
		/// @brief 位于下方的 2 条横杠。
		///
		/// @return
		///
		static constexpr base::segment_led::SymbolCode lower_two_dash()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(6);
			value |= base::bit::Bit(3);
			return SymbolCode{value};
		}

		///
		/// @brief 3 条横杠。
		///
		/// @return
		///
		static constexpr base::segment_led::SymbolCode three_dash()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(0);
			value |= base::bit::Bit(6);
			value |= base::bit::Bit(3);
			return SymbolCode{value};
		}
	};

} // namespace base::segment_led
