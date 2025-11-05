#pragma once
#include <cstdint>
#include <memory>

namespace base::segment_led
{
	class segment_led_handle;

	std::shared_ptr<base::segment_led::segment_led_handle> open(uint32_t id);

	///
	/// @brief
	///
	/// @param h
	/// @param symbol_index 符号索引。因为一个数码管面板通常不止能显示 1 个数字。
	///
	/// @param led_index LED 索引。
	/// 	@note 数码管各段的索引如下：
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
	/// @return
	///
	bool read_symbol_led(base::segment_led::segment_led_handle &h,
						 uint32_t symbol_index,
						 uint32_t led_index);

	///
	/// @brief 写其中一个符号的某一个 LED.
	///
	///
	///
	///
	/// @param h
	/// @param symbol_index 符号索引。因为一个数码管面板通常不止能显示 1 个数字。
	///
	/// @param led_index LED 索引。
	/// 	@note 数码管各段的索引如下：
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
	/// @param value 要写入的值。
	///
	void write_symbol_led(base::segment_led::segment_led_handle &h,
						  uint32_t symbol_index,
						  uint32_t led_index,
						  bool value);

} // namespace base::segment_led
