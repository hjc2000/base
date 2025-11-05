#pragma once
#include <cstdint>
#include <memory>

namespace base::segment_led
{
	///
	/// @brief 数码管面板句柄。
	///
	/// @note 数码管各段的索引如下：
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
	class segment_led_handle;

	std::shared_ptr<base::segment_led::segment_led_handle> open(uint32_t id);

	///
	/// @brief 读其中一个符号的某一个 LED.
	///
	/// @param h
	/// @param symbol_index 符号索引。
	///
	/// @param led_index LED 索引。
	/// 	@note 数码管各段的索引见 @ref "class segment_led_handle" 的注释。
	///
	/// @return
	///
	bool read_symbol_led(base::segment_led::segment_led_handle &h,
						 uint32_t symbol_index,
						 uint32_t led_index);

	///
	/// @brief 写其中一个符号的某一个 LED.
	///
	/// @param h
	/// @param symbol_index 符号索引。
	///
	/// @param led_index LED 索引。
	/// 	@note 数码管各段的索引见 "class segment_led_handle" 的注释。
	///
	/// @param value 要写入的值。
	///
	void write_symbol_led(base::segment_led::segment_led_handle &h,
						  uint32_t symbol_index,
						  uint32_t led_index,
						  bool value);

	///
	/// @brief 读取指定符号的代码。
	///
	/// @note 数码管的代码就是 uint8_t, 每一位代表一个 LED 灯。uint8_t 的位索引与
	/// "class segment_led_handle" 的注释中定义的各段 LED 的索引一致。
	///
	/// @param h
	/// @param symbol_index 符号索引。
	/// @return
	///
	uint8_t read_symbol_code(base::segment_led::segment_led_handle &h, uint32_t symbol_index);

	///
	/// @brief 写指定符号的代码。
	///
	/// @param h
	/// @param symbol_index 符号索引。
	/// @param code
	///
	void write_symbol_code(base::segment_led::segment_led_handle &h,
						   uint32_t symbol_index,
						   uint8_t code);

} // namespace base::segment_led
