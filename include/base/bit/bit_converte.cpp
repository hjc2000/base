#include "bit_converte.h"

uint32_t base::bit_converte::ToUInt32(uint8_t b3, uint8_t b2, uint8_t b1, uint8_t b0)
{
	uint16_t high = ToUInt16(b3, b2);
	uint16_t low = ToUInt16(b1, b0);
	return ToUInt32(high, low);
}
