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
		uint8_t _value{};

	public:
		constexpr SymbolCode() = default;

		explicit constexpr SymbolCode(uint8_t value)
			: _value(value)
		{
		}

		explicit constexpr operator uint8_t() const
		{
			return _value;
		}

		static constexpr base::segment_led::SymbolCode Space()
		{
			return SymbolCode{0};
		}

		static constexpr base::segment_led::SymbolCode Number_0()
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

		static constexpr base::segment_led::SymbolCode Number_1()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(4);
			value |= base::bit::Bit(5);
			return SymbolCode{value};
		}

		static constexpr base::segment_led::SymbolCode Number_2()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(0);
			value |= base::bit::Bit(5);
			value |= base::bit::Bit(6);
			value |= base::bit::Bit(2);
			value |= base::bit::Bit(3);
			return SymbolCode{value};
		}

		static constexpr base::segment_led::SymbolCode Number_3()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(0);
			value |= base::bit::Bit(5);
			value |= base::bit::Bit(6);
			value |= base::bit::Bit(4);
			value |= base::bit::Bit(3);
			return SymbolCode{value};
		}

		static constexpr base::segment_led::SymbolCode Number_4()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(1);
			value |= base::bit::Bit(5);
			value |= base::bit::Bit(6);
			value |= base::bit::Bit(4);
			return SymbolCode{value};
		}

		static constexpr base::segment_led::SymbolCode Number_5()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(0);
			value |= base::bit::Bit(1);
			value |= base::bit::Bit(6);
			value |= base::bit::Bit(4);
			value |= base::bit::Bit(3);
			return SymbolCode{value};
		}

		static constexpr base::segment_led::SymbolCode Number_6()
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

		static constexpr base::segment_led::SymbolCode Number_7()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(0);
			value |= base::bit::Bit(5);
			value |= base::bit::Bit(4);
			return SymbolCode{value};
		}

		static constexpr base::segment_led::SymbolCode Number_8()
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

		static constexpr base::segment_led::SymbolCode Number_9()
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

		static constexpr base::segment_led::SymbolCode DigitalDot()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(7);
			return SymbolCode{value};
		}

		static constexpr base::segment_led::SymbolCode Letter_A()
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

		static constexpr base::segment_led::SymbolCode Letter_b()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(1);
			value |= base::bit::Bit(2);
			value |= base::bit::Bit(3);
			value |= base::bit::Bit(4);
			value |= base::bit::Bit(6);
			return SymbolCode{value};
		}

		static constexpr base::segment_led::SymbolCode Letter_C()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(0);
			value |= base::bit::Bit(1);
			value |= base::bit::Bit(2);
			value |= base::bit::Bit(3);
			return SymbolCode{value};
		}

		static constexpr base::segment_led::SymbolCode Letter_c()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(2);
			value |= base::bit::Bit(3);
			value |= base::bit::Bit(6);
			return SymbolCode{value};
		}

		static constexpr base::segment_led::SymbolCode Letter_d()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(2);
			value |= base::bit::Bit(3);
			value |= base::bit::Bit(4);
			value |= base::bit::Bit(5);
			value |= base::bit::Bit(6);
			return SymbolCode{value};
		}

		static constexpr base::segment_led::SymbolCode Letter_E()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(0);
			value |= base::bit::Bit(1);
			value |= base::bit::Bit(2);
			value |= base::bit::Bit(3);
			value |= base::bit::Bit(6);
			return SymbolCode{value};
		}

		static constexpr base::segment_led::SymbolCode Letter_F()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(0);
			value |= base::bit::Bit(1);
			value |= base::bit::Bit(2);
			value |= base::bit::Bit(6);
			return SymbolCode{value};
		}

		static constexpr base::segment_led::SymbolCode Letter_G()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(0);
			value |= base::bit::Bit(1);
			value |= base::bit::Bit(2);
			value |= base::bit::Bit(3);
			value |= base::bit::Bit(4);
			return SymbolCode{value};
		}

		static constexpr base::segment_led::SymbolCode Letter_H()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(1);
			value |= base::bit::Bit(2);
			value |= base::bit::Bit(4);
			value |= base::bit::Bit(5);
			value |= base::bit::Bit(6);
			return SymbolCode{value};
		}

		static constexpr base::segment_led::SymbolCode Letter_i()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(4);
			return SymbolCode{value};
		}

		static constexpr base::segment_led::SymbolCode Letter_J()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(2);
			value |= base::bit::Bit(3);
			value |= base::bit::Bit(4);
			value |= base::bit::Bit(5);
			return SymbolCode{value};
		}

		static constexpr base::segment_led::SymbolCode Letter_L()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(0);
			value |= base::bit::Bit(1);
			value |= base::bit::Bit(2);
			return SymbolCode{value};
		}

		static constexpr base::segment_led::SymbolCode Letter_n()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(2);
			value |= base::bit::Bit(4);
			value |= base::bit::Bit(6);
			return SymbolCode{value};
		}

		static constexpr base::segment_led::SymbolCode Letter_o()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(2);
			value |= base::bit::Bit(3);
			value |= base::bit::Bit(4);
			value |= base::bit::Bit(6);
			return SymbolCode{value};
		}

		static constexpr base::segment_led::SymbolCode Letter_P()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(0);
			value |= base::bit::Bit(1);
			value |= base::bit::Bit(2);
			value |= base::bit::Bit(5);
			value |= base::bit::Bit(6);
			return SymbolCode{value};
		}

		static constexpr base::segment_led::SymbolCode Letter_q()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(0);
			value |= base::bit::Bit(1);
			value |= base::bit::Bit(4);
			value |= base::bit::Bit(5);
			value |= base::bit::Bit(6);
			return SymbolCode{value};
		}

		static constexpr base::segment_led::SymbolCode Letter_r()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(2);
			value |= base::bit::Bit(6);
			return SymbolCode{value};
		}

		static constexpr base::segment_led::SymbolCode Letter_S()
		{
			return base::segment_led::SymbolCode::Number_5();
		}

		static constexpr base::segment_led::SymbolCode Letter_t()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(1);
			value |= base::bit::Bit(2);
			value |= base::bit::Bit(3);
			value |= base::bit::Bit(6);
			return SymbolCode{value};
		}

		static constexpr base::segment_led::SymbolCode Letter_U()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(1);
			value |= base::bit::Bit(2);
			value |= base::bit::Bit(3);
			value |= base::bit::Bit(4);
			value |= base::bit::Bit(5);
			return SymbolCode{value};
		}

		static constexpr base::segment_led::SymbolCode Letter_u()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(2);
			value |= base::bit::Bit(3);
			value |= base::bit::Bit(4);
			return SymbolCode{value};
		}

		static constexpr base::segment_led::SymbolCode Letter_V()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(1);
			value |= base::bit::Bit(2);
			value |= base::bit::Bit(3);
			value |= base::bit::Bit(4);
			value |= base::bit::Bit(5);
			return SymbolCode{value};
		}

		static constexpr base::segment_led::SymbolCode Letter_v()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(2);
			value |= base::bit::Bit(3);
			value |= base::bit::Bit(4);
			return SymbolCode{value};
		}

		static constexpr base::segment_led::SymbolCode Letter_y()
		{
			uint8_t value = 0;
			value |= base::bit::Bit(1);
			value |= base::bit::Bit(3);
			value |= base::bit::Bit(4);
			value |= base::bit::Bit(5);
			value |= base::bit::Bit(6);
			return SymbolCode{value};
		}

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

		// uint8_t value = 0;
		// value |= base::bit::Bit(0);
		// value |= base::bit::Bit(1);
		// value |= base::bit::Bit(2);
		// value |= base::bit::Bit(3);
		// value |= base::bit::Bit(4);
		// value |= base::bit::Bit(5);
		// value |= base::bit::Bit(6);
		// return SymbolCode{value};
	};

	constexpr uint8_t _value{base::segment_led::SymbolCode::Letter_S()};

} // namespace base::segment_led
